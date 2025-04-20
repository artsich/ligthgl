param (
	[Parameter()]
	[ValidateSet("Release", "Debug")]
	[string]$configuration = "Release",

	[Parameter()]
	[string]$outputPath = $null
)

$ErrorActionPreference = "Stop"
Set-StrictMode -version latest

try {
	cmake -S "$PSScriptRoot" -B "$PSScriptRoot/out/$configuration" -DCMAKE_BUILD_TYPE=$configuration
	cmake --build "$PSScriptRoot/out/$configuration" --config $configuration

	Write-Host "Build completed"
}
catch {
	Write-Error "Failed to build native project"
	Write-Error $_.Exception.Message
	exit 1
}

if ($outputPath) {
	if (-not (Test-Path $outputPath)) {
		New-Item -Path $outputPath -ItemType Directory -Force | Out-Null
		Write-Host "Created output directory: $outputPath"
	}
	
	$SourcePath = Join-Path $PSScriptRoot "out/$configuration/$configuration"
	Copy-Item -Path "$SourcePath\*" -Destination $outputPath -Force -Recurse
	Write-Host "Copied build artifacts to: $outputPath"
}
