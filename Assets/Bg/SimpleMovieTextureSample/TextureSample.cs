using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class TextureSample : MonoBehaviour
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void DebugLogDelegate(string str);
    DebugLogDelegate debugLogFunc = Debug.Log;
    
    [DllImport("WinSimpleMovieTexture")]
    public static extern void SetDebugLogFunc(IntPtr ptr);
    
    [DllImport("WinSimpleMovieTexture")]
    private static extern void SetTexturePtr(IntPtr texturePtr, int width, int height);

    [SerializeField] private Image _image;

    void Start()
    {
        var logCallback = new DebugLogDelegate(debugLogFunc);
        var ptr = Marshal.GetFunctionPointerForDelegate(logCallback);
        SetDebugLogFunc(ptr);
        
        var tex = new Texture2D(1920, 1080, TextureFormat.RGBA32, false);
        var sprite = Sprite.Create(tex, new Rect(0, 0, tex.width, tex.height), Vector2.zero);
        _image.sprite = sprite;
        SetTexturePtr(tex.GetNativeTexturePtr(), tex.width, tex.height);
    }
}