# Detailed Feature Implementation Plan

Each phase ends in a demonstrable vertical slice. Estimates are relative engineering days for one developer and should be recalibrated after the first milestone.

## Phase 0: Foundation (5-7 days)

**Deliverables:** CMake targets, module directories, Qt shell, logging, formatting/static-analysis config, CI, test harness, version metadata.

1. Create domain/application/infrastructure/presentation libraries with enforced dependency direction.
2. Add `QApplication` composition root and an empty `MainWindow` with persisted geometry.
3. Add compiler warnings, clang-format, clang-tidy, sanitizers, and coverage options.
4. Add fake filesystem/process ports and first unit test.
5. Establish error/result types, naming conventions, and Definition of Done.

**Exit:** Clean configure/build/test on all CI platforms; application starts offline and presents an empty shell.

## Phase 1: Editor Core (8-12 days)

**Deliverables:** QScintilla wrapper, tabs, file open/save, C++ lexer, search, dirty-state safeguards.

1. Implement `SourceDocument` independently of widgets.
2. Wrap QScintilla configuration in `CodeEditor`; do not leak it into controllers.
3. Implement `DocumentController` and tab model.
4. Add UTF-8 and line-ending detection/preservation, atomic save, external-change detection.
5. Add syntax theme tokens, brace matching, folding, indentation, search/replace.
6. Add close-many unsaved dialog and autosave snapshots.

**Tests:** encoding fixtures, atomic-write failure, dirty transitions, external edits, GUI actions, large-file warning.

**Exit:** A user can safely edit several C++ files through keyboard and menu workflows.

## Phase 2: Projects and Persistence (7-10 days)

**Deliverables:** manifest schema, project templates, explorer, recent projects, session restore.

1. Implement `Project`, `BuildProfile`, manifest DTOs, validation, and schema migration registry.
2. Implement JSON repository with deterministic atomic writes and backup recovery.
3. Add transactional project creation from packaged templates.
4. Add lazy project tree, refresh/watcher coalescing, and file operations.
5. Add recent-project and workspace-state stores through `QSettings`.

**Tests:** golden manifests, invalid field paths, traversal rejection, migrations, symlinks, case-sensitive/case-insensitive behavior.

**Exit:** Projects are portable, diffable, and recover safely from invalid metadata.

## Phase 3: Toolchains and Compilation (10-15 days)

**Deliverables:** discovery, profiles, async build, raw output, normalized diagnostics, cancellation.

1. Define compiler capability, build request/result, observer, and handle contracts.
2. Implement bounded discovery and manual compiler validation.
3. Add GCC/Clang strategy, then MSVC strategy using shared contract fixtures.
4. Implement async process adapter with explicit args/environment/working directory.
5. Implement build state machine, output throttling, cancellation, artifact verification.
6. Add Problems panel and source navigation.

**Tests:** quoted paths, unusual Unicode paths, warning/error fixtures, missing compiler, process start failure, cancellation race, stale operation signal.

**Exit:** One action builds a project without UI blocking and links diagnostics to source.

## Phase 4: Run and Console (6-9 days)

**Deliverables:** program runner, stdin/stdout/stderr, timeout/output caps, stop, run configuration.

1. Generalize process lifecycle behind `IProcessRunner` while keeping compiler policy separate.
2. Implement stream draining, buffered display updates, and output retention cap.
3. Implement monotonic timeout and cross-platform descendant cleanup.
4. Add console panel, run configuration dialog, duration/exit presentation.
5. Disable Run when no artifact matches current successful build fingerprint.

**Tests:** echo, stderr, nonzero exit, crash, infinite loop, infinite output, spawn child, paths with spaces.

**Exit:** Programs execute predictably, the UI stays responsive, and terminal states are unambiguous.

## Phase 5: Competitive Programming (8-12 days)

**Deliverables:** test-case editor, persistence, run-one/run-all, diff, timing, templates.

1. Implement `TestCase`, comparison strategies, and result aggregation.
2. Store metadata separately from large `.in`/`.out` payloads.
3. Implement deterministic queue with cancel and progress.
4. Add exact, trailing-whitespace-insensitive, and token comparison with first mismatch.
5. Build three-pane test workspace and summary filters.
6. Add console-app and contest templates.

**Tests:** CRLF/LF, blank lines, Unicode, floating text as tokens (no numeric tolerance in v1), timeout, truncation, cancellation.

**Exit:** A user can build once and evaluate multiple persisted cases with trustworthy results.

## Phase 6: Product Hardening (10-15 days)

**Deliverables:** themes, shortcuts, settings, accessibility, recovery, performance, offline help.

1. Centralize color tokens and validate contrast in light/dark/system themes.
2. Implement shortcut conflict detection and reset.
3. Add accessible names/status announcements and keyboard-only flows.
4. Complete autosave recovery and crash-safe session handling.
5. Profile startup, project scan, editor latency, and memory; enforce budgets.
6. Package searchable help and third-party notices locally.

**Exit:** NFR performance/accessibility targets pass and no known High data-loss defect remains.

## Phase 7: Release Engineering (7-12 days)

**Deliverables:** installers/archives, update-independent release information, checksums, signing, release checklist.

1. Create platform CPack/deployment configurations.
2. Run clean-machine installation/uninstallation smoke tests.
3. Add protected tag workflow, SBOM, checksums, signatures, and provenance where supported.
4. Complete license audit and source archive verification.
5. Run SRS traceability, regression, exploratory, accessibility, and performance passes.

**Exit:** `v1.0.0` artifacts install, run entirely offline, and match documented hashes and version data.

## Definition of Done

A feature is done only when requirements and UX states are agreed; domain/application behavior has automated tests; infrastructure failures have tests; accessibility names and keyboard behavior exist; docs and release notes are updated; no new unsuppressed warnings or sanitizer failures exist; and CI passes on supported platforms.

## Risk Register

| Risk | Probability | Impact | Mitigation |
|---|---|---|---|
| QScintilla packaging differs by platform | High | High | Prototype CI/install early; pin tested versions; document compatible sources |
| Compiler output formats vary | High | Medium | Fixture corpus, best-effort parser, preserve raw output |
| Child process cleanup differs by OS | Medium | High | Job objects/process groups; integration fixtures; explicit limitations |
| Large output freezes UI | Medium | High | Drain continuously, batch paints, cap retention |
| File watcher event storms | Medium | Medium | Debounce/coalesce, refresh subtree, ignore own atomic rename |
| Scope expands toward full IDE | High | High | Maintain v1 exclusions and requirement priorities |
| Platform signing delays release | Medium | Medium | Separate unsigned CI artifacts from protected release process |

## Suggested Team Ownership

| Area | Primary | Reviewer focus |
|---|---|---|
| Domain/application | Core C++ engineer | invariants, API ownership, tests |
| Qt presentation | GUI engineer | accessibility, state consistency, platform behavior |
| Toolchains/processes | Systems engineer | security, cancellation, OS differences |
| Packaging/CI | Release engineer | reproducibility, signing, dependency licensing |
| Documentation/UX | Product contributor | clarity, offline help, requirement traceability |
