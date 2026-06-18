# Contributing to OfflineCode Studio

Thank you for helping build a fast, private C++ learning tool. Contributions of code, tests, design, documentation, and reproducible bug reports are welcome.

## Before You Start

- Search existing issues and discussions.
- For behavior changes, open or claim an issue before substantial work.
- Start with a `good first issue` if the architecture is unfamiliar.
- Keep pull requests focused; unrelated cleanup belongs separately.

Participation is governed by [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). Security reports must follow [SECURITY.md](SECURITY.md), not a public issue.

## Development Setup

Follow [docs/BUILDING.md](docs/BUILDING.md). A core-only configure is available when Qt/QScintilla is not installed:

```bash
cmake -S . -B build -G Ninja -DOFFLINECODE_BUILD_GUI=OFF
cmake --build build
ctest --test-dir build --output-on-failure
```

## Workflow

1. Fork and create a branch such as `fix/diagnostic-column` or `feat/token-comparison`.
2. Add or update tests before changing behavior where practical.
3. Follow module boundaries in `docs/ARCHITECTURE.md`.
4. Run formatting, build, tests, and relevant manual checks.
5. Use a Conventional Commit subject and complete the pull request template.

## Code Standards

- C++17; RAII and value semantics by default.
- `std::filesystem::path` for filesystem paths and `std::chrono` for durations.
- No Qt dependency in `src/domain`.
- No shell command strings for compiler or program execution.
- Explicit ownership; avoid raw owning pointers and mutable global state.
- Keep interfaces narrow and inject infrastructure through constructors.
- Comments explain constraints or intent, not syntax.
- User-facing strings are ready for translation and accessible presentation.

Run the configured formatter before submitting. New warnings are not accepted.

## Tests and Documentation

Bug fixes should include a regression test. New ports/adapters need contract tests; manifest changes need golden migration fixtures. Update the SRS/SDD when requirements or boundaries change and `CHANGELOG.md` for user-visible behavior.

## Commit Style

```text
<type>(optional-scope): <imperative summary>
```

Common types: `feat`, `fix`, `docs`, `test`, `refactor`, `perf`, `build`, `ci`, and `chore`. Use `!` and a `BREAKING CHANGE:` footer only for actual compatibility breaks.

## Pull Request Review

Reviewers prioritize data safety, cancellation/lifetime correctness, process argument safety, cross-platform behavior, accessibility, tests, and architecture boundaries. Address or explicitly resolve every conversation. Maintainers may squash merge a clean PR.

## Issue Claiming

Comment before starting an unassigned issue. A maintainer may assign it and clarify acceptance criteria. If there is no update for two weeks, the issue may be made available again so contribution does not stall.
