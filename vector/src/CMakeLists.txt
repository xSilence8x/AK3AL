set(SOURCES vector.c)

set(HEADERS "include/vector.h")

set(LIBNAME "vector")

include(FetchContent)
FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:glpat-EMUjOEVqEKIvaGNxPz825W86MQp1OmpsCA.01.0y0hn9zdb@git.fai.utb.cz/ap4al/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

add_library(${LIBNAME} ${SOURCES} ${HEADERS})
target_link_libraries(${LIBNAME} PUBLIC myMalloc)

target_include_directories(${LIBNAME} PUBLIC include)
