cmake_minimum_required (VERSION 3.5)
project(MulticastSender)

set(MULTICAST_SENDER_VERSION_MAJOR 1)
set(MULTICAST_SENDER_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creamos librerías

set(MULTICAST_SENDER_SOURCESLIB 
    ${PROJECT_SOURCE_DIR}/src/MulticastSenderLib.cpp    
    )
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(MulticastSenderLib SHARED ${MULTICAST_SENDER_SOURCESLIB})

set(ASYNC_LOG_SOURCESLIB 
    ${PROJECT_SOURCE_DIR}/src/AsyncLog.cpp    
    )
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(AsyncLogLib SHARED ${ASYNC_LOGR_SOURCESLIB})


# Ver que está como SHARED en vez de STATIC, con lo que puede verse de forma independiente como *.so e idealmente compilarse de forma independiente

# Habilitamos testing
enable_testing()
add_subdirectory(test)

# Creamos el ejecutable prinipal y le pegamos la librería
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    )
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(MulticastSender ${SOURCES})

# find_package(Boost COMPONENTS regex system filesystem REQUIRED)
find_package(Boost COMPONENTS system REQUIRED) # por el momento parece que sólo requerimos la de system, ya vermos después
target_link_libraries (
    MulticastSender
    AsyncLogLib
    MulticastSenderLib
    pthread
    ${Boost_SYSTEM_LIBRARY}        
    )
