add_executable(example example.c)
target_compile_options(example PRIVATE -Wall -Werror -ansi -pedantic -D_POSIX_C_SOURCE=200112L)

target_link_libraries(example streams)