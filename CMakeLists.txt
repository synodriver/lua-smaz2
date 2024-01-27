cmake_minimum_required(VERSION 3.27)
project(lua_smaz2 C)

set(CMAKE_C_STANDARD 11)

link_directories("D:\\conda\\envs\\py310\\Library\\lib" D:\\conda\\envs\\py310\\Library\\bin)
include_directories(D:\\conda\\envs\\py310\\Library\\include ./dep)


add_library(smaz2 SHARED src/lsmaz2.c dep/smaz2.c)
target_link_libraries(smaz2 lua)
