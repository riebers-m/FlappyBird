add_executable(ecs_tests ecs_tests.cpp)
target_link_libraries(ecs_tests PRIVATE Catch2::Catch2WithMain ecslib::ecslib)
set_target_properties(ecs_tests PROPERTIES CXX_STANDARD 20)
add_test(ecs_tests COMMAND ecs_tests)
