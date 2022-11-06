cmake_minimum_required(VERSION 3.23)
<<<<<<< HEAD
project(image LANGUAGES CXX)
=======
project(CS250-Project1 LANGUAGES CXX)
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

<<<<<<< HEAD
add_library(common progargs.cpp progargs.hpp)
add_library(aos main-aos.cpp)
add_library(soa main-soa.cpp)

add_executable(image-aos imageaos.cpp)
target_link_libraries(image-aos common aos)
add_executable(image-soa imagesoa.cpp)
target_link_libraries(image-soa common soa)
=======
add_library(common common/progargs.cpp common/progargs.hpp)
add_library(aos aos/imageaos.cpp aos/imageaos.hpp)
add_library(soa soa/imagesoa.cpp soa/imagesoa.hpp)

add_executable(image-aos image-aos/main-aos.cpp)
target_link_libraries(image-aos common aos)
add_executable(image-soa image-soa/main-soa.cpp)
target_link_libraries(image-soa common soa)

#ADDED GOOGLE UNIT TESTS
>>>>>>> b840c421f3eb33a26ed84ec03d620d87da9019e6
