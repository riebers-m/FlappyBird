add_executable(ecs_tests ecs_tests.cpp
        ${CMAKE_SOURCE_DIR}/src/ecs/Entity.hpp
        ${CMAKE_SOURCE_DIR}/src/ecs/Entity.cpp
        ${CMAKE_SOURCE_DIR}/src/ecs/components/RigidBody.hpp
        ${CMAKE_SOURCE_DIR}/src/ecs/components/Transform.hpp
)
target_include_directories(ecs_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(ecs_tests PRIVATE Catch2::Catch2WithMain EnTT::EnTT glm::glm)
set_target_properties(ecs_tests PROPERTIES CXX_STANDARD 20)
add_test(NAME ecs_tests COMMAND ecs_tests)


add_executable(asset_load_tests assets_load_tests.cpp)
target_include_directories(asset_load_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(asset_load_tests PRIVATE Catch2::Catch2WithMain JsonParser::JsonParser)
set_target_properties(asset_load_tests PROPERTIES CXX_STANDARD 20)
add_test(NAME asset_load_tests COMMAND asset_load_tests)
