add_executable(r-type-client
    src/main.cpp
)

target_include_directories(r-type-client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(r-type-client PRIVATE
    engine
)

add_custom_command(TARGET r-type-client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)