using LightGl.Bindings;
using System.Runtime.InteropServices.JavaScript;

namespace LightGl;

public partial class Application
{
	public static void Main(string[] args)
	{
	}

	[JSExport]
	public static void UpdateFrame()
	{
		Console.WriteLine("Hello from c#");
		Console.WriteLine("Try call light gl");

		//Console.WriteLine("The result of c++ 33 * 2 = " + WebGpuNative.my_function(33));
	}
}
