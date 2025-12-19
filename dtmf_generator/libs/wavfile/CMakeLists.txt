set(SOURCES wavfile.c)

set(HEADER_LIST wavfile.h)

set(LIBNAME "wavfile")

add_library(${LIBNAME} ${SOURCES} ${HEADER_LIST})
target_include_directories(${LIBNAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})