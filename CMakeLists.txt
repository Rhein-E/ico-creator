CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

PROJECT("ico creator")

SET(SRC
    "${PROJECT_SOURCE_DIR}/src/ico.cpp"
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

ADD_EXECUTABLE(icocreator ${SRC})

TARGET_INCLUDE_DIRECTORIES(icocreator
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
)

TARGET_LINK_LIBRARIES(icocreator
    PRIVATE
        "/usr/local/lib/libopencv_highgui.so"
        "/usr/local/lib/libopencv_core.so"
        "/usr/local/lib/libopencv_imgcodecs.so"
)