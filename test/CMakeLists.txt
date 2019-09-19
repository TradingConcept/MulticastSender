find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories("${PROJECT_SOURCE_DIR}/include")

set(TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/MulticastSenderTest.cpp)
set(TEST_LIBS MulticastSenderLib)

add_executable(test_main ${TEST_SOURCES})
target_link_libraries(
    test_main 
    pthread 
    ${TEST_LIBS} 
    ${Boost_LIBRARIES})
add_test(MulticastSenderTest test_main COMMAND test_main)
