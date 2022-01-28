cmake_minimum_required(VERSION 3.12)
project(pam_wordle)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(PAM REQUIRED)

if (NOT PAM_FOUND)
    message(FATAL_ERROR "PAM library was not found.")
endif()

include_directories(
    ${PAM_INCLUDE_DIR}
)

add_library(pam_wordle SHARED
    "src/pam_wordle.cpp"
)
set_target_properties(pam_wordle PROPERTIES PREFIX "")
set_target_properties(pam_wordle PROPERTIES SUFFIX ".so")

target_link_libraries(pam_wordle
    ${PAM_LIBRARIES}
)

set_target_properties(pam_wordle PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS pam_wordle RUNTIME DESTINATION "/usr/lib/pam")
