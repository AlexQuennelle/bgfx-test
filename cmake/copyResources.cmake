file(
    COPY "${CMAKE_SOURCE_DIR}/resources"
    DESTINATION
    ${DEST_DIR}/..
    PATTERN "shaders" EXCLUDE
)
if(CONFIG STREQUAL "Release")
else()
endif()
