# Product Roadmap

Dates are intentionally omitted until maintainer capacity and dependency availability are known. Milestones are outcome-based; semantic versions use `MAJOR.MINOR.PATCH` with prerelease suffixes.

## v0.1 Alpha: Edit, Build, Run

**Goal:** prove the end-to-end local workflow.

- Qt main window and QScintilla editor
- Create/open/save files with dirty-state protection
- C++ highlighting, line numbers, folding, search
- Single-project JSON manifest
- GCC/Clang discovery and single-target compilation
- Raw build output and basic diagnostic navigation
- Program execution, stdin/stdout/stderr, timeout, stop
- Linux-first CI and developer documentation

**Gate:** no silent source loss; UI remains responsive during build/run; smoke workflow passes from a clean clone.

## v0.5 Beta: Project Workflow

**Goal:** make regular student and contest use practical across platforms.

- Project explorer and templates
- Multiple build profiles; MSVC support
- Robust normalized diagnostics and Problems panel
- Test-case persistence, run-all, output diff, timing
- Session restore and autosave recovery
- Themes, settings, configurable shortcuts
- Windows/macOS CI and preview packages
- Performance instrumentation and accessibility baseline

**Gate:** all Must requirements implemented, migration tests established, no open Critical issues, beta packages pass clean-machine smoke tests.

## v1.0 Stable: Trustworthy Offline IDE

**Goal:** stable, documented, and distributable daily-use release.

- Stable manifest schema and migration policy
- Hardened atomic saves and external-change reconciliation
- Process-tree cleanup and output limiting on supported systems
- Complete offline help, third-party notices, and privacy statement
- Accessibility and high-DPI release pass
- Signed installers/packages where project infrastructure permits
- Performance budgets and >= 80% core line coverage
- Complete SRS traceability and release checklist

**Gate:** supported platform matrix passes; no unapproved Critical/High defects; recovery, uninstall, artifact checksum, and offline acceptance tests pass.

## v1.1: Workflow Polish

- Split editor and detachable tool panels
- Project-wide symbol/text search
- More project templates and template variables
- Test groups, tags, and result history for the current session
- Improved compiler installation guidance
- Localization infrastructure

## v1.5: Deeper C++ Assistance

- Optional local `clangd` integration behind an application port
- Completion, hover, go-to-definition, and rename when `clangd` is installed
- `compile_commands.json` generation
- Optional local debugger adapter research (not promised until security/UX prototype passes)

## v2.0 Candidates

- Multi-target projects and CMake project import
- Plugin API with strict compatibility/version model
- Optional indexed symbol cache, potentially SQLite-backed
- Classroom configuration bundles and read-only managed defaults
- Sandboxed execution helpers where the host OS provides a reliable primitive

## Explicit Non-Goals for v1

- Cloud sync, accounts, telemetry, collaboration, or online judging
- A bundled package manager
- Full CMake language editing or arbitrary build-system emulation
- A full debugger
- Running hostile code securely
- Reimplementing a language server

## Roadmap Governance

Features move into a milestone only with a requirement, owner, UX states, dependency/licensing review, test approach, and maintenance assessment. Community demand informs priority but does not override privacy, performance, or reliability budgets.
