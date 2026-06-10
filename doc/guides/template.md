# Project Origin

This project was created from the
[C Project Standard](https://github.com/your-org/c-project-standard) template
and renamed to **TextEditor** using the `rename-project.ps1` script.

## What Was Renamed

The rename script replaced `TextEditor`, `texteditor`, and `TEXTEDITOR` across
all source, cmake, CI, and documentation files, then renamed the include and
source directories and cmake config files to match.

## What Was Kept

- CMake modules split by responsibility.
- C11 as the target-level language baseline.
- Cross-platform compiler support for MSVC, GCC, Clang, and AppleClang.
- CMake presets for debug, release, sanitizer, and coverage builds.
- Static and shared library builds through `BUILD_SHARED_LIBS`.
- CTest based unit tests.
- Installable CMake package config with downstream smoke tests.
- `add_subdirectory()` smoke tests for subproject consumers.
- GitHub Actions for build, test, and static analysis.
- Short contributor, testing, release, security, and AI-agent guidance.

## Next Steps For This Project

The template scaffolding (example library, example executable) is in place.
Replace it with the real text editor implementation:

- Replace `include/texteditor/example.h` with the editor's public API.
- Replace `src/texteditor/example.c` with the editor's core implementation.
- Replace `src/main.c` with the editor's entry point.
- Keep tests focused on public behavior in `tests/`.

## Validate The Project

Run the local checks:

**Windows PowerShell**

```powershell
./scripts/bootstrap.ps1
./scripts/check.ps1
cmake --preset ninja-shared
cmake --build --preset ninja-shared
ctest --preset ninja-shared --output-on-failure
```

**Linux/macOS**

```sh
./scripts/bootstrap.sh
./scripts/check.sh
cmake --preset ninja-shared
cmake --build --preset ninja-shared
ctest --preset ninja-shared --output-on-failure
```
