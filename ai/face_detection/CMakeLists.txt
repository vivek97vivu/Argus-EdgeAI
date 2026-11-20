project(face_detection)

set(SOURCES
    src/detector.cpp
    src/recognizer.cpp
)

set(HEADERS
    include/face_detection/detector.h
    include/face_detection/recognizer.h
)

add_library(face_detection ${SOURCES} ${HEADERS})
target_link_libraries(face_detection 
    ${OpenCV_LIBS} 
    ${CUDA_LIBRARIES}
    nvinfer
)
target_include_directories(face_detection PUBLIC include)
