cmake_minimum_required(VERSION 3.5)

project(SLS VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "/Users/kimno/Qt/6.2.4/macos")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets DataVisualization Charts)

include_directories("/usr/local/include/eigen3")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        Resources.qrc
        STNewProject.cpp STNewProject.h STNewProject.ui
        STFileManager.cpp STFileManager.h STFileManager.ui
        STPreferences.h STPreferences.cpp STPreferences.ui
        STToolBox.h STToolBox.cpp STToolBox.ui
        STFormEditor.h STFormEditor.cpp STFormEditor.ui
        STSimulation.h STSimulation.cpp STSimulation.ui
)

set(PROJECT_SOURCES_SIM

        Sim/SGHeaders.h Sim/SGHeaders.cpp
        Sim/SGFile.h Sim/SGFile.cpp
        Sim/SGModelBase.h Sim/SGModelBase.cpp
        Sim/SGModelGround.h Sim/SGModelGround.cpp
        Sim/SGModelLine.h Sim/SGModelLine.cpp
        Sim/SGModelRes.h Sim/SGModelRes.cpp
        Sim/SGModelSource.h Sim/SGModelSource.cpp
        Sim/SGCanvasNotification.h Sim/SGCanvasNotification.cpp Sim/SGCanvasNotification.ui
        Sim/SGCanvasView.h Sim/SGCanvasView.cpp Sim/SGCanvasView.ui
        Sim/SGEditorModel.h Sim/SGEditorModel.cpp Sim/SGEditorModel.ui
        Sim/SCHeader.h
        Sim/SCConsole.h Sim/SCConsole.cpp
        Sim/SCNetlist.h Sim/SCNetlist.cpp
        Sim/SCSimulation.h Sim/SCSimulation.cpp
        Sim/SCMatrixResolve.h Sim/SCMatrixResolve.cpp
        Sim/SCSpice.h Sim/SCSpice.cpp
)

set(PROJECT_SOURCES_LAB 

        Lab/LG2DWidget.h Lab/LG2DWidget.cpp Lab/LG2DWidget.ui
        Lab/LG3DWidget.h Lab/LG3DWidget.cpp Lab/LG3DWidget.ui
        Lab/LGDataModel.h Lab/LGDataModel.cpp
        Lab/LGStyleCollection.h Lab/LGStyleCollection.cpp
)

qt_add_executable(SLS
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${PROJECT_SOURCES_SIM}
    ${PROJECT_SOURCES_LAB}
)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${PROJECT_SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${PROJECT_SOURCES_SIM})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${PROJECT_SOURCES_LAB})

target_link_libraries(SLS PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::DataVisualization Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(SLS PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER studio.tri.slsmain
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_custom_command(
            TARGET SLS
            POST_BUILD
            COMMAND plutil -replace NSRequiresAquaSystemAppearance -bool true ./Debug/SLS.app/Contents/Info.plist
    )
endif()


install(TARGETS SLS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SLS)
endif()
