set(SOURCES_VECTOR vector.c)

set(HEADERS_VECTOR include/vector.h)

set(LIBNAME_VECTOR "vector")

include(FetchContent)

FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:glpat-EMUjOEVqEKIvaGNxPz825W86MQp1OmpsCA.01.0y0hn9zdb@git.fai.utb.cz/ap4al/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

add_library(${LIBNAME_VECTOR} ${SOURCES_VECTOR} ${HEADERS_VECTOR})
target_link_libraries(${LIBNAME_VECTOR} PUBLIC myMalloc)
target_include_directories(${LIBNAME_VECTOR} PUBLIC include)

set(SOURCES_DTMF dtmf.c)

set(HEADERS_DTMF include/dtmf.h)

set(LIBNAME_DTMF "dtmfGenerator")

add_library(${LIBNAME_DTMF} ${SOURCES_DTMF} ${HEADERS_DTMF})
target_link_libraries(${LIBNAME_DTMF} PUBLIC ${LIBNAME_VECTOR} wavfile m)
target_include_directories(${LIBNAME_DTMF} PUBLIC include)