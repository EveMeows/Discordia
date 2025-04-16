#include "lua_functions.h"
#include "discordia_api.h"

int Discordia::Lua::l_id(lua_State* lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  const char* appid = luaL_checkstring(lua, 2);
  
  self->id(appid);
  return 0;
}

int Discordia::Lua::l_gcmm(lua_State *lua)
{
  delete *reinterpret_cast<Discordia::DiscordiaApi**>(lua_touserdata(lua, 1));
  return 0;
}

void Discordia::Lua::l_createmm(lua_State* lua)
{
  if (luaL_newmetatable(lua, Discordia::Lua::discordia_mm))
  {
    lua_pushcfunction(lua, Discordia::Lua::l_id);
    lua_setfield(lua, -2, "id");

    // TODO: Rest of the functions!!!

    // Set index
    lua_pushvalue(lua, -1);
    lua_setfield(lua, -2, "__index");

    // Set garbage collector
    lua_pushcfunction(lua, Discordia::Lua::l_gcmm);
    lua_setfield(lua, -2, "__gc");
  }

  lua_setmetatable(lua, -2);
  lua_setglobal(lua, Discordia::Lua::discordia_mm);
}
