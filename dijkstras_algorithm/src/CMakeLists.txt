set(SOURCES_HEAP heap.c data.c map.c)

set(HEADERS_HEAP include/heap.h include/data.h include/map.h)

set(LIBNAME_HEAP "heap")

include(FetchContent)
FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:glpat-EMUjOEVqEKIvaGNxPz825W86MQp1OmpsCA.01.0y0hn9zdb@git.fai.utb.cz/ap4al/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

add_library(${LIBNAME_HEAP} ${SOURCES_HEAP} ${HEADERS_HEAP})
target_link_libraries(${LIBNAME_HEAP} PUBLIC myMalloc)
target_include_directories(${LIBNAME_HEAP} PUBLIC include)

set(SOURCES_DIJKSTRA dijkstra.c)

set(HEADERS_DIJKSTRA include/dijkstra.h)

set(LIBNAME_DIJKSTRA "dijkstra")

add_library(${LIBNAME_DIJKSTRA} ${SOURCES_DIJKSTRA} ${HEADERS_DIJKSTRA})
target_link_libraries(${LIBNAME_DIJKSTRA} PUBLIC ${LIBNAME_HEAP})
target_include_directories(${LIBNAME_DIJKSTRA} PUBLIC include)
