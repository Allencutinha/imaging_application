cmake_minimum_required(VERSION 2.8)
project(imlib)
find_package(OpenCV REQUIRED)

add_executable(imlib 
    main.cpp 
    hcd_custom.cpp 
    canny_custom.cpp 
    gaussian_custom.cpp
    hough_custom.cpp
    sobel_custom.cpp
    median_custom.cpp
    draw_custom.cpp
    )

target_link_libraries(imlib ${OpenCV_LIBS})


