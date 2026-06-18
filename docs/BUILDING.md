# Building OfflineCode Studio

## Requirements

- CMake 3.24+
- Ninja or a platform build system
- C++17 compiler
- Qt 6.5+ with Core, Gui, Widgets, and Test
- QScintilla 2.14+ compiled against the same Qt major version

## Common Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Useful options:

| Option | Default | Purpose |
|---|---:|---|
| `OFFLINECODE_BUILD_TESTS` | `ON` | Configure unit/integration tests |
| `OFFLINECODE_ENABLE_WARNINGS_AS_ERRORS` | `OFF` | Treat project warnings as errors |
| `OFFLINECODE_ENABLE_SANITIZERS` | `OFF` | Enable ASan/UBSan on supported compilers |

## Windows

Use the Qt Online Installer or a compatible package manager, then run from an x64 Native Tools prompt when using MSVC.

```powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:\Qt\6.7.3\msvc2022_64
cmake --build build
ctest --test-dir build --output-on-failure
```

QScintilla may require an additional prefix path. Keep architecture (x64/ARM64), compiler ABI, build type, and Qt major version aligned.

## macOS

```bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/Qt/6.7.3/macos"
cmake --build build
ctest --test-dir build --output-on-failure
```

The minimum deployment target is set in release presets. Signing and notarization are intentionally excluded from local debug builds.

## Linux

Install Qt 6 development packages, QScintilla for Qt 6, Ninja, and a supported compiler from the distribution. Package names vary. Avoid mixing distro Qt with a differently-versioned QScintilla build.

## Troubleshooting

- **Qt not found:** add the Qt installation prefix to `CMAKE_PREFIX_PATH`.
- **QScintilla not found:** provide `QScintillaQt6_DIR` or install its CMake/pkg-config development metadata.
- **Undefined Qt symbols:** remove the build directory and ensure all dependencies share the same compiler/architecture/Qt build.
- **No runtime compiler found:** the IDE compiler used to build OfflineCode Studio and the compiler used for user projects are separate; configure the latter in Toolchains.
