# GitHub Labels

The canonical labels live in `.github/labels.yml` and can be synchronized with a label action or `gh label create/edit`. The required public set is:

| Label | Purpose |
|---|---|
| `bug` | Behavior differs from a requirement or documented expectation |
| `enhancement` | New capability or intentional improvement |
| `documentation` | Docs, examples, or comments only |
| `good first issue` | Bounded, explained, and independently testable contribution |
| `help wanted` | Maintainers actively invite ownership |
| `UI` | Layout, state presentation, interaction, theming, accessibility-adjacent UI |
| `performance` | Startup, memory, input latency, scanning, output throughput |
| `compiler` | Discovery, command generation, diagnostics, build lifecycle |
| `editor` | QScintilla, documents, file safety, search, syntax behavior |

Supporting labels cover accessibility, testing, triage, platforms, and severity. Use one type label, one or more area labels, and a priority only after triage. `good first issue` means the description includes files, acceptance criteria, tests, and an available maintainer; it must not be used merely because a change has few lines.

## Severity Guide

- `priority-critical`: source loss, unsafe overwrite, exploitable vulnerability, or application unusable for all users.
- `priority-high`: primary edit/build/run workflow broken for a supported setup, with no reasonable workaround.
- `priority-medium`: important defect or degradation with a workaround.
- `priority-low`: polish, rare edge case, or small inconsistency.
