[CmdletBinding()]
param(
    [string]$Preset = "ninja-release",
    [string]$OutputDir = "dist\windows",
    [ValidateSet("x86", "x64", "arm64")]
    [string]$Architecture = "x64",
    [switch]$AcceptWixEula
)

$ErrorActionPreference = "Stop"
$RepoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")

if ([System.Environment]::OSVersion.Platform -ne [System.PlatformID]::Win32NT) {
    throw "scripts/build-msi.ps1 only supports Windows."
}

function Invoke-CheckedCommand {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Command,

        [Parameter(Mandatory = $true)]
        [string[]]$Arguments
    )

    & $Command @Arguments
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
}

function Get-TextEditorVersion {
    param(
        [Parameter(Mandatory = $true)]
        [string]$CMakeLists
    )

    $content = Get-Content -Raw -LiteralPath $CMakeLists
    if ($content -match "project\s*\(\s*TextEditor[\s\S]*?VERSION\s+([0-9]+\.[0-9]+\.[0-9]+)") {
        return $Matches[1]
    }

    throw "Could not find project(TextEditor VERSION x.y.z) in $CMakeLists."
}

function Get-TextEditorExe {
    param(
        [Parameter(Mandatory = $true)]
        [string]$BuildDir
    )

    $candidates = @(
        (Join-Path $BuildDir "bin\td.exe"),
        (Join-Path $BuildDir "bin\Release\td.exe"),
        (Join-Path $BuildDir "bin\Debug\td.exe"),
        (Join-Path $BuildDir "Release\td.exe"),
        (Join-Path $BuildDir "Debug\td.exe"),
        (Join-Path $BuildDir "td.exe")
    )

    foreach ($candidate in $candidates) {
        if (Test-Path -LiteralPath $candidate) {
            return (Resolve-Path -LiteralPath $candidate).Path
        }
    }

    $found = Get-ChildItem -LiteralPath $BuildDir -Recurse -File -Filter "td.exe" |
        Sort-Object FullName |
        Select-Object -First 1
    if ($found) {
        return $found.FullName
    }

    throw "Could not find td.exe under $BuildDir."
}

if (-not (Get-Command "wix" -ErrorAction SilentlyContinue)) {
    throw "WiX Toolset CLI was not found. Install WiX Toolset v4 or newer and ensure the 'wix' command is on PATH."
}

$resolvedOutputDir = $ExecutionContext.SessionState.Path.GetUnresolvedProviderPathFromPSPath($OutputDir)

Push-Location $RepoRoot
try {
    $version = Get-TextEditorVersion -CMakeLists (Join-Path $RepoRoot "CMakeLists.txt")

    Invoke-CheckedCommand -Command "cmake" -Arguments @("--preset", $Preset)
    Invoke-CheckedCommand -Command "cmake" -Arguments @("--build", "--preset", $Preset, "--target", "texteditor_exe")

    $buildDir = Join-Path (Join-Path $RepoRoot "build") $Preset
    $textEditorExe = Get-TextEditorExe -BuildDir $buildDir

    New-Item -ItemType Directory -Force -Path $resolvedOutputDir | Out-Null

    $wxsFile = Join-Path $RepoRoot "installer\windows\TextEditor.wxs"
    $licenseRtf = Join-Path $RepoRoot "installer\windows\License.rtf"
    $msiPath = Join-Path $resolvedOutputDir "TextEditor-$version-$Architecture.msi"

    $wixArguments = @("build")
    if ($AcceptWixEula) {
        $wixArguments += @("-acceptEula", "wix7")
    }
    $wixArguments += @(
        $wxsFile,
        "-ext",
        "WixToolset.UI.wixext",
        "-arch",
        $Architecture,
        "-d",
        "ProductVersion=$version",
        "-d",
        "TextEditorExe=$textEditorExe",
        "-d",
        "LicenseRtf=$licenseRtf",
        "-o",
        $msiPath
    )

    Invoke-CheckedCommand -Command "wix" -Arguments $wixArguments

    Write-Host "Built MSI: $msiPath"
} finally {
    Pop-Location
}
