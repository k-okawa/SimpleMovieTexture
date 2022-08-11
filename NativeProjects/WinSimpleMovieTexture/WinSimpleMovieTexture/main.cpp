#include <d3d11.h>
#include <thread>
#include <mutex>
#include <memory>

#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityGraphicsD3D11.h"

namespace global {
	IUnityInterfaces* unity = nullptr;
}

extern "C" {
    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces) {
        global::unity = unityInterfaces;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API UnityPluginUnload() {
        
    }

    void UNITY_INTERFACE_API OnRenderEvent(int eventId) {
        
    }

    UNITY_INTERFACE_EXPORT UnityRenderingEvent UNITY_INTERFACE_API GetRenderEventFunc() {
        return OnRenderEvent;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetTexturePtr(void* texturePtr, int width, int height) {
        // RGBA
        std::unique_ptr<BYTE[]> colors = std::make_unique<BYTE[]>(width * height * 4);
        // ê‘
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                int index = (h * height + w) * 4;
                // R
                colors[index + 0] = UCHAR_MAX;
                // G
                colors[index + 1] = 0;
                // B
                colors[index + 2] = 0;
                // A
                colors[index + 3] = UCHAR_MAX;
            }
        }

        auto device = global::unity->Get<IUnityGraphicsD3D11>()->GetDevice();
        ID3D11DeviceContext* context;
        device->GetImmediateContext(&context);
        ID3D11Texture2D* texture = (ID3D11Texture2D*)texturePtr;
        context->UpdateSubresource(texture, 0, nullptr, colors.get(), 4, 0);
    }
}