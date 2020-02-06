include_directories ("${PROJECT_SOURCE_DIR}/src")

add_executable(run main.c)

target_link_libraries(run bilist)
