#include "lua_functions.h"
#include "discordia_api.h"
#include <iostream>

int Discordia::Lua::l_id(lua_State* lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  const char* appid = luaL_checkstring(lua, 2);
  
  self->id(appid);
  return 0;
}

int Discordia::Lua::l_txt(lua_State *lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  const char* details = luaL_checkstring(lua, 2);
  const char* state = luaL_checkstring(lua, 3);

  self->details(details, state);
  return 0;
}

int Discordia::Lua::l_bimg(lua_State *lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  const char* key = luaL_checkstring(lua, 2);
  const char* text = luaL_checkstring(lua, 3);

  self->large_image(key, text);
  return 0;
}

int Discordia::Lua::l_simg(lua_State* lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  const char* key = luaL_checkstring(lua, 2);
  const char* text = luaL_checkstring(lua, 3);

  self->small_image(key, text);
  return 0;
}

int Discordia::Lua::l_tstart(lua_State *lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  int64_t start = static_cast<int64_t>(luaL_checkinteger(lua, 2));

  self->start_time(start);
  return 0;
}

int Discordia::Lua::l_tend(lua_State *lua)
{
  DiscordiaApi* self = *reinterpret_cast<DiscordiaApi**>(luaL_checkudata(lua, 1, Discordia::Lua::discordia_mm));
  int end = lua_tonumber(lua, 2);

  self->end_time(end);
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

    lua_pushcfunction(lua, Discordia::Lua::l_txt);
    lua_setfield(lua, -2, "details");

    lua_pushcfunction(lua, Discordia::Lua::l_simg);
    lua_setfield(lua, -2, "small_image");
    
    lua_pushcfunction(lua, Discordia::Lua::l_bimg);
    lua_setfield(lua, -2, "large_image");

    lua_pushcfunction(lua, Discordia::Lua::l_tstart);
    lua_setfield(lua, -2, "start_time");
    
    lua_pushcfunction(lua, Discordia::Lua::l_tend);
    lua_setfield(lua, -2, "end_time");
    
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
