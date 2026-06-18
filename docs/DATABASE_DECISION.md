# Database Decision Record

**Status:** Accepted
**Decision:** Use JSON project manifests and `QSettings`; do not embed a database in v1.

## Context

OfflineCode Studio stores project configuration, recent projects, UI preferences, open tabs, and competitive-programming test cases. The data volume is small, access is local, and almost all data is loaded or saved as a complete aggregate. Users should be able to move a project directory, inspect its settings, and review changes in Git.

## Options Considered

| Option | Advantages | Costs |
|---|---|---|
| SQLite | Transactions, queries, indexing, robust concurrency | Binary state is harder to inspect/diff; migration and packaging overhead; unnecessary query model |
| JSON + QSettings | Portable, human-readable, diffable, simple deployment | Requires schema validation, careful atomic writes, no ad hoc querying |
| One custom text format | Small and controllable | New parser, weak tooling, needless maintenance |

## Decision

- Store shareable project configuration in `<project>/offlinecode.json`.
- Store shareable test cases in `<project>/.offlinecode/tests/*.json` or text pairs for large input/output.
- Store machine-specific preferences and recent-project history through `QSettings` in the platform-native location.
- Store build artifacts under a configurable ignored directory, `.offlinecode/build/` by default.

The manifest includes `schemaVersion`. Reads validate required fields, preserve a last-known-good backup, and produce actionable errors. Writes serialize to a sibling temporary file, flush, and atomically replace the target where the platform supports it.

## Consequences

This choice lowers startup, binary size, packaging, and contributor complexity while preserving portability. It does not support rich global search history or analytics efficiently. SQLite may be reconsidered only if measured requirements emerge for indexed symbol storage, very large test catalogs, concurrent writers, or query-heavy code intelligence. That would be a separate optional cache, never the canonical project source.
