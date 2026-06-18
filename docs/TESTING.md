# Testing Strategy

## 1. Objectives

Testing protects source data, process lifecycle correctness, cross-platform behavior, user responsiveness, and stable project formats. Tests are deterministic, offline, and layered according to risk.

## 2. Test Pyramid

| Level | Scope | Tools | Target |
|---|---|---|---|
| Unit | Domain invariants, parsers, comparison modes, state machines | Qt Test or Catch2, fakes | Fast; majority of suite |
| Contract | Every compiler/repository/process adapter against shared expectations | Qt Test, fixtures | All implementations |
| Integration | Real temp files, JSON, `QProcess`, compiler fixtures | Qt Test, CTest | Key failure paths |
| GUI | Widget state, shortcuts, primary flows | Qt Test/QTest | Focused critical paths |
| System | Installed package, real compiler, offline behavior | CTest/scripts/manual | Release candidates |
| Exploratory | UX, accessibility, unusual platform interactions | Checklist | Every beta/stable RC |

## 3. Quality Gates

- All tests pass on Linux, Windows, and macOS CI.
- Core domain/application line coverage >= 80%; branch coverage >= 70%.
- No sanitizer failures in Linux debug jobs.
- No Critical/High CodeQL or clang-tidy issue without a reviewed waiver.
- No known Critical defect; High defects require explicit release-blocker review.
- Performance budgets pass on controlled reference hardware before stable release.
- Manifest changes include backward migration and future-version rejection tests.

Coverage is evidence, not a substitute for boundary and failure testing.

## 4. Representative Test Cases

| ID | Requirement | Scenario | Expected result |
|---|---|---|---|
| TC-001 | FR-101 | Save UTF-8 C++ text to a new file | Exact content is durable; dirty state clears |
| TC-002 | FR-105 | Close three dirty tabs | One review dialog lists all; Cancel loses nothing |
| TC-003 | FR-106 | Modify open file externally | User chooses Reload/Compare/Keep; no silent overwrite |
| TC-004 | FR-201 | Template write fails halfway | Target is rolled back to pre-create state |
| TC-005 | FR-205 | Load schema v0 fixture | Migration produces valid v1 model and backup |
| TC-006 | FR-206 | Source path is `../../secret.cpp` | Manifest rejected with field-specific path error |
| TC-007 | FR-301 | Compiler probe hangs | Probe times out; UI continues; candidate marked invalid |
| TC-008 | FR-305 | Compiler emits 10,000 lines slowly | Output streams; editor remains responsive |
| TC-009 | FR-306 | GCC/Clang/MSVC error fixtures | Severity/file/line/column/message normalize correctly |
| TC-010 | FR-307 | Cancel near natural build exit | Exactly one terminal result; no process remains |
| TC-011 | FR-308 | Source path contains spaces/metacharacters | Exact discrete arguments reach compiler; no shell executes |
| TC-012 | FR-402 | Child writes interleaved stdout/stderr and exits 7 | Both streams retained, status 7 and duration shown |
| TC-013 | FR-404 | Infinite-loop child with 200 ms timeout | Result is TimedOut and process tree is cleaned |
| TC-014 | FR-404 | Child writes infinite output | Retained output capped, process drained, truncation shown |
| TC-015 | FR-503 | Expected CRLF, actual LF in token mode | Passes; exact mode reports mismatch |
| TC-016 | FR-503 | Different trailing blank lines | Result follows selected comparison policy only |
| TC-017 | FR-504 | Program crashes during test case | Case shows Runtime Error, exit detail, and stderr |
| TC-018 | FR-601 | One corrupt settings key | That key defaults; unrelated settings survive |
| TC-019 | FR-603 | Keyboard-only create/edit/build/run | Workflow completes with visible focus |
| TC-020 | FR-001 | Block all network access | Startup and all documented v1 workflows function |

## 5. Platform Matrix

| Platform | Compiler used to build app | User-code compiler fixtures | CI | Manual RC |
|---|---|---|---:|---:|
| Ubuntu 22.04/24.04 x64 | GCC and Clang | GCC, Clang | Yes | Yes |
| Windows 10/11 x64 | MSVC 2022 | MSVC, MinGW where supported | Yes | Yes |
| macOS 13+ Apple Silicon | Apple Clang | Apple Clang | Yes | Yes |
| macOS 13+ Intel | Apple Clang | Apple Clang | Best effort | Yes before stable |

Qt/QScintilla versions use a minimum supported pair and the latest tested compatible pair.

## 6. Test Data

- Golden manifests for valid v1, old schema, malformed JSON, wrong types, unknown future schema, traversal, Unicode, and large arrays.
- Compiler-output fixtures captured from supported compiler families, scrubbed of personal paths.
- Tiny helper executables: echo, nonzero exit, stderr, crash, sleep, infinite output, child spawner, argument printer.
- Text fixtures: empty, UTF-8, BOM, LF, CRLF, mixed endings, NUL/binary, 5 MB and 50 MB.

Fixtures are generated or licensed for redistribution and must not contain private user source.

## 7. Performance Testing

Reference system: documented four-core CPU, 8 GB RAM, SSD, clean release build. Record OS, CPU, Qt version, commit, power mode, and sample count.

- Startup: 5 warm-ups then 30 cold-process samples; report median/P95.
- Memory: one 10k-line project, idle 60 seconds; report resident/private bytes.
- Editor latency: replay 500 edits and measure input event to paint completion.
- Project scan: 1k, 10k, and 50k file synthetic trees; ensure cancellation.
- Output: 1 MB, 10 MB, and unbounded streams; measure UI responsiveness and cap behavior.

CI detects large regressions; controlled hardware decides release gates.

## 8. Accessibility Testing

Test keyboard navigation, focus order/visibility, high contrast, 200% scale, theme contrast, reduced motion, and screen-reader labels/announcements. Use NVDA on Windows, VoiceOver on macOS, and Orca where supported on Linux. Automated accessible-property checks run in GUI tests; human checks remain required.

## 9. Security and Robustness Testing

- Fuzz manifest and compiler-diagnostic parsers.
- Test symlinks, junctions, case variants, long paths, permission failures, full disk, read-only media, and concurrent external edits.
- Pass adversarial path/argument strings to process adapters without shell invocation.
- Confirm logs exclude source, stdin, stdout, environment secrets, and unredacted home paths where avoidable.
- Confirm child cleanup on timeout, cancellation, app close, and parent crash where the OS permits.

## 10. Bug Lifecycle

Every defect includes environment, minimal reproduction, expected/actual behavior, severity, logs without private source, regression status, and requirement/test linkage. A fix adds a failing test first when practical. Closed Critical/High issues receive targeted release-candidate verification.

## 11. Release Test Checklist

- Build from a clean clone with documented commands.
- Install, launch, create project, edit, build, run, test, close, reopen, uninstall.
- Repeat with networking disabled.
- Verify version/About/licenses/checksums.
- Exercise missing compiler, broken manifest, unwritable directory, timeout, and crash recovery.
- Verify no user project or preference files are removed by uninstall.
- Archive signed test report with the release candidate.
