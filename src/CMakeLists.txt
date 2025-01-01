include_directories(../include)

add_library(client client.c)
add_library(server server.c)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} client server)