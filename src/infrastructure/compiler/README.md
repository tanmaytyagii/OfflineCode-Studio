# Compiler Infrastructure

This module will contain GCC, Clang, Apple Clang, and MSVC strategy implementations plus diagnostic fixtures. Adapters implement `application/interfaces/compiler_service.h`, invoke executables with discrete arguments, preserve raw output, and normalize diagnostics on a best-effort basis.

No compiler-specific type may escape this module. Shared behavior belongs in application contracts or domain value objects.
