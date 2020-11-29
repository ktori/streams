add_library(streams)

add_subdirectory(include)
add_subdirectory(src)

target_include_directories(streams PUBLIC include)

target_compile_options(streams PRIVATE -Wall -Werror -ansi -pedantic -D_POSIX_C_SOURCE=200112L)