# TextEditor

A command-line text editor built in C11.

## Layout

```text
include/        Public headers
src/            Implementation files
tests/          CTest test programs
cmake/          CMake modules
scripts/        Local bootstrap and check entry points
doc/            Short project documentation
doc/guides/     Topic guides
.github/        CI workflows and repository templates
```

## Quick Start

Required tools:

- CMake 3.21 or newer.
- A C11 compiler from MSVC, GCC, Clang, or AppleClang.
- Ninja for the default cross-platform presets, or another CMake-supported
  generator through local presets.

On Windows, run the Ninja presets from a Developer PowerShell, Developer
Command Prompt, or VS Code CMake kit that initializes MSVC.

For step-by-step installation instructions per platform, see
[doc/guides/environment.md](doc/guides/environment.md).

Recommended editor tools:

- VS Code with the CMake Tools and clangd extensions.
- Ninja, because it generates `compile_commands.json` for clangd.
- Microsoft C/C++ remains usable as a local fallback; see
  `.vscode/c_cpp_properties.example.json`.

The repository includes portable VS Code recommendations, CMake tasks, clangd
defaults, an optional C/C++ fallback example, and Ninja presets. Compiler
installation paths and per-user kits stay in local user configuration.

First-time setup:

**Windows PowerShell**

```powershell
./scripts/bootstrap.ps1
```

**Linux/macOS**

```sh
./scripts/bootstrap.sh
```

The bootstrap script checks required tools and runs configure so editors can
load `build/ninja-debug/compile_commands.json`.

For a local Visual Studio, Xcode, or Make workflow, copy
`CMakeUserPresets.example.json` to `CMakeUserPresets.json` and edit it for your
machine. The real user preset file is ignored by Git.

Daily check:

**Windows PowerShell**

```powershell
./scripts/check.ps1
```

**Linux/macOS**

```sh
./scripts/check.sh
```

Optional clang-tidy checks:

**Windows PowerShell**

```powershell
./scripts/check.ps1 -EnableTidy
```

**Linux/macOS**

```sh
./scripts/check.sh --enable-tidy
```

For a fuller explanation of configure, build, test, install, presets, and common
errors, see [doc/guides/cmake.md](doc/guides/cmake.md).

## Documentation Map

- [doc/README.md](doc/README.md) maps each topic to its source of truth.
- [doc/guides/cmake.md](doc/guides/cmake.md) explains day-to-day CMake usage.
- [doc/guides/testing.md](doc/guides/testing.md) describes test and static-analysis
  expectations.
- [CONTRIBUTING.md](CONTRIBUTING.md) describes branch, commit, and PR workflow.
- [SECURITY.md](SECURITY.md) describes vulnerability and dependency handling.
- [C_PROJECT_STANDARD.md](C_PROJECT_STANDARD.md) defines the reusable project standard
  this project follows.

## Installed Package Use

The install rules generate a CMake package config:

```cmake
find_package(TextEditor CONFIG REQUIRED)
target_link_libraries(app PRIVATE TextEditor::texteditor_lib)
```

The `tests/package_smoke/` project validates installed C and C++ consumers.

Direct source-tree consumption through `add_subdirectory()` is validated by
`tests/subproject_smoke/`.

See [C_PROJECT_STANDARD.md](C_PROJECT_STANDARD.md) for the full guidance.
