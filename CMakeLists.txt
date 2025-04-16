cmake_minimum_required(VERSION 3.15)
project(Discordia LANGUAGES CXX VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Handle lua
set(LUA_DEFAULT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/External/lua-5.4.7")
set(LUA_ROOT "${LUA_DEFAULT_ROOT}" CACHE PATH "Path to the lua root directory.")

set(LUA_INCLUDE "${LUA_ROOT}/include")
set(LUA_LIB "${LUA_ROOT}/lib")

if (NOT EXISTS "${LUA_ROOT}")
  message(SEND_ERROR "Could not find lua root directory at ${LUA_ROOT}.")
endif()

if (NOT EXISTS "${LUA_INCLUDE}/lua.h")
  message(SEND_ERROR "Could not find lua.h file at ${LUA_INCLUDE}.")
else()
  message(STATUS "Lua include files found at ${LUA_INCLUDE}!")
endif()

find_library(LUA_LIBS
  NAMES lua lua-5.4 lua5.4 Lua
  PATHS "${LUA_LIB}"
  NO_DEFAULT_PATH
)

if (NOT LUA_LIBS)
  message(SEND_ERROR "Lua libraries not found at ${LUA_LIB}.")
else()
  message(STATUS "Lua libraries found at ${LUA_LIB}!")
endif()

# Handle DiscordRPC
set(DISCORD_DEFAULT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/External/discord-rpc")
set(DISCORD_ROOT "${DISCORD_DEFAULT_ROOT}" CACHE PATH "Path to the discord rpc root directory")

set(DISCORD_INCLUDE "${DISCORD_ROOT}/include")
set(DISCORD_LIB "${DISCORD_ROOT}/lib")

if (NOT EXISTS "${DISCORD_ROOT}")
  message(SEND_ERROR "Could not find discord root directory at ${DISCORD_ROOT}.")
endif()

if (NOT EXISTS "${DISCORD_INCLUDE}/discord_rpc.h")
  message(SEND_ERROR "Could not find discord_rpc.h file at ${DISCORD_INCLUDE}.")
else()
  message(STATUS "Discord include files found at ${DISCORD_INCLUDE}!")
endif()

find_library(DISCORD_LIBS
  NAMES discord-rpc discordrpc DiscordRPC DiscordRpc
  PATHS "${DISCORD_LIB}"
  NO_DEFAULT_PATH
)

if (NOT DISCORD_LIBS)
  message(SEND_ERROR "Discord libraries not found at ${DISCORD_LIB}.")
else()
  message(STATUS "Discord libraries found at ${DISCORD_LIB}!")
endif()


add_executable(${PROJECT_NAME}
  Discordia/main.cpp
  Discordia/discordia_api.cpp
  Discordia/lua_functions.cpp

  Discordia/util.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  Discordia
  
  # Discord
  ${DISCORD_INCLUDE}
  
  # Lua
  ${LUA_INCLUDE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  # Discord
  ${DISCORD_LIBS}
  
  # Lua
  ${LUA_LIBS}
)
