#pragma once

#include <lua.hpp>
#include <string>

class LuaCore {
private:
  lua_State *L;

public:
  LuaCore();
  ~LuaCore();

  void run(const std::string &chunk_name);

  void parse(const std::string &script, const std::string &chunk_name);

  void push_constant(const std::string &name, double value);
  void push_function(const std::string &name, lua_CFunction func);
  void push_functiontable(const std::string &name, lua_CFunction func);
};
