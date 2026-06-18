# Software Requirements Specification

**Product:** OfflineCode Studio
**Version:** 1.0 draft
**Status:** Baseline for implementation

## 1. Introduction

### 1.1 Purpose

This document specifies the requirements for a cross-platform desktop IDE focused on offline C++ editing, compilation, execution, project management, and competitive programming.

### 1.2 Scope

The product shall provide a cohesive local workflow from creating or opening source files to observing compilation diagnostics and program output. It shall not require authentication, a server, or network access. Version 1.0 is not intended to replace a full language-server IDE, package manager, debugger, or hostile-code sandbox.

### 1.3 Definitions

| Term | Meaning |
|---|---|
| Project | Directory with an `offlinecode.json` manifest |
| Toolchain | Compiler family, executable, version, and supported flags |
| Build profile | Named standard, optimization, debug, warning, and custom compiler options |
| Test case | Standard input, expected output, comparison mode, and execution limits |
| Workspace state | Machine-local open tabs, selection, panel layout, and recent projects |

## 2. Stakeholders and Users

- Students need clear errors, simple defaults, and low setup overhead.
- Competitive programmers need repeatable tests, timing, and keyboard-driven flows.
- General developers need predictable files, compiler control, and platform-native behavior.
- Educators need offline deployability, safe defaults, and reproducible project templates.
- Contributors need modular boundaries, tests, documentation, and approachable issues.

## 3. Assumptions and Constraints

- The host provides a supported C++ compiler; compiler bundling is distribution-specific.
- Qt 6 and QScintilla are application dependencies.
- The implementation uses C++17, CMake, STL, and `std::filesystem`.
- Files may be modified outside the application.
- Programs launched by the user may hang, crash, or produce excessive output.
- Full operation after installation must not depend on network availability.

## 4. Functional Requirements

Priority uses MoSCoW: Must, Should, Could.

### 4.1 Application and Session

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-001 | The application shall start without network access. | Must | Blocking network calls are absent from startup and offline smoke test passes. |
| FR-002 | The application shall restore the last window geometry and panel layout. | Should | Clean exit followed by start restores valid visible geometry. |
| FR-003 | The application shall show a first-run screen with project actions and compiler status. | Must | Fresh settings produce the welcome screen and discovery result. |
| FR-004 | The application shall maintain a bounded recent-project list. | Should | Valid entries open; missing entries can be removed; list never exceeds configured limit. |
| FR-005 | The application shall offer recovery for unsaved editor snapshots after abnormal exit. | Should | Forced termination followed by launch presents timestamped recoverable content. |

### 4.2 File Editing

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-101 | Users shall create, open, edit, save, Save As, and close UTF-8 text files. | Must | File round-trip preserves supported content and line endings per chosen policy. |
| FR-102 | The editor shall highlight C++17 syntax and show line numbers. | Must | Representative C++ tokens have configured styles and line numbers track scrolling. |
| FR-103 | The editor shall support undo/redo, search/replace, indentation, brace matching, and folding. | Must | Keyboard and menu tests cover each operation. |
| FR-104 | Multiple files shall be open in tabs with visible dirty state. | Must | Changes add a marker; successful save clears it. |
| FR-105 | Closing dirty files shall require Save, Discard, or Cancel. | Must | No dirty buffer is lost without an explicit discard. |
| FR-106 | External file changes shall trigger Reload, Compare, or Keep actions. | Should | A disk edit is detected and the in-memory buffer is not silently overwritten. |
| FR-107 | Large or binary files shall fail gracefully. | Must | Binary detection avoids corruption; files above the warning threshold require confirmation. |
| FR-108 | Editor font, tab width, spaces/tabs, wrapping, and theme shall be configurable. | Should | Settings persist and apply to existing/new editors. |

### 4.3 Project Management

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-201 | Users shall create a project from an included template. | Must | Creation writes a valid manifest and source files or leaves the target unchanged on failure. |
| FR-202 | Users shall open a project by manifest or directory. | Must | Valid projects render; invalid manifests produce field-specific errors. |
| FR-203 | The explorer shall display project files and directories with refresh/filter actions. | Must | Created, renamed, and deleted files are reflected without restart. |
| FR-204 | Users shall add, rename, remove, and reveal project files. | Should | Operations confirm destructive effects and keep manifest sources synchronized. |
| FR-205 | Project configuration shall be portable and schema-versioned. | Must | Moving the directory retains relative settings; unknown future schemas are rejected safely. |
| FR-206 | The application shall prevent accidental path traversal from manifest-relative paths. | Must | `../` escaping the project root is rejected unless the user explicitly imports an external file. |

### 4.4 Toolchain and Build

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-301 | The application shall discover supported GCC, Clang, Apple Clang, and MSVC installations. | Must | Available reference toolchain is identified with executable and version. |
| FR-302 | Users shall select and validate a compiler executable manually. | Must | Invalid or incompatible executables produce actionable messages. |
| FR-303 | Users shall choose C++ standard, warnings, optimization, debug symbols, and extra arguments. | Must | Previewed and executed argument lists match the selected profile. |
| FR-304 | Build shall save or explicitly exclude dirty source files before invoking a compiler. | Must | Build never silently compiles a stale version while presenting newer editor content. |
| FR-305 | Build output shall stream to a panel without blocking the UI. | Must | UI remains interactive during a 30-second compiler process. |
| FR-306 | Diagnostics shall be normalized and link to file, line, and column where available. | Must | GCC/Clang/MSVC fixtures produce equivalent normalized records. |
| FR-307 | Users shall cancel an active build. | Must | Cancellation updates UI promptly and no compiler child remains after the grace period. |
| FR-308 | Command construction shall not invoke a shell. | Must | Paths and adversarial flags are passed as discrete process arguments. |

### 4.5 Program Execution

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-401 | Users shall run the most recent successful artifact. | Must | Run is disabled before success and launches the matching artifact afterward. |
| FR-402 | Users shall provide stdin and see stdout/stderr, exit code, and duration. | Must | Fixture program verifies all four values. |
| FR-403 | Users shall stop a running program. | Must | Process exits after terminate/kill policy and state returns to idle. |
| FR-404 | Execution shall enforce a configurable timeout and output limit. | Must | Infinite-loop and infinite-output fixtures terminate with distinct statuses. |
| FR-405 | The working directory and command-line arguments shall be configurable. | Should | Child observes configured directory and exact arguments. |
| FR-406 | The UI shall disclose that local execution is not sandboxed. | Must | First run and settings/run surfaces contain the warning. |

### 4.6 Competitive Programming

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-501 | Users shall create, edit, duplicate, order, and delete test cases. | Must | Operations persist and survive project reopen. |
| FR-502 | Users shall run one case or all enabled cases. | Must | Results map to the correct case and retain deterministic order. |
| FR-503 | Comparison modes shall include exact, trailing-whitespace-insensitive, and token modes. | Must | Unit fixtures cover line endings, whitespace, and token mismatches. |
| FR-504 | Results shall show pass/fail, duration, exit status, stderr, timeout, and truncation. | Must | Each terminal state has a distinct visible and accessible label. |
| FR-505 | Users shall configure per-case timeout and a project default. | Should | Per-case value overrides project default with validation. |
| FR-506 | Project templates shall include contest-ready C++ boilerplate. | Could | Template produces a buildable source with fast I/O setup. |

### 4.7 Settings, Help, and Accessibility

| ID | Requirement | Priority | Acceptance criterion |
|---|---|---|---|
| FR-601 | Settings shall persist locally and support scoped reset. | Must | Restart retains values; page reset leaves unrelated pages unchanged. |
| FR-602 | The application shall provide light, dark, and system themes. | Should | Theme applies without restart and preserves syntax readability. |
| FR-603 | Primary actions shall be keyboard-accessible and shortcuts configurable. | Must | Keyboard-only end-to-end build/run flow passes. |
| FR-604 | Controls shall expose accessible names, roles, and focus state. | Must | Automated inspection plus manual screen-reader checklist passes. |
| FR-605 | Offline help shall document setup, shortcuts, manifests, build errors, and safety. | Should | Help opens with networking disabled and search returns packaged content. |
| FR-606 | The About dialog shall show version, license, Qt, QScintilla, and compiler information. | Must | Installed build reports reproducible version metadata. |

## 5. Non-Functional Requirements

| ID | Requirement | Verification |
|---|---|---|
| NFR-001 | Cold startup shall be <= 1.5 s P95 on the reference system. | 30-run benchmark after OS reboot/warm-up policy. |
| NFR-002 | Idle resident memory shall be <= 150 MB with one small project. | Platform memory measurement after 60 seconds idle. |
| NFR-003 | UI input latency shall be <= 16 ms P95 for a 10k-line file. | Instrument key-to-paint latency. |
| NFR-004 | The application shall support Windows 10/11, Ubuntu 22.04+, and macOS 13+. | CI plus release-candidate manual matrix. |
| NFR-005 | A recoverable infrastructure failure shall not crash or silently lose saved data. | Fault-injection tests for read/write/process errors. |
| NFR-006 | Canonical project data shall remain local unless the user invokes an OS sharing action. | Network-disabled tests and architecture review. |
| NFR-007 | Core domain and application services shall achieve >= 80% line and >= 70% branch coverage. | Coverage job on Linux. |
| NFR-008 | Release builds shall have no Critical/High static-analysis findings without documented waiver. | CodeQL/clang-tidy review gate. |
| NFR-009 | Settings and manifest migrations shall preserve backward compatibility across stable 1.x releases. | Golden-file migration suite. |
| NFR-010 | User-visible errors shall state what failed and at least one recovery action when one exists. | UX review and error catalog test. |
| NFR-011 | Reproducible builds shall embed a semantic version and commit identifier. | CI artifact inspection. |
| NFR-012 | Source and documentation shall use an approved license and third-party notices. | Release checklist. |

## 6. External Interfaces

### 6.1 User Interface

The primary interface is a Qt Widgets main window containing menu/toolbar, project explorer, tabbed editor, bottom tool panel, and status bar. Detailed behavior is specified in `UI_WIREFRAMES.md`.

### 6.2 Files

- UTF-8 source and text files; BOM is detected and preserved by policy.
- `offlinecode.json` project manifest with integer schema version.
- Test-case JSON metadata plus optional `.in`/`.out` payload files.
- Machine-local preferences through `QSettings`.
- Diagnostic logs with rotating size limits and source-content exclusion.

### 6.3 Processes

Compilers and user programs are launched with `QProcess`, explicit executable/argument lists, environment, and working directory. stdout/stderr are consumed asynchronously. Process groups/job objects are used where supported to clean up descendants.

## 7. Data Requirements

Project name is non-empty and at most 100 Unicode scalar values. Source paths are relative, normalized, unique under platform case rules, and cannot escape the project root. Timeout is 100-600000 ms; output limit is 1 KiB-100 MiB. Unknown manifest keys are preserved when feasible, while unknown required schema versions are rejected.

## 8. Acceptance and Release Criteria

Version 1.0 is accepted when all Must requirements pass on the supported platform matrix; no open Critical or High known issue lacks explicit release approval; installers pass clean-machine smoke tests; accessibility and performance budgets pass; and documentation, licensing, checksums, and rollback notes accompany signed release artifacts.

## 9. Traceability

Tests use requirement IDs in names or metadata, for example `FR_404_times_out_infinite_process`. Pull requests changing an ID must update the SRS, implementation tests, and relevant release notes in one change.
