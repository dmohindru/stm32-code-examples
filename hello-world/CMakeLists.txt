add_executable(hello-world main.c)

target_link_libraries(hello-world PRIVATE stm32_common_starter)