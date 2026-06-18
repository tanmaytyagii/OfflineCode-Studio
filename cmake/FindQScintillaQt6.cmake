# Locate QScintilla built for Qt 6 and expose QScintillaQt6::QScintillaQt6.

find_path(QScintillaQt6_INCLUDE_DIR
    NAMES Qsci/qsciscintilla.h
    DOC "QScintilla Qt 6 include directory"
)

find_library(QScintillaQt6_LIBRARY
    NAMES qscintilla2_qt6 qscintilla2-qt6 qscintilla2_qt6d
    DOC "QScintilla Qt 6 library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QScintillaQt6
    REQUIRED_VARS QScintillaQt6_LIBRARY QScintillaQt6_INCLUDE_DIR
)

if(QScintillaQt6_FOUND AND NOT TARGET QScintillaQt6::QScintillaQt6)
    add_library(QScintillaQt6::QScintillaQt6 UNKNOWN IMPORTED)
    set_target_properties(QScintillaQt6::QScintillaQt6 PROPERTIES
        IMPORTED_LOCATION "${QScintillaQt6_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${QScintillaQt6_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(QScintillaQt6_INCLUDE_DIR QScintillaQt6_LIBRARY)
