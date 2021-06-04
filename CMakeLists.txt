cmake_minimum_required(VERSION 3.2)
project(imlib)
#find_package(OpenCV REQUIRED)
include(/home/allen/deps/OpenCV-3.4.14/share/OpenCV/OpenCVConfig.cmake)
include_directories(include)
set(IMLIB_SRC
    src/main.cpp 
    src/hcd_custom.cpp 
    src/canny_custom.cpp 
    src/gaussian_custom.cpp
    src/hough_custom.cpp
    src/sobel_custom.cpp
    src/median_custom.cpp
    src/draw_custom.cpp
)

add_executable(imlib ${IMLIB_SRC})

target_link_libraries(imlib ${OpenCV_LIBS})


