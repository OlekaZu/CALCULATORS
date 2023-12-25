cmake_minimum_required(VERSION 3.5)

project(MyCalculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Charts)

set(PROJECT_SOURCES
        main.cc
        View/mainwindow.cc
        View/mainwindow.h
        View/mainwindow.ui
        View/graph.cc
        View/graph.h
        View/graph.ui
        View/credit.cc
        View/credit.h
        View/credit.ui
        View/deposit.cc
        View/deposit.h
        View/deposit.ui
        Model/calculator_model.cc
        Model/calculator_model.h
        Model/credit_model.cc
        Model/credit_model.h
        Model/deposit_model.cc
        Model/deposit_model.h
        Controller/controller.cc
        Controller/controller.h
        resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
           set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/Icons/calc_icon.rc")
           qt_add_executable(MyCalculator
               MANUAL_FINALIZATION
               ${PROJECT_SOURCES}
               ${APP_ICON_RESOURCE_WINDOWS}
           )
   else ()
        qt_add_executable(MyCalculator
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
        )
   endif()
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MyCalculator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MyCalculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MyCalculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MyCalculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MyCalculator PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
)

set_target_properties(MyCalculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyCalculator)
endif()
