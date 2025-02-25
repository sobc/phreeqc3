#include "LuaCore.hpp"
#include "lua.h"
#include <lua.hpp>

static int error_read_only(lua_State *L) {
  return luaL_error(L, "read-only variable");
}

LuaCore::LuaCore() : L(luaL_newstate()) {
  luaL_openlibs(this->L);

  luaJIT_setmode(this->L, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
}

LuaCore::~LuaCore() { lua_close(this->L); }

void LuaCore::run(const std::string &chunk_name) {
  lua_getglobal(this->L, chunk_name.c_str());
  lua_pcall(this->L, 0, 0, 0);
}

void LuaCore::parse(const std::string &script, const std::string &chunk_name) {
  luaL_loadbuffer(this->L, script.c_str(), script.size(),
                  std::string(chunk_name + ".debug").c_str());
  lua_setglobal(this->L, chunk_name.c_str());
}

void LuaCore::push_constant(const std::string &name, double value) {
  lua_pushnumber(this->L, value);
  lua_setglobal(this->L, name.c_str());
}

void LuaCore::push_function(const std::string &name, lua_CFunction func) {
  lua_pushcfunction(this->L, func);
  lua_setglobal(this->L, name.c_str());
}

void LuaCore::push_functiontable(const std::string &name, lua_CFunction func) {
  const struct luaL_Reg funcs[] = {
      {"__index", func}, {"__newindex", error_read_only}, {NULL, NULL}};

  lua_newtable(this->L);
  luaL_newmetatable(this->L, std::string("metatable." + name).c_str());
  luaL_setfuncs(this->L, funcs, 0);
  lua_setmetatable(this->L, -2);

  lua_setglobal(this->L, name.c_str());
}
