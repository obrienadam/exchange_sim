project(market_maker_sim)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cc")

add_library(mm_sim ${HEADERS} ${SOURCES})

add_executable(run_sim main.cc)
target_link_libraries(run_sim mm_sim)
