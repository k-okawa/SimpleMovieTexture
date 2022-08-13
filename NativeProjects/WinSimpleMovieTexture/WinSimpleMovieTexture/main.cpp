#include "global.h"
#include "MoviePlayer.h"

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
        
    }

    UNITY_INTERFACE_EXPORT UnityRenderingEvent UNITY_INTERFACE_API GetRenderEventFunc() {
        return OnRenderEvent;
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetTexturePtr(void* texturePtr, int width, int height) {
        global::DebugLog("SetTexturePtr");
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

    UNITY_INTERFACE_EXPORT void  UNITY_INTERFACE_API MovieTest(char* moviePath) {
        global::DebugLog("MovieTest");
        global::DebugLog(moviePath);
        
        IGraphBuilder* pGraph = NULL;
        IMediaControl* pControl = NULL;
        IMediaEvent* pEvent = NULL;

        // Initialize the COM library.
        HRESULT hr = CoInitialize(NULL);
        if (FAILED(hr))
        {
            global::DebugLogError("ERROR - Could not initialize COM library");
            return;
        }

        global::DebugLog("Finish CoInitialize");

        // Create the filter graph manager and query for interfaces.
        hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
            IID_IGraphBuilder, (void**)&pGraph);
        if (FAILED(hr))
        {
            global::DebugLogError("ERROR - Could not create the Filter Graph Manager.");
            return;
        }

        global::DebugLog("Finish CoCreateInstance");

        hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
        hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

        // Build the graph. IMPORTANT: Change this string to a file on your system.
        auto wStrPath = global::CharPtrToLPWSTR(moviePath);
        hr = pGraph->RenderFile(wStrPath, NULL);
        delete wStrPath;
        if (SUCCEEDED(hr))
        {
            // Run the graph.
            hr = pControl->Run();
            if (SUCCEEDED(hr))
            {
                // Wait for completion.
                long evCode;
                pEvent->WaitForCompletion(INFINITE, &evCode);

                // Note: Do not use INFINITE in a real application, because it
                // can block indefinitely.
            }
        }

        pControl->Release();
        pEvent->Release();
        pGraph->Release();
        CoUninitialize();
    }
}