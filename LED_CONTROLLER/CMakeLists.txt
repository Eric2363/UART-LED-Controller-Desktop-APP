cmake_minimum_required(VERSION 3.16)

project(LED_CONTROLLER VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find Qt with Widgets + SerialPort
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort)

# ✅ Set project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# ✅ Add Windows icon resource if on Windows
if(WIN32)
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")
    list(APPEND PROJECT_SOURCES ${APP_ICON_RESOURCE})
endif()

# ✅ Add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LED_CONTROLLER
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(LED_CONTROLLER SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(LED_CONTROLLER
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ✅ Link Qt libraries
target_link_libraries(LED_CONTROLLER
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::SerialPort
)

# Optional: Mac/iOS bundle settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LED_CONTROLLER)
endif()

set_target_properties(LED_CONTROLLER PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ✅ Install settings
include(GNUInstallDirs)
install(TARGETS LED_CONTROLLER
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ✅ Finalize if Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LED_CONTROLLER)
endif()
