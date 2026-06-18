# Known Issues and Limitations

This is a realistic pre-1.0 planning register, not a claim that all listed features are already implemented. IDs should become GitHub issues as their owning milestone begins.

| ID | Severity | Issue | Workaround | Planned fix |
|---|---|---|---|---|
| KI-001 | High | Cancelling a build may leave compiler descendants alive when the compiler launches helper processes on Windows. | End descendants from Task Manager; avoid cancelling during link. | Assign builds to a Windows Job Object and terminate the job after a graceful timeout; add child-spawner integration test. |
| KI-002 | High | A file changed both in the editor and externally cannot yet be merged automatically. Choosing either version can discard the other after confirmation. | Use Compare and save one version under a new name before reconciling. | Add three-way merge using last-saved content, retain recovery snapshots, and test conflict decisions. |
| KI-003 | Medium | MSVC diagnostics containing localized text may not parse into the Problems panel. Raw output remains correct. | Use the Build tab or configure English compiler output. | Parse stable structural prefixes independent of message language and expand localized fixture corpus. |
| KI-004 | Medium | File watchers can coalesce rapid rename/delete/create sequences, leaving the explorer stale until refresh on network-mounted folders. | Use Refresh Project. | Debounce events, reconcile affected subtrees against a filesystem snapshot, and add network-filesystem simulation tests. |
| KI-005 | Medium | Opening files above 20 MB may temporarily increase memory and reduce editor responsiveness. | Use an external large-file viewer or open read-only. | Add streaming detection, read-only large-file mode, deferred highlighting, and a configurable threshold. |
| KI-006 | Medium | Token comparison treats all values as text; floating-point tolerance is unsupported. | Pre-round output in the solution or use an external checker. | Add an explicit numeric-tolerance comparator with absolute/relative bounds and clear mismatch reporting. |
| KI-007 | Medium | Program timeout cannot guarantee descendant cleanup on every Unix setup when child processes detach into a new session. | Do not run untrusted or intentionally daemonizing programs. | Add platform helper using process groups/cgroups where available and document the remaining OS boundary. |
| KI-008 | Low | At 200% scaling, long compiler paths may truncate in the Toolchain dialog without an inline expansion. | Hover for tooltip or widen the dialog. | Use elided text with accessible full-path description and Copy Path action; add high-DPI layout test. |
| KI-009 | Low | Restoring a session across monitor-layout changes may place a floating panel partly off-screen. | Reset Window Layout from View. | Clamp all restored rectangles to the union of available screens and migrate older geometry keys. |
| KI-010 | Low | Mixed line endings are normalized to the selected document line ending on save rather than preserved per line. | Review the diff before committing or choose the intended line ending. | Detect mixed endings, warn once, and offer Preserve Mixed/Normalize choices; add round-trip fixtures. |

## Product Limitations

- The application does not provide a hostile-code sandbox.
- A compatible local compiler is normally required and is not automatically downloaded.
- v1 does not promise a debugger, language server, Git client, package manager, cloud sync, collaboration, or online judge.
- Compiler diagnostics are best-effort normalized; raw output is the source of truth.
- QScintilla availability and native packaging vary by platform.

No stable release should ship with an unresolved High issue involving data loss or unsafe file writes. Other High issues require a documented owner, workaround, and release decision.
