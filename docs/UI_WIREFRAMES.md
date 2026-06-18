# UI Wireframes

## Design Principles

- Keep source code central; secondary tools collapse without hiding state.
- Make Build and Run outcomes visible without modal dialogs.
- Use text, icon, and color together so status does not depend on color alone.
- Preserve keyboard access and platform conventions.
- Offer a useful first run without requiring configuration when a compiler is discoverable.

## Main Window

```text
+--------------------------------------------------------------------------------+
| Menu bar                                                                      |
+--------------------------------------------------------------------------------+
| Toolbar: New | Open | Save || Profile | Build | Run | Stop || Test Cases      |
+----------------------+---------------------------------------------------------+
| Project Explorer     | Tab: main.cpp | Tab: solution.cpp*                     |
| [filter files...]    +---------------------------------------------------------+
| v Project            |  1  #include <iostream>                                |
|   v src              |  2                                                     |
|       main.cpp       |  3  int main() {                                       |
|       solution.cpp * |  4      return 0;                                      |
|   v tests            |  5  }                                                  |
|   offlinecode.json   |                                                        |
|                      |                                                        |
+----------------------+---------------------------------------------------------+
| Problems | Build | Run | Test Cases | Terminal                                |
| [!] src/main.cpp 12:7  unused variable 'n'                                    |
+--------------------------------------------------------------------------------+
| Ready | Debug | clang++ 18 | UTF-8 | LF | Spaces: 4 | Ln 3, Col 1             |
+--------------------------------------------------------------------------------+
```

**Behavior:** explorer width and bottom-panel height are persisted. `Ctrl/Cmd+P` opens quick file search. `F6` builds, `F5` runs, and `Shift+F5` stops by default; shortcuts remain configurable. Dirty tabs show `*`; close prompts list all unsaved documents in one dialog.

## First Run and Toolchain Setup

```text
+------------------------------------------------------------------+
| Welcome to OfflineCode Studio                                    |
|                                                                  |
| [ Create Project ] [ Open Folder ] [ Import C++ File ]            |
|                                                                  |
| Compiler status                                                   |
| [check] Clang 18 detected at /usr/bin/clang++                     |
|          [Use compiler] [Choose another...]                       |
|                                                                  |
| Recent Projects                                                   |
| No recent projects yet.                                          |
+------------------------------------------------------------------+
```

If discovery fails, the screen explains what a compiler is, links to offline help packaged with the application, and allows browsing for an executable. It never claims the IDE bundles a compiler unless a platform distribution explicitly does.

## New Project Dialog

Fields: project name, location, template (`Empty`, `Console App`, `Competitive Programming`), C++ standard, and detected toolchain. Inline validation shows the final path and disables Create for invalid or non-empty targets. Creation is transactional: a failure removes only files created during that attempt.

## Build and Problems Panels

The Build tab shows timestamped raw compiler output and elapsed time. The Problems tab contains sortable severity, file, line, code, and message columns. Selecting a diagnostic focuses the source location. A running operation shows `Cancel`; completion announces success or failure through text, icon, status bar, and accessible notification.

## Competitive Programming Workspace

```text
+-------------------------+-------------------------+--------------------------+
| Test Cases              | Input                   | Expected / Actual Diff   |
| [check] Sample 1  12 ms | 5                       | Expected: 15             |
| [x]     Sample 2  TLE   | 1 2 3 4 5               | Actual:   14             |
| [ ]     Custom          |                         |                 ^^       |
| [+ Add] [Run all]       |                         |                          |
+-------------------------+-------------------------+--------------------------+
```

Each case supports a name, stdin, expected stdout, timeout, and comparison mode (`exact`, `trim trailing whitespace`, or `tokens`). Results show pass/fail, runtime, exit status, stderr availability, and truncated-output warning.

## Settings

Categories: Editor, Appearance, Build & Toolchains, Run, Competitive Programming, Keyboard, and Privacy. Changes apply to a preview where safe. Reset can target the current page or all settings. Machine-specific compiler paths never enter the shareable project manifest unless explicitly requested.

## Responsive and Accessibility Behavior

- At narrow widths, the explorer and bottom panel become toggleable drawers.
- A 125%, 150%, and 200% scale test is required on every platform.
- All controls have accessible names, focus indicators, and logical tab order.
- Minimum contrast follows WCAG 2.1 AA where Qt/platform rendering permits.
- Screen reader announcements cover build start/end, diagnostics count, and test result summaries.
- Reduced-motion mode disables non-essential transitions.

## Empty, Error, and Recovery States

Every panel has purposeful empty text and a primary action. Missing files remain visible with a warning and Locate/Remove actions. Crash recovery lists autosaved documents with original paths, timestamps, and preview/diff actions before restoration.
