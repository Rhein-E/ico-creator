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
        "${PROJECT_SOURCE_DIR}/lib/libopencv_highgui.so"
        "${PROJECT_SOURCE_DIR}/lib/libopencv_core.so"
        "${PROJECT_SOURCE_DIR}/lib/libopencv_imgcodecs.so"
)