set(SOURCES heap.c data.c)

set(HEADER_LIST 
    include/heap.h
    include/data.h
  )

set(LIBNAME "heap")

add_library(${LIBNAME} ${SOURCES} ${HEADER_LIST})

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

target_link_libraries(${LIBNAME} PUBLIC myMalloc ioutils)
target_include_directories(${LIBNAME} PUBLIC include)
