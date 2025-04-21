param (
	[Parameter()]
	[ValidateSet("Release", "Debug")]
	[string]$configuration = "Release"
)

Write-Host "Building for web with configuration $configuration"

emsdk activate 3.1.56 #latest

$pathToBuild = Join-Path $PSScriptRoot "out/web/$configuration"

Write-Host "configure: cmake -S $PSScriptRoot -B $pathToBuild -DCMAKE_BUILD_TYPE=$configuration"
emcmake cmake -S "$PSScriptRoot" -B $pathToBuild -DCMAKE_BUILD_TYPE="$configuration"
cmake --build $pathToBuild --config "$configuration" -j4 

Write-Host "Web Build completed."

