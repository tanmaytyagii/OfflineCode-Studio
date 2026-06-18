# Professional Repository Structure

```text
OfflineCode-Studio/
|-- .github/
|   |-- ISSUE_TEMPLATE/
|   |   |-- bug_report.yml
|   |   |-- feature_request.yml
|   |   `-- config.yml
|   |-- workflows/
|   |   `-- ci.yml
|   |-- labels.yml
|   `-- PULL_REQUEST_TEMPLATE.md
|-- cmake/
|   `-- FindQScintillaQt6.cmake
|-- docs/
|   |-- ARCHITECTURE.md
|   |-- BUILDING.md
|   |-- CI_CD.md
|   |-- CONVENTIONAL_COMMITS.md
|   |-- DATABASE_DECISION.md
|   |-- FEATURE_PLAN.md
|   |-- FIRST_TIME_CONTRIBUTOR_ISSUES.md
|   |-- GITHUB_LABELS.md
|   |-- KNOWN_ISSUES.md
|   |-- RELEASE_NOTES.md
|   |-- ROADMAP.md
|   |-- SDD.md
|   |-- SHOWCASE.md
|   |-- SRS.md
|   |-- TESTING.md
|   `-- UI_WIREFRAMES.md
|-- examples/
|   `-- hello-world/
|       |-- main.cpp
|       `-- offlinecode.json
|-- resources/
|   |-- icons/
|   `-- README.md
|-- src/
|   |-- app/                         # Composition root
|   |-- application/
|   |   |-- interfaces/              # Ports implemented by infrastructure
|   |   `-- services/                # Use-case coordination
|   |-- domain/
|   |   |-- entities/                # Framework-independent models
|   |   `-- value_objects/           # Validated immutable-ish values
|   |-- infrastructure/
|   |   |-- compiler/                # GCC/Clang/MSVC strategies
|   |   `-- filesystem/              # Safe filesystem adapters
|   `-- presentation/
|       `-- main_window/             # Qt view shell
|-- tests/
|   |-- integration/
|   `-- unit/
|-- .clang-format
|-- .editorconfig
|-- .gitignore
|-- CHANGELOG.md
|-- CMakeLists.txt
|-- CMakePresets.json
|-- CODE_OF_CONDUCT.md
|-- CONTRIBUTING.md
|-- LICENSE
|-- README.md
`-- SECURITY.md
```

## Ownership Rules

- `src/domain` has no Qt includes and no knowledge of files or processes.
- `src/application` depends on domain and owns interfaces and use cases.
- `src/infrastructure` implements interfaces using Qt/STL/OS facilities.
- `src/presentation` owns widgets and controllers, not product policy.
- `src/app` is the only production composition root.
- Unit tests mirror module ownership; integration tests cross real boundaries deliberately.
- Generated build output never enters source control.

## Recommended Additions as the Project Grows

Add `resources/themes`, `resources/templates`, `resources/help`, and `resources/translations` only with their first real assets. Add `packaging/windows`, `packaging/macos`, and `packaging/linux` when release prototypes exist. Add an `adr/` directory when architectural decisions outgrow the SDD; number records and never rewrite accepted history.
