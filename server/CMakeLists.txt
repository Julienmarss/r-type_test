add_executable(r-type-server
    src/main.cpp
)

target_include_directories(r-type-server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(r-type-server PRIVATE
    engine
)