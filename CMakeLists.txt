cmake_minimum_required(VERSION 3.5)

project(weatherapp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(FetchContent)
#FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
#FetchContent_MakeAvailable(cpr)
# set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(cpr CONFIG REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        src/mainwindow.cpp
        src/apichecker.cpp
        include/mainwindow.h
        include/mainwindow.ui
        include/apichecker.h
        src/apichecker.cpp
        include/geocoding.h
        src/geocoding.cpp
        include/weatherfetching.h
        src/weatherfetching.cpp
)

if (TARGET Qt6::Widgets)
    qt_add_executable(weatherapp MANUAL_FINALIZATION ${PROJECT_SOURCES}
        icons.qrc
        resource.qrc)
else ()
    add_executable(weatherapp ${PROJECT_SOURCES})
endif ()


target_link_libraries(weatherapp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cpr::cpr)

set_target_properties(weatherapp PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS weatherapp
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(weatherapp)
endif ()
