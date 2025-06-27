cmake_minimum_required(VERSION 3.16)

project(simulador VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

set(PUBSUB_CORE_SOURCES
    src/Broker.cpp
    src/Component.cpp
    src/Follower.cpp
    src/Publisher.cpp
    src/Recorder.cpp
    # src/Subscriber.cpp
    src/VideoPublisher.cpp
    src/VideoFollower.cpp
    includes/VideoFollower.h
)

add_library(pubsub_core STATIC ${PUBSUB_CORE_SOURCES})

target_include_directories(pubsub_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(pubsub_core PUBLIC Qt6::Core)

set(PROJECT_SOURCES
    src/simulador/main.cpp
    src/simulador/mainwindow.cpp
    src/simulador/mainwindow.h
)

qt_add_executable(simulador
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(simulador PRIVATE pubsub_core Qt6::Widgets Qt6::Core)

if(Qt6_VERSION VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.simulador)
endif()
set_target_properties(simulador PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS simulador
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(simulador)
