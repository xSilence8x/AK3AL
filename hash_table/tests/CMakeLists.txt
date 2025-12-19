set(GTEST_TESTS tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

add_executable(${GTEST_TESTS} tests.cpp fff.h DataMock.h DataMock.cpp)
target_link_libraries(${GTEST_TESTS} PRIVATE gtest gmock gtest_main hashTable stdc++)

gtest_discover_tests(${GTEST_TESTS})

file(COPY ${CMAKE_SOURCE_DIR}/test_files DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
