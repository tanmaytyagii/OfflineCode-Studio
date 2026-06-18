# Portfolio and Career Showcase

Use claims that match the actual milestone demonstrated in the repository. Do not present roadmap items or target metrics as completed work.

## Resume Bullet Points: Current Foundation

- Architected and prototyped **OfflineCode Studio**, a cross-platform C++17 desktop IDE foundation using Qt 6, QScintilla, CMake, STL, and `std::filesystem`, with explicit domain, application, infrastructure, and presentation layers.
- Designed dependency-inverted compiler and process contracts, a validated project aggregate, and a build lifecycle coordinator with cancellation and unit tests, keeping core logic buildable without GUI dependencies.
- Authored a production-oriented engineering package including traceable SRS requirements, class and sequence diagrams, test strategy, security policy, CI baseline, contributor workflows, release plan, and 20 mentored starter issues.

## Resume Bullet Points: Use After v1 Verification

Replace bracketed values with measured CI/release results; remove any bullet whose evidence is not public.

- Built a fully offline C++ desktop IDE for Windows, Linux, and macOS, integrating Qt 6/QScintilla editing with asynchronous GCC, Clang, and MSVC compilation and execution.
- Applied MVC, SOLID, Strategy, Repository, Observer, Command, and State patterns across [N]+ tested C++ classes, achieving [X]% core coverage and zero GUI blocking during compiler/process workloads.
- Engineered atomic project persistence, external-change detection, autosave recovery, timeout/output enforcement, and shell-free process invocation to protect source data and local workflows.
- Delivered competitive-programming test automation with [N] persisted cases, deterministic output comparison, runtime/timeout reporting, and first-mismatch diagnostics.
- Established a three-platform CI/CD pipeline with warnings-as-errors, sanitizers, static analysis, packaging, SBOM/checksums, and clean-machine offline smoke tests.

## One-Line Portfolio Description

OfflineCode Studio is a lightweight, fully offline C++ IDE that combines a QScintilla editor, portable projects, local compiler integration, safe process control, and competitive-programming test workflows in a modular Qt 6 application.

## Portfolio Project Description

### OfflineCode Studio - Offline C++ Development, Designed as a Product

I designed OfflineCode Studio to answer a focused question: how much of the everyday C++ edit-build-run loop can a native application provide without accounts, cloud services, or heavyweight extension infrastructure?

The project uses C++17, Qt 6, QScintilla, CMake, STL, and `std::filesystem`. Its architecture combines MVC at the GUI boundary with layered dependency inversion: framework-independent domain models describe projects and build profiles; application services own build, run, and test-case workflows; infrastructure adapters handle JSON, files, compilers, processes, and settings; Qt views render state and user intent.

The technically interesting work is at system boundaries. Compiler output differs across GCC, Clang, and MSVC, so adapters retain raw output while producing normalized diagnostics. Build and run tasks are asynchronous, cancellable, and guarded against stale callbacks. Project files are schema-versioned, human-readable, and written atomically. Program execution enforces usability limits but clearly does not claim to sandbox hostile code.

The repository treats engineering communication as part of the product: requirements have acceptance IDs, the SDD documents ownership and runtime flows, tests cover failure paths, and contributor issues include scope and review criteria. The result is both a practical desktop-tool roadmap and a visible demonstration of C++ design, GUI engineering, file safety, process integration, testing, and release discipline.

## LinkedIn Showcase Post: Foundation Launch

**Introducing OfflineCode Studio: a native, fully offline C++ IDE project**

I have been building the engineering foundation for OfflineCode Studio, a lightweight desktop environment for students, competitive programmers, and developers who want a focused local C++ workflow.

The goal is straightforward: edit, organize, compile, run, and test C++ projects without an account, cloud dependency, or network connection.

The stack is C++17, Qt 6, QScintilla, CMake, STL, and `std::filesystem`. Under the UI, I am using layered architecture with MVC and dependency inversion so project rules remain independent from widgets, filesystems, and compiler processes. Toolchains fit behind strategies, project persistence behind repositories, and asynchronous build/run operations have explicit lifecycle state.

The first public foundation includes:

- a compilable Qt-free core and tested build coordinator;
- a Qt/QScintilla application shell;
- SRS and software design documentation with class/sequence diagrams;
- an offline-first JSON project format decision;
- test, accessibility, security, CI/CD, and release plans;
- contributor templates and 20 scoped first issues.

One design boundary matters enough to say plainly: the application can enforce timeouts and output limits, but it is not a sandbox for untrusted programs.

I built this as a software-engineering portfolio project, not just a UI demo. The next milestones connect safe file editing, real compiler adapters, diagnostics, and competitive-programming test cases into the shell.

Repository: `[GitHub URL]`

#cplusplus #qt #cmake #opensource #softwareengineering #desktopdevelopment

## Interview Pitch (60 Seconds)

OfflineCode Studio is my C++17/Qt 6 portfolio project: a lightweight IDE designed to work entirely offline. I chose it because it combines GUI state, filesystem safety, asynchronous processes, compiler-specific parsing, persistence, and cross-platform release engineering in one coherent product.

The design uses a pure domain layer, application use cases behind ports, infrastructure adapters for JSON/files/processes, and MVC-based Qt presentation. That lets me test build and project policy without starting a GUI and add GCC, Clang, or MSVC behavior through strategies. I paid particular attention to hard edges: atomic writes, external changes, stale asynchronous callbacks, cancellation races, output limits, and honest security boundaries. The repository also includes requirements traceability, release gates, CI, and contributor onboarding because maintainability is part of the project goal.

## Interview Discussion Prompts

- **Why no database?** The canonical data is small, hierarchical, portable, and diffable. JSON plus `QSettings` is simpler; SQLite is reserved for a future measured indexing need.
- **Why not call the compiler with `system()`?** Shell strings are fragile and unsafe with user-controlled paths. `QProcess` accepts an executable and discrete arguments and supports asynchronous lifecycle control.
- **How is MVC used?** Widgets display view state and emit intent; controllers map actions to application services; domain/application types own policy.
- **What was deliberately excluded?** Cloud features, hostile-code sandboxing, a debugger, package management, and reimplementing language-server behavior.
- **How do you test OS integrations?** Ports use fakes in unit tests, shared contract tests apply to adapters, and integration helpers exercise real files and child processes per platform.

## Suggested Portfolio Screens

Capture these only when the implemented behavior matches:

1. Main workspace with project explorer, C++ editor, Problems panel, and status bar.
2. Compiler diagnostic selected beside the highlighted source line.
3. Competitive-programming test run with pass, mismatch, timeout, and duration states.
4. Architecture diagram beside a passing three-platform CI run.
5. Settings/toolchain screen showing explicit offline and execution-safety messaging.
