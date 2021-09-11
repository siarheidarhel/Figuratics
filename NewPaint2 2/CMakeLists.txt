cmake_minimum_required(VERSION 3.5)

project(Figuratics LANGUAGES CXX)
set(PROJECT_VERSION 0.0.1)





set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        myresource.qrc
        myscene.cpp
        myscene.h
        figuretype.h
        mytextclass.cpp
        mytextclass.h
        myresource.qrc




)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#  qt_add_executable(NewPaint2
#       ${PROJECT_SOURCES}
        set(CUR_TARGET Figuratics)

             set(MACOSX_BUNDLE_ICON_FILE iconfile.icns)
             set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/Assets/iconfile.icns)
                set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
                       MACOSX_PACKAGE_LOCATION "Resources")
                   set(MACOSX_BUNDLE_BUNDLE_VERSION 0.0.1)
                   qt_add_executable(${CUR_TARGET} MACOSX_BUNDLE ${PROJECT_SOURCES} ${APP_ICON_MACOSX}

    )
#)
else()
    if(ANDROID)
        add_library(Figuratics SHARED
            ${PROJECT_SOURCES}
        )
    else()
       add_executable(Figuratics
          ${PROJECT_SOURCES}


   )
    endif()
endif()

target_link_libraries(Figuratics PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)



