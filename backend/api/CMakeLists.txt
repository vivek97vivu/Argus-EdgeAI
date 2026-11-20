project(backend_api)

add_library(backend_api
    src/api_server.cpp
    include/api_server.h
)

target_include_directories(backend_api PUBLIC include)
target_link_libraries(backend_api PUBLIC pthread)
