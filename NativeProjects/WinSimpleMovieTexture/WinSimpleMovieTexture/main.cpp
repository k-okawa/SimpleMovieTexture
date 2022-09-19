#include "global.h"
#include "MoviePlayer.h"
#include <string>
#include <Windows.h>

extern "C" {
    UNITY_INTERFACE_EXPORT void SetDebugLogFunc(global::DebugLogFuncType func) {
        global::debugLogFunc = func;
    }

    UNITY_INTERFACE_EXPORT void SetDebugLogErrorFunc(global::DebugLogFuncType func) {
        global::debugLogErrorFunc = func;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces) {
        global::unity = unityInterfaces;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload() {

    }

    ID3D11Texture2D* movieTexture;
    MoviePlayer* player;
    void UNITY_INTERFACE_API OnRenderEvent(int eventId) {
        if (player == nullptr) {
            return;
        }

        auto device = global::unity->Get<IUnityGraphicsD3D11>()->GetDevice();
        ID3D11DeviceContext* context;
        device->GetImmediateContext(&context);
        context->UpdateSubresource(movieTexture, 0, nullptr, player->GetMovieBuffer(), player->GetWidth() * 4, 0);
    }

    UNITY_INTERFACE_EXPORT UnityRenderingEvent UNITY_INTERFACE_API GetRenderEventFunc() {
        return OnRenderEvent;
    }

    UNITY_INTERFACE_EXPORT bool  UNITY_INTERFACE_API MovieTest(char* moviePath, void* texturePtr) {
        movieTexture = (ID3D11Texture2D*)texturePtr;
        auto moviePlayer = new MoviePlayer();
        if (FAILED(moviePlayer->Init(moviePath))) {
            return false;
        }

        player = moviePlayer;
        return true;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API ReleasePlayer() {

    }
}