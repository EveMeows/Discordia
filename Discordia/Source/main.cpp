#include <lua.hpp>

int main()
{
  lua_State* lua = luaL_newstate();
  luaopen_base(lua);
  luaopen_string(lua);
  luaopen_math(lua);

  // Cooler hello world
  luaL_dostring(lua, "print(\"Hello, Worlds!\")");

  // Clean up the lua state
  lua_close(lua);
}
