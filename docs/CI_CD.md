# CI/CD Recommendations

## Pull Request Pipeline

1. **Style:** `clang-format --dry-run`, Markdown/YAML lint, CMake format where adopted.
2. **Build and test:** Linux GCC/Clang, Windows MSVC, macOS Apple Clang using pinned Qt and QScintilla versions.
3. **Analysis:** clang-tidy on changed translation units and CodeQL on push/PR schedule.
4. **Sanitizers:** Linux Clang ASan+UBSan; separate TSan job only for targeted concurrency tests.
5. **Coverage:** Linux Debug, upload summary, enforce core thresholds without blocking on generated/Qt glue.
6. **Architecture:** reject Qt includes in `src/domain` and forbidden layer dependencies.

Use dependency caches keyed by OS, architecture, compiler, Qt/QScintilla versions, and lock metadata. Never cache release artifacts or signing material.

## Release Pipeline

Trigger on annotated `v*` tags after protected review:

1. Verify tag matches CMake version and `CHANGELOG.md` contains the version.
2. Rebuild from clean source in pinned environments.
3. Run complete tests and install-tree smoke tests offline.
4. Deploy Qt/QScintilla and produce ZIP/installer, DMG, and Linux package artifacts.
5. Generate SPDX/CycloneDX SBOM, third-party notices, SHA-256 checksums, and provenance.
6. Sign/notarize through protected GitHub Environments with least-privilege, short-lived credentials where possible.
7. Draft GitHub Release from the matching release-note section; require maintainer approval to publish.

## Branch and Supply-Chain Policy

- Protect `main`: pull request, one or two reviews, passing required checks, resolved conversations, no force pushes.
- Pin third-party actions to immutable commit SHAs and review updates through Dependabot/Renovate.
- Grant workflows minimal `permissions`; default to `contents: read`.
- Do not expose secrets to fork pull requests or run fork code in privileged `pull_request_target` jobs.
- Retain release artifacts and attestations; expire ordinary debug artifacts quickly.
- Use concurrency cancellation for superseded branch builds, never for an active release.

## Suggested Required Checks

`format`, `linux-gcc`, `linux-clang`, `windows-msvc`, `macos-clang`, `unit-tests`, `integration-tests`, `architecture`, `codeql`, and `license-scan`.

## Versioning and Changelog

Use Semantic Versioning. Commit messages follow Conventional Commits; a release tool may propose changelog entries, but maintainers edit user-facing notes. Breaking manifest changes require a major release after 1.0 and an explicit migration path.

## Current Workflow Scope

The included `.github/workflows/ci.yml` is a conservative baseline that validates CMake configuration and documentation without pretending dependencies are universally available. Once the Qt/QScintilla package strategy is selected, replace placeholders with pinned installation steps and activate the full matrix above.
