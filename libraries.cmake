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
