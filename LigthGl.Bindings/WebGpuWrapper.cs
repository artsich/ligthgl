using System.Runtime.InteropServices;

namespace LightGl.Bindings;

public static class WebGpuNative
{
	private const string DllName = "Libs\\LightGl.Native\\lightgl";

	[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
	public static extern int print_adapter_info();
}