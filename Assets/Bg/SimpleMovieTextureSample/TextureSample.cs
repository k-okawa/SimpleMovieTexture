using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class TextureSample : MonoBehaviour
{
    [DllImport(("WinSimpleMovieTexture"))]
    private static extern void SetTexturePtr(IntPtr texturePtr, int width, int height);

    [SerializeField] private Image _image;

    void Start()
    {
        var tex = new Texture2D(1920, 1080, TextureFormat.RGBA32, false);
        var sprite = Sprite.Create(tex, new Rect(0, 0, tex.width, tex.height), Vector2.zero);
        _image.sprite = sprite;
        SetTexturePtr(tex.GetNativeTexturePtr(), tex.width, tex.height);
    }
}