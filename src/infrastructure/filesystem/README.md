# Filesystem Infrastructure

This module will implement application filesystem and project-repository ports with `std::filesystem`, schema-validated JSON, temporary sibling writes, atomic replacement where supported, external-change stamps, and recovery backups.

Filesystem errors are converted into stable application errors with user-facing recovery information; platform exception types do not cross the adapter boundary.
