add_executable(app main.c)

include(FetchContent)
FetchContent_Declare(
  ioutils
  GIT_REPOSITORY https://ioutils:glpat-Hyz6BP2Mb3PjPidodW9qYm86MQp1OmptCA.01.0y06iozwr@git.fai.utb.cz/ap4al/common/ioutils.git
)

FetchContent_MakeAvailable(ioutils)

target_link_libraries(app dtmfGenerator ioutils)
