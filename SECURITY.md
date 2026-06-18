# Security Policy

## Supported Versions

| Version | Security fixes |
|---|---|
| Latest stable 1.x | Yes |
| Latest prerelease | Best effort |
| Older releases | No |

## Reporting a Vulnerability

Do not open a public issue. Use GitHub's private vulnerability reporting feature. If it is unavailable, contact the private security address listed in the repository profile. Include affected version, platform, impact, minimal reproduction, and suggested mitigation; omit unrelated private source code.

Expect acknowledgement within 3 business days and an initial assessment within 10 business days. Timelines may change with severity and maintainer availability. Reporters will be credited unless they prefer anonymity.

## Scope Notes

Relevant reports include path traversal, unsafe process argument handling, project-file code execution, arbitrary file overwrite/delete, credential leakage through logs, dependency compromise, and process cleanup failures with security impact.

OfflineCode Studio executes user-selected compiled programs locally. It enforces resource policies for usability, but it is not a hostile-code sandbox. Running malicious code with the user's privileges is outside the application's security guarantee unless the issue bypasses an explicit safety boundary.

## Disclosure

Maintainers will coordinate a fix, regression test, advisory, affected-version range, and release. Please allow a reasonable remediation window before public disclosure.
