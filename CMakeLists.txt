cmake_minimum_required(VERSION 3.6.0)

project(SecureServerClient
  VERSION
    1.0
  DESCRIPTION
    "qt based example of server client TLS handshake to secure data transmission"
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(SecureServer)
add_subdirectory(SecureClient)
