add_executable(Main main.c)
target_link_libraries(Main PUBLIC Prefix_container)
target_compile_options(Main PUBLIC -Wall -Wextra -pedantic -Werror)
