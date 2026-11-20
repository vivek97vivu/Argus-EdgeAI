project(communication_mqtt)

add_library(communication_mqtt
    src/mqtt_client.cpp
    include/communication/mqtt/mqtt_client.h
)

target_include_directories(communication_mqtt PUBLIC include)
target_link_libraries(communication_mqtt PUBLIC mosquitto pthread)
