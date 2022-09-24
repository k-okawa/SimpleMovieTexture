using System;
using System.Collections;
using System.IO;
using System.Runtime.InteropServices;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class TextureSample : MonoBehaviour
{
    private const string DLL_NAME = "WinSimpleMovieTexture";
    
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void DebugLogDelegate(string str);
    DebugLogDelegate debugLogFunc = Debug.Log;
    private DebugLogDelegate debugLogErrorFunc = Debug.LogError;
    
    [DllImport(DLL_NAME)]
    public static extern void SetDebugLogFunc(IntPtr ptr);
    
    [DllImport(DLL_NAME)]
    public static extern void SetDebugLogErrorFunc(IntPtr ptr);
    
    [DllImport(DLL_NAME)]
    public static extern IntPtr GetRenderEventFunc();

    [DllImport(DLL_NAME)]
    private static extern ulong CreateMoviePlayer(string moviePath);

    [DllImport(DLL_NAME)]
    private static extern void SetMovieTexturePtr(ulong id, IntPtr texturePtr);

    [DllImport(DLL_NAME)]
    private static extern void DisposeMoviePlayer(ulong id);

    [DllImport(DLL_NAME)]
    private static extern long GetMovieWidth(ulong id);
    
    [DllImport(DLL_NAME)]
    private static extern long GetMovieHeight(ulong id);

    [DllImport(DLL_NAME)]
    private static extern void StartMovie(ulong id);


    [SerializeField] private Image _image;

    private ulong _movieId;

    void Start()
    {
        // デバッグログ設定
        var logCallback = new DebugLogDelegate(debugLogFunc);
        var ptr = Marshal.GetFunctionPointerForDelegate(logCallback);
        SetDebugLogFunc(ptr);

        var logErrorCallback = new DebugLogDelegate(debugLogErrorFunc);
        var ptrError = Marshal.GetFunctionPointerForDelegate(logErrorCallback);
        SetDebugLogErrorFunc(ptrError);
        
        // MoviePlayer作成
        string moviePath = Path.Combine(Application.streamingAssetsPath, "TestMovie.wmv");
        moviePath = moviePath.Replace("/", "\\");
        _movieId = CreateMoviePlayer(moviePath);
        if (_movieId <= 0)
        {
            Debug.LogError("video init failed");
            return;
        }

        // Texture作成
        var tex = new Texture2D((int)GetMovieWidth(_movieId), (int)GetMovieHeight(_movieId), TextureFormat.RGBA32, false);
        var sprite = Sprite.Create(tex, new Rect(0, 0, tex.width, tex.height), Vector2.zero);
        _image.sprite = sprite;
        
        // Textureをセット
        SetMovieTexturePtr(_movieId, tex.GetNativeTexturePtr());
        
        // 動画再生開始
        StartMovie(_movieId);

        // 描画コルーチン開始
        StartCoroutine(OnRender());
    }

    private void OnDestroy()
    {
        DisposeMoviePlayer(_movieId);
    }

    IEnumerator OnRender()
    {
        while (true)
        {
            yield return new WaitForEndOfFrame();
            GL.IssuePluginEvent(GetRenderEventFunc(), 0);
        }
    }
}