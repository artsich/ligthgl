using System.Runtime.InteropServices;

namespace LightGl.Bindings;

public unsafe static class WebGpuNative
{
	public const int LIGHT_GL_SUCCESS = 0;

	private const string nativeLibName = "lightgl";

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern int light_gl_init();

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern int light_gl_destroy();
}