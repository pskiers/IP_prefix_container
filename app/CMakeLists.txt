add_executable(Main main.c)
target_link_libraries(Main PRIVATE Ip_prefix)
target_compile_options(Main PUBLIC -Wall -Wextra -pedantic -Werror)
