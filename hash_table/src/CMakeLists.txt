set(SOURCES table.c
    data.c
    data_person.c
    data_cstring.c
    hash_private.c)

set(HEADER_LIST 
    include/table.h
    include/data.h
    include/data_person.h
    include/data_cstring.h
    include/hash_private.h
  )

set(LIBNAME "hashTable")

add_library(${LIBNAME} ${SOURCES} ${HEADER_LIST})

include(FetchContent)
FetchContent_Declare(
  myMalloc
  GIT_REPOSITORY https://mymalloc:glpat-EMUjOEVqEKIvaGNxPz825W86MQp1OmpsCA.01.0y0hn9zdb@git.fai.utb.cz/ap4al/common/mymalloc.git
)

FetchContent_MakeAvailable(myMalloc)

target_link_libraries(${LIBNAME} PUBLIC myMalloc)
target_include_directories(${LIBNAME} PUBLIC include)
