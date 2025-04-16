#include "discordia_api.h"
#include "lua_functions.h"
#include "util.h"
#include <filesystem>
#include <iostream>
#include <lua.hpp>
#include <thread>

using namespace std::chrono_literals;

int main()
{
  // Setup the lua state
  lua_State* lua = luaL_newstate();
  luaopen_base(lua);
  luaopen_string(lua);
  luaopen_math(lua);

  // Create the lua user data.
  Discordia::DiscordiaApi* udata = *reinterpret_cast<Discordia::DiscordiaApi**>(lua_newuserdata(lua, sizeof(Discordia::DiscordiaApi*))) = new Discordia::DiscordiaApi();
  Discordia::DiscordiaApi* api = udata;

  Discordia::Lua::l_createmm(lua);

  // Config file search
  std::filesystem::path config_root = Discordia::Util::config_home();
  if (!std::filesystem::exists(config_root))
  {
    std::cerr << "ERROR: The configuration folder " << config_root << " does not exist. Please create it and retry." << std::endl;
    return -1;
  }
  
  std::cout << "INFO: Using configuration folder " << config_root << "." << std::endl;

  std::filesystem::path config_file = config_root / "discordia" / "config.lua";
  if (!std::filesystem::exists(config_file))
  {
    std::cerr << "ERROR: The configuration file " << config_file << " does not exist. Please create it and try again." << std::endl;
    return -1;
  }

  std::cout << "INFO: Using configuration file " << config_file << "." << std::endl;

  // Run lua script.
  std::string string_config = config_file.string();
  int status = luaL_dofile(lua, string_config.c_str());
  if (status != LUA_OK)
  {
    std::cerr << "ERROR: Failed to load Lua script: " << lua_tostring(lua, -1) << std::endl;
    lua_pop(lua, 1);
  }

  status = lua_pcall(lua, 0, 0, 0);
  if (status != LUA_OK)
  {
    std::cerr << "ERROR: Failed to execute Lua script: " << lua_tostring(lua, -1) << std::endl;
    lua_pop(lua, 1);
  }

  // Construct the RPC daemon.
  api->construct_rpc();

  while (true)
  {
    api->update_rpc();
    std::this_thread::sleep_for(1000ms);
  }
  
  // Clean up the lua state
  lua_close(lua);
}
