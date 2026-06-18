cmake_minimum_required(VERSION 3.24)

project(
    OfflineCodeStudio
    VERSION 0.1.0
    DESCRIPTION "A lightweight, fully offline C++ desktop IDE"
    LANGUAGES CXX
)

option(OFFLINECODE_BUILD_GUI "Build the Qt/QScintilla desktop application" ON)
option(OFFLINECODE_BUILD_TESTS "Build tests" ON)
option(OFFLINECODE_ENABLE_WARNINGS_AS_ERRORS "Treat project warnings as errors" OFF)
option(OFFLINECODE_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(offlinecode_core
    src/domain/entities/project.cpp
    src/application/services/build_coordinator.cpp
)
add_library(OfflineCode::Core ALIAS offlinecode_core)

target_include_directories(offlinecode_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(offlinecode_core PRIVATE /W4 /permissive-)
    if(OFFLINECODE_ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(offlinecode_core PRIVATE /WX)
    endif()
else()
    target_compile_options(offlinecode_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    if(OFFLINECODE_ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(offlinecode_core PRIVATE -Werror)
    endif()
endif()

if(OFFLINECODE_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU" AND NOT WIN32)
        target_compile_options(offlinecode_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(offlinecode_core PUBLIC -fsanitize=address,undefined)
    else()
        message(WARNING "Sanitizers are only configured for GCC/Clang on non-Windows hosts")
    endif()
endif()

if(OFFLINECODE_BUILD_GUI)
    find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)
    find_package(QScintillaQt6 REQUIRED)

    qt_standard_project_setup()

    qt_add_executable(offlinecode_studio
        src/app/main.cpp
        src/presentation/main_window/main_window.cpp
        src/presentation/main_window/main_window.h
    )

    target_link_libraries(offlinecode_studio
        PRIVATE
            OfflineCode::Core
            Qt6::Core
            Qt6::Gui
            Qt6::Widgets
            QScintillaQt6::QScintillaQt6
    )

    set_target_properties(offlinecode_studio PROPERTIES
        OUTPUT_NAME "OfflineCodeStudio"
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "OfflineCode Studio"
        MACOSX_BUNDLE_GUI_IDENTIFIER "studio.offlinecode.app"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    )
endif()

if(OFFLINECODE_BUILD_TESTS)
    include(CTest)
    enable_testing()

    add_executable(offlinecode_core_tests
        tests/unit/project_test.cpp
        tests/unit/build_coordinator_test.cpp
    )
    target_link_libraries(offlinecode_core_tests PRIVATE OfflineCode::Core)
    add_test(NAME offlinecode_core_tests COMMAND offlinecode_core_tests)
endif()
