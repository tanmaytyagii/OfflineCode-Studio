# Integration Tests

Integration tests exercise real temporary files, JSON manifests, child processes, compiler fixtures, cancellation, timeouts, and platform path behavior. They remain fully offline, create all state under test-owned temporary directories, and remove only state they created.

Tiny helper executables for echo, crash, sleep, unbounded output, argument printing, and child spawning should be built as test-only CMake targets.
