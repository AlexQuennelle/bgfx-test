cmake_minimum_required(VERSION 4.2.1)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_POLICY_DEFAULT_CMP0069 NEW) set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

if(NOT EMSCRIPTEN)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if("${CMAKE_GENERATOR}" STREQUAL "Ninja")

else()

endif()

if(WIN32)
  set(CMAKE_CXX_COMPILER clang++)
  set(CMAKE_C_COMPILER clang)
endif()

if(NOT WIN32)
  # add_compile_options("-fsanitize=undefined")
  # add_compile_options("-fsanitize=address")
endif()

# Change this to match the name of the current folder
project(
  bgfx-test
  LANGUAGES CXX C
  VERSION 0.0
)
message("Build type: ${CMAKE_BUILD_TYPE}")

add_executable("${CMAKE_PROJECT_NAME}")

if(NOT WIN32)
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

# Libraries here
if(EMSCRIPTEN)
    set(GLFW_BUILD_WAYLAND OFF)
    set(GLFW_BUILD_X11 OFF)
    set(BGFX_CONFIG_MULTITHREADED OFF)
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/libraries.cmake")

set(CMAKE_CXX_FLAGS
    "-Wall -Wextra -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused\
    -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion\
    -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond\
    -Wduplicated-branches -Wlogical-op -Wuseless-cast"
)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(EMSCRIPTEN)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}\
 --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/src/template.html"
  )
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}\
 --js-library ${CMAKE_CURRENT_SOURCE_DIR}/src/lib.js"
  )
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES LINK_FLAGS
               "--preload-file ../resources@./resources -sALLOW_MEMORY_GROWTH"
  )
endif()
target_compile_definitions(
  ${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:PRODUCTION_BUILD>
                               NAME="${CMAKE_PROJECT_NAME}"
)

set_target_properties(
  "${CMAKE_PROJECT_NAME}"
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
             RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/\
${CMAKE_PROJECT_NAME}_${CMAKE_PROJECT_VERSION}"
)
if(EMSCRIPTEN)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE
               "${CMAKE_CURRENT_SOURCE_DIR}/bin/\
${CMAKE_PROJECT_NAME}_${CMAKE_PROJECT_VERSION}_web"
  )
endif()

set(RELEASE_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/\
${CMAKE_PROJECT_NAME}_${CMAKE_PROJECT_VERSION}/resources/"
)
set(DEBUG_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
    RESOURCES_PATH=$<IF:$<CONFIG:Release>,"./resources/","${DEBUG_RESOURCE_DIR}">
)

target_compile_features("${CMAKE_PROJECT_NAME}" PRIVATE cxx_std_23)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

target_include_directories(
  "${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_include_directories(
  "${CMAKE_PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}"
)
target_include_directories(
  "${CMAKE_PROJECT_NAME}"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/nativefiledialog-extended-1.2.1/src/include/"
)

if(NOT EMSCRIPTEN)
  add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_SOURCE_DIR}/resources"
      $<IF:$<CONFIG:Release>,"${RELEASE_RESOURCE_DIR}","${DEBUG_RESOURCE_DIR}">
  )
endif()
