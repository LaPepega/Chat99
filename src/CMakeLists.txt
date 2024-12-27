include_directories(include)

add_library(client SHARED client.c)
add_library(server SHARED server.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} client server)