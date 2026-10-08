cmake_minimum_required(VERSION 4.1.2)

project(MultiAgentSwarn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(cpr REQUIRED)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/.git DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/.env DESTINATION ${CMAKE_BINARY_DIR})
add_executable(main main.cpp GithubAuthenticate.cpp)
target_link_libraries(main cpr::cpr)
