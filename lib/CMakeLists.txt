add_library(Prefix_container Ip_v4_prefix.c Prefix_container.c)
target_compile_options(Prefix_container PUBLIC -Wall -Wextra -pedantic -Werror)
