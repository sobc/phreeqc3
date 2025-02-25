#include "Lua/LuaCore.hpp"
#include <Phreeqc.h>
#include <memory>
class LuaInitializer {
private:
  std::weak_ptr<LuaCore> lua_instance;
  std::weak_ptr<Phreeqc> phreeqc;

public:
  LuaInitializer(LuaCore *lua_instance, Phreeqc *phreeqc);

private:
  enum class LuaInitializerType { CONSTANT, FUNCTION, FUNCTIONTABLE };

  struct LuaInitializerData {
    LuaInitializerType type;
    std::string name;
    union {
      double constant;
      lua_CFunction function;
    } data;
  };
};
