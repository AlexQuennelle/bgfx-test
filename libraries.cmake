include(FetchContent)


message("Fetching bgfx")
set(BGFX_BUILD_EXAMPLES OFF)
FetchContent_Declare(
    bgfx
    GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
    GIT_TAG v1.136.9095-503
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(bgfx)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE bgfx)
message("Done!")

message("Fetching glfw")
set(GLFW_VERSION 3.4)
find_package(glfw ${GLFW_VERSION} QUIET)
if (NOT glfw_FOUND)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG ${GLFW_VERSION}
        GIT_SHALLOW ON
        GIT_PRORGRESS ON
    )
    FetchContent_MakeAvailable(glfw)
    FetchContent_GetProperties(glfw SOURCE_DIR GLFW_DIR)
    target_include_directories(
        ${CMAKE_PROJECT_NAME}
        SYSTEM PRIVATE "${glfw_SOURCE_DIR}/include/GLFW/"
    )
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
message("Done!")
