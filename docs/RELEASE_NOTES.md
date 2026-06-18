# Sample Release Notes

These are polished templates for planned milestones. Replace planned language, dates, download links, hashes, and contributor names with verified release data before publishing.

## v0.1.0-alpha - Edit, Build, Run

OfflineCode Studio's first alpha demonstrates the complete local C++ loop in one lightweight desktop window.

### Highlights

- Create, open, edit, and save C++ source files in a QScintilla editor.
- C++17 syntax highlighting, line numbers, folding, brace matching, and search.
- Open a JSON-backed project and compile it with a discovered GCC or Clang toolchain.
- Stream build output without blocking the interface and navigate basic diagnostics.
- Run the latest artifact with stdin, stdout/stderr, exit status, timeout, and Stop.

### Known limitations

This alpha targets contributors and early testers. Project templates, MSVC normalization, test-case management, recovery, accessibility hardening, and installers remain in progress. Running code is not sandboxed.

### Upgrade notes

The manifest is experimental and may change before 1.0. Back up important project metadata. Build artifacts are not compatible promises and can be deleted safely.

## v0.5.0-beta - Projects and Test Cases

The beta turns the proof of concept into a practical offline workspace for students and competitive programmers.

### Highlights

- Project explorer, portable templates, recent projects, and session restore.
- GCC, Clang, Apple Clang, and MSVC toolchain profiles.
- Normalized Problems panel while preserving complete raw compiler output.
- Multiple persisted test cases with exact, trailing-whitespace, and token comparison.
- Runtime, timeout, exit status, stderr, and first-mismatch reporting.
- Light/dark/system themes, configurable shortcuts, autosave recovery, and settings.
- Preview packages for Windows, Linux, and macOS.

### Fixed

- Prevented stale asynchronous compiler output from replacing the current build result.
- Capped retained child-process output while continuing to drain pipes.
- Reconciled atomic-save rename events without duplicating project-tree entries.

### Testing focus

Please report toolchain discovery, high-DPI layout, screen-reader behavior, descendant process cleanup, and manifest migration problems using the issue templates.

## v1.0.0 - Stable Offline C++ Development

OfflineCode Studio 1.0 establishes a stable, private, cross-platform C++ workflow with no required cloud service, account, telemetry, or network connection.

### Highlights

- Stable, schema-versioned project format with validated migration and atomic writes.
- Safe multi-tab editing, external-change reconciliation, recovery, and large-file safeguards.
- Asynchronous compilation and execution with toolchain-specific strategies and cancellation.
- Competitive-programming workspace with persistent cases, deterministic comparison, and limits.
- Keyboard-complete UI, accessible status announcements, high-DPI support, and packaged offline help.
- Release packages with checksums, third-party notices, and build provenance.

### Compatibility

- Windows 10/11 x64 with MSVC 2022 or supported MinGW configuration.
- Ubuntu 22.04+ x64 with GCC or Clang.
- macOS 13+ on Apple Silicon and Intel with Apple Clang.

The exact Qt/QScintilla and compiler compatibility matrix belongs in the final release artifact.

### Security

Compiler and program arguments are passed without shell interpolation. Project-relative paths are validated. Local programs still execute with user privileges; OfflineCode Studio is not a sandbox for untrusted code.

### Upgrade notes

Projects from supported prerelease schemas are migrated after creating a backup. Keep source control or an independent backup. Review `KNOWN_ISSUES.md` before upgrading production classroom images.

### Thank you

Credit contributors by GitHub handle and link the full changelog, checksums, SBOM, and signed artifacts when this release is real.
