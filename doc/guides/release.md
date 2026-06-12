# Release

This template does not prescribe a release tool. A typical release should:

1. Update version metadata.
2. Run `./scripts/check.sh --preset ninja-release` (or `./scripts/check.ps1 -Preset ninja-release` on Windows PowerShell).
3. Run shared-library, sanitizer, or coverage presets where supported.
4. Update release notes.
5. Run static and shared package smoke tests for installable libraries.
6. Build platform installers, such as the Windows MSI when publishing Windows artifacts.
7. Tag the release.
8. Publish artifacts through CI or a documented local packaging command.

Do not publish releases from AI-assisted changes without maintainer approval.

## Suggested Verification

Use `cmake.md` for detailed command explanations. A release-oriented local
check usually includes:

**Linux/macOS**

```sh
./scripts/check.sh --preset ninja-release
cmake --preset ninja-shared
cmake --build --preset ninja-shared
ctest --preset ninja-shared --output-on-failure
cmake --preset ninja-asan
cmake --build --preset ninja-asan
ctest --preset ninja-asan --output-on-failure
```

**Windows PowerShell**

```powershell
./scripts/check.ps1 -Preset ninja-release
cmake --preset ninja-shared
cmake --build --preset ninja-shared
ctest --preset ninja-shared --output-on-failure
cmake --preset ninja-asan
cmake --build --preset ninja-asan
ctest --preset ninja-asan --output-on-failure
```

For installable libraries, also run static and shared package smoke tests before
tagging.

Build the Windows MSI from a Windows shell with WiX Toolset v4 or newer installed:

```powershell
./scripts/build-msi.ps1
```

With WiX v7, accept the WiX Toolset OSMF EULA once with `wix eula accept wix7`
or pass `-AcceptWixEula` to `build-msi.ps1`.

The MSI is written to `dist/windows/`.
