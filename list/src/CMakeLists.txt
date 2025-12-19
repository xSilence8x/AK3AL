set(SOURCES_LIST list.c data.c)

set(HEADERS_LIST include/list.h include/data.h)

set(LIBNAME_LIST "list")

include(FetchContent)
FetchContent_Declare(
  ioutils
  GIT_REPOSITORY https://ioutils:glpat-Hyz6BP2Mb3PjPidodW9qYm86MQp1OmptCA.01.0y06iozwr@git.fai.utb.cz/ap4al/common/ioutils.git
)

FetchContent_MakeAvailable(ioutils)

FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:glpat-EMUjOEVqEKIvaGNxPz825W86MQp1OmpsCA.01.0y0hn9zdb@git.fai.utb.cz/ap4al/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

add_library(${LIBNAME_LIST} ${SOURCES_LIST} ${HEADERS_LIST})
target_link_libraries(${LIBNAME_LIST} PUBLIC myMalloc ioutils)
target_include_directories(${LIBNAME_LIST} PUBLIC include)
