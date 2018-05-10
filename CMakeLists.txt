project(MeFFoS)

cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
  ${CMAKE_CURRENT_SOURCE_DIR}/boost
)

add_definitions(-DSAMPGDK_AMALGAMATION)
add_definitions(-DCPPCONN_PUBLIC_FUNC=)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mysql)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/cppconn)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

add_samp_plugin(MeFFoS
  amxplugin.cpp
  Main.cpp
  Main.h
  Main.def
  sampgdk.c
  sampgdk.h
  Server.cpp
  Server.h
  Player.cpp
  Player.h
  Commands.cpp
  Commands.h
  streamer.cpp
  streamer.hpp
  callbacksPlugins.cpp
  Dialogs.cpp
  Dialogs.h
  Functions.cpp
  Functions.h
  House.cpp
  House.h
)

target_link_libraries(${PROJECT_NAME} mysqlcppconn)