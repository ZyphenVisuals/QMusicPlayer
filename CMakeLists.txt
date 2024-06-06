cmake_minimum_required(VERSION 3.16)

project(PPMusicProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appPPMusicProject
    main.cpp
)

qt_add_qml_module(appPPMusicProject
    URI PPMusicProject
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES filemanager.h filemanager.cpp
        SOURCES playlist.h playlist.cpp
        SOURCES song.h song.cpp
        RESOURCES static.qrc
        QML_FILES settings.qml
        SOURCES
        SOURCES player.h player.cpp
        SOURCES
        SOURCES songmodel.h songmodel.cpp
        QML_FILES about.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPPMusicProject PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPPMusicProject
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPPMusicProject
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appPPMusicProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

find_package(Qt6 COMPONENTS Multimedia REQUIRED)
target_link_libraries(appPPMusicProject PUBLIC Qt::Multimedia)
