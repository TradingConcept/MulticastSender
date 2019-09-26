cmake_minimum_required (VERSION 3.5)
project(MulticastSender)

set(MULTICAST_SENDER_VERSION_MAJOR 1)
set(MULTICAST_SENDER_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# metemos librerias
add_subdirectory(LoggingLib)

# Creamos el ejecutable prinipal y le pegamos la librería
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Helpers.cpp    
    ${PROJECT_SOURCE_DIR}/src/MulticastSenderLib.cpp    
    )
include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/LoggingLib/include"
	)
add_executable(MulticastSender ${SOURCES})

# find_package(Boost COMPONENTS regex system filesystem REQUIRED)
find_package(Boost COMPONENTS system REQUIRED) # por el momento parece que sólo requerimos la de system, ya vermos después
target_link_libraries (
    MulticastSender
    LoggingLib
    pthread
    ${Boost_SYSTEM_LIBRARY}        
    )
