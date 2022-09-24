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

    void UNITY_INTERFACE_API OnRenderEvent(int eventId) {
        auto device = global::unity->Get<IUnityGraphicsD3D11>()->GetDevice();
        for (auto itr : global::moviePlayerMap) {
            if (global::movieTexturePtrMap.count(itr.first) == 0) {
                continue;
            }
            auto texture = (ID3D11Texture2D*)global::movieTexturePtrMap[itr.first];
            ID3D11DeviceContext* context;
            device->GetImmediateContext(&context);
            context->UpdateSubresource(texture, 0, nullptr, itr.second->GetMovieBuffer(), itr.second->GetWidth() * 4, 0);
        }
    }

    UNITY_INTERFACE_EXPORT UnityRenderingEvent UNITY_INTERFACE_API GetRenderEventFunc() {
        return OnRenderEvent;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API ReleasePlayer() {

    }

    UNITY_INTERFACE_EXPORT unsigned long UNITY_INTERFACE_API CreateMoviePlayer(char* moviePath) {
        auto moviePlayer = new MoviePlayer();
        if (FAILED(moviePlayer->Init(moviePath))) {
            return 0;
        }
        ULONG id = global::idIncrement++;
        global::moviePlayerMap[id] = moviePlayer;
        return id;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetMovieTexturePtr(unsigned long id, void* texturePtr) {
        global::movieTexturePtrMap[id] = texturePtr;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API DisposeMoviePlayer(unsigned long id) {
        if (global::moviePlayerMap.count(id) != 0) {
            auto moviePlayer = global::moviePlayerMap[id];
            global::moviePlayerMap.erase(id);
            delete moviePlayer;
        }

        global::movieTexturePtrMap.erase(id);
    }

    UNITY_INTERFACE_EXPORT long UNITY_INTERFACE_API GetMovieWidth(unsigned long id) {
        if (global::moviePlayerMap.count(id) == 0) {
            return 0;
        }
        return global::moviePlayerMap[id]->GetWidth();
    }

    UNITY_INTERFACE_EXPORT long UNITY_INTERFACE_API GetMovieHeight(unsigned long id) {
        if (global::moviePlayerMap.count(id) == 0) {
            return 0;
        }
        return global::moviePlayerMap[id]->GetHeight();
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API StartMovie(unsigned long id) {
        if (global::moviePlayerMap.count(id) == 0) {
            return;
        }
        global::moviePlayerMap[id]->Play();
    }
}