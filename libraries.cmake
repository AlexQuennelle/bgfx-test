include(FetchContent)

message("Fetching glfw")
if(NOT EMSCRIPTEN)
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
else()
    message("Using port")
    add_link_options("--use-port=contrib.glfw3")
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    # Also set compiler and linker flags for Emscripten
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "-s USE_PTHREADS=1")
endif()
message("Done!")

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
