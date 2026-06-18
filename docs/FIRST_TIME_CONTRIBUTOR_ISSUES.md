# First-Time Contributor Issue Backlog

These 20 issues are ready to copy into GitHub. Before publishing, a maintainer should confirm file paths against the implementation and volunteer as mentor. Each issue is independently mergeable and avoids critical ownership or security decisions.

## 1. Add Copy Path to the project explorer context menu

**Labels:** `good first issue`, `UI`
**Effort:** 2-4 hours

Add Copy Absolute Path and Copy Project-Relative Path actions for selected files. Use the existing clipboard abstraction and disable the relative action for external files.

**Acceptance:** actions have shortcuts/accessibility names; separators stay tidy; GUI test verifies both values on a temp project.

## 2. Show line-ending mode in the status bar

**Labels:** `good first issue`, `editor`, `UI`
**Effort:** 2-4 hours

Display `LF`, `CRLF`, or `Mixed` for the active document and update it when the active tab or document metadata changes.

**Acceptance:** empty state is hidden; tooltip explains the value; view-model unit test covers all modes.

## 3. Add a Reset Font button to Editor settings

**Labels:** `good first issue`, `UI`
**Effort:** 2-4 hours

Reset only editor family and size to platform defaults without changing indentation or theme.

**Acceptance:** preview updates; Cancel restores prior values; persistence test covers Apply.

## 4. Document compiler setup for Ubuntu

**Labels:** `good first issue`, `documentation`, `compiler`
**Effort:** 1-2 hours

Add an offline-friendly guide for checking GCC/Clang, selecting an executable, and diagnosing missing standard libraries. Do not promise package names across unsupported distributions.

**Acceptance:** commands are tested on supported Ubuntu versions; links are supplemental, not required to use the guide.

## 5. Add an Empty Project explorer message

**Labels:** `good first issue`, `UI`
**Effort:** 2-4 hours

Show a concise empty state with Create File and Reveal Folder actions when a valid project has no source files.

**Acceptance:** keyboard reachable; screen reader name exists; disappears after the first file is added.

## 6. Add project name length validation

**Labels:** `good first issue`, `bug`
**Effort:** 2-3 hours

Enforce the documented non-empty 100-character limit in the domain validator and New Project dialog.

**Acceptance:** leading/trailing whitespace policy is consistent; boundary unit tests cover 0, 1, 100, and 101 characters.

## 7. Add a Copy Diagnostic action

**Labels:** `good first issue`, `compiler`, `UI`
**Effort:** 3-5 hours

Copy selected Problems rows in `relative-path:line:column: severity: message` format without exposing absolute home paths.

**Acceptance:** missing location fields format cleanly; multiple selections use one line each; unit test covers formatting.

## 8. Add a Clear Build Output command

**Labels:** `good first issue`, `compiler`, `UI`
**Effort:** 2-3 hours

Add toolbar/context actions to clear completed output. Disable while no content exists; clearing must not remove Problems records or alter the build result.

**Acceptance:** action state follows content; keyboard focus remains in the output panel; GUI test passes.

## 9. Add elapsed-time formatting tests

**Labels:** `good first issue`, `testing`
**Effort:** 1-3 hours

Add table-driven tests for the shared duration formatter at sub-millisecond, millisecond, second, minute, and boundary values.

**Acceptance:** locale policy is explicit; tests do not depend on wall-clock time.

## 10. Add `.cc` and `.cxx` source filters

**Labels:** `good first issue`, `editor`, `enhancement`
**Effort:** 1-2 hours

Recognize `.cc`, `.cxx`, `.hh`, `.hxx`, and `.hpp` alongside `.cpp`/`.h` in open dialogs and C++ lexer selection.

**Acceptance:** comparison follows platform case policy; parameterized test covers every extension.

## 11. Add Reveal Build Directory action

**Labels:** `good first issue`, `UI`
**Effort:** 3-5 hours

Expose the active profile build directory through a platform desktop-service adapter. Disable before a directory exists.

**Acceptance:** controller depends on an interface, not `QDesktopServices`; fake-adapter test verifies canonical path.

## 12. Improve malformed manifest error text

**Labels:** `good first issue`, `bug`, `documentation`
**Effort:** 2-4 hours

Include JSON line/column, project-relative manifest path, and recovery actions while keeping raw parser detail in expandable diagnostics.

**Acceptance:** message does not show a home-directory prefix; golden tests cover syntax and schema failures.

## 13. Add test-case duplicate action

**Labels:** `good first issue`, `enhancement`, `UI`
**Effort:** 4-6 hours

Duplicate the selected test with a new ID and a collision-free name such as `Sample 1 copy`.

**Acceptance:** all inputs/settings copy; result history does not; persistence round-trip test passes.

## 14. Add trailing-whitespace comparator fixtures

**Labels:** `good first issue`, `testing`
**Effort:** 2-3 hours

Expand fixtures for tabs, spaces, blank final lines, CRLF/LF, empty output, and internal whitespace.

**Acceptance:** fixtures document intended normalization; exact mode remains unchanged.

## 15. Add tooltip for truncated compiler paths

**Labels:** `good first issue`, `UI`, `accessibility`
**Effort:** 2-3 hours

When the Toolchain dialog elides a compiler path, expose the full value via tooltip and accessible description.

**Acceptance:** no tooltip when fully visible; test covers resizing and accessible value.

## 16. Document keyboard shortcuts

**Labels:** `good first issue`, `documentation`
**Effort:** 2-4 hours

Create a categorized shortcut reference derived from current defaults, showing macOS alternatives where they differ.

**Acceptance:** every primary menu action appears; a maintainer verifies labels against action definitions.

## 17. Add recent-project missing-path cleanup

**Labels:** `good first issue`, `bug`
**Effort:** 3-5 hours

Offer Remove from List when a recent project no longer exists. Do not remove entries automatically, because removable drives may be disconnected.

**Acceptance:** Open remains recoverable; cleanup persists; fake-filesystem tests cover missing and temporarily unavailable paths.

## 18. Add output-limit setting validation

**Labels:** `good first issue`, `bug`, `performance`
**Effort:** 2-4 hours

Validate the 1 KiB to 100 MiB retained-output range in both settings DTO and application boundary.

**Acceptance:** invalid persisted values fall back safely; boundary tests cover minimum/maximum and overflow input.

## 19. Add About dialog copy-version button

**Labels:** `good first issue`, `UI`
**Effort:** 2-3 hours

Copy application version, commit, Qt version, QScintilla version, OS, and architecture for bug reports. Exclude usernames and full paths.

**Acceptance:** output is stable plain text; unknown commit is handled; unit test checks privacy fields.

## 20. Add manifest schema reference page

**Labels:** `good first issue`, `documentation`
**Effort:** 3-5 hours

Document every v1 field, type, default, allowed range, portability rule, and a complete example.

**Acceptance:** example passes repository validation; required/optional fields and unknown-key behavior are explicit.

## Maintainer Publishing Checklist

- Confirm the behavior is not already implemented.
- Link the relevant SRS requirement and code locations.
- Add a named mentor and expected test command.
- Mark dependencies and platform requirements.
- Keep acceptance criteria unchanged unless discussed publicly.
