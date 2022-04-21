add_executable(simple_test simple_test.c)
target_link_libraries(simple_test Prefix_container)
add_test(NAME simple_test COMMAND simple_test)
