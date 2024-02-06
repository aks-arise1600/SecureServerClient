cmake_minimum_required(VERSION 3.6.0)

project(SecureClient
  VERSION
    1.0
  DESCRIPTION
    "Qt & ssl based Secure TCP Client"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Qt5Core REQUIRED)

find_package(OpenSSL REQUIRED)

set(SRC_FILES
		main.cpp
		MainWindow.cpp
		SecureClient.cpp
		)

set(HEADER_FILES
		MainWindow.h
		SecureClient.h
		)
		
set(UI_FILES
		MainWindow.ui
		)
		
set(QRC_FILES
		resources.qrc
		)


add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${UI_FILES} ${QRC_FILES})

add_definitions(-DQT_NO_VERSION_TAGGING)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets ssl)

qt5_use_modules(${PROJECT_NAME} Core Network)

include_directories(.)
