#include "discordia_api.h"
#include "lua_functions.h"
#include <lua.hpp>

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

  // TODO: Config file

  luaL_dostring(lua, "Discordia:id()");
  api->construct_rpc();
  
  // Clean up the lua state
  lua_close(lua);
}
