#pragma once

#include <lua.hpp>

namespace Discordia::Lua
{
  inline constexpr const char* discordia_mm = "Discordia";

  void l_createmm(lua_State* lua);
  int l_gcmm(lua_State* lua);
  
  int l_id(lua_State* lua);
  int l_txt(lua_State* lua);


  int l_simg(lua_State* lua);
  int l_bimg(lua_State* lua);

  int l_tstart(lua_State* lua);
  int l_tend(lua_State* lua);
}
