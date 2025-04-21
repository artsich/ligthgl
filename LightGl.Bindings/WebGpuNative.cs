using System.Runtime.InteropServices;

namespace LightGl.Bindings;

public unsafe static class WebGpuNative
{
	private const string nativeLibName = "lightgl";

	[DllImport(nativeLibName, CallingConvention = CallingConvention.Cdecl)]
	public static extern int my_function(int v);
}