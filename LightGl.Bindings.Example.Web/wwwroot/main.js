import { dotnet } from './_framework/dotnet.js';

const runtimeAPI = await dotnet
    .withDiagnosticTracing(false)
    .create();

const { getConfig, getAssemblyExports, runMain } = runtimeAPI;

const config = getConfig();
const exports = await getAssemblyExports(config.mainAssemblyName);

// start your .NET Main(), but *don't* exit the runtime:
await runMain(config.mainAssemblyName);

function mainLoop() {
    exports.LightGl.Application.UpdateFrame();
    //window.requestAnimationFrame(mainLoop);
}

window.requestAnimationFrame(mainLoop);
console.log("Initial setup of JS side");
