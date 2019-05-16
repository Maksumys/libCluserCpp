project(libClusterCpp)

find_package(Boost REQUIRED)

set(SOURCES src/main.cpp)

add_executable(cluster ${SOURCES})

target_link_libraries(cluster ${Boost_LIBRARIES})
target_include_directories(cluster PUBLIC ${Boost_INCLUDE_DIRS})
