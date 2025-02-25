#include <Phreeqc.h>
#include <lua.hpp>

template <typename Func, typename... Args>
int push_phreeqc_data(lua_State *L, Func rate_func, Args... args) {
  auto phreeqc =
      static_cast<Phreeqc **>(lua_touserdata(L, lua_upvalueindex(1)));
  lua_pushnumber(L, ((*phreeqc)->*rate_func)(args...));
  return 1;
}

static int err_no_newindex(lua_State *L) {
  return luaL_error(L, "No newindex");
}

static const struct luaL_Reg pqc_func_vec[] = {
    {"M",
     [](lua_State *L) -> int {
       return push_phreeqc_data(L, &Phreeqc::get_rate_m);
     }},
    {"time",
     [](lua_State *L) -> int {
       return push_phreeqc_data(L, &Phreeqc::get_rate_time);
     }},
    {"SI",
     [](lua_State *L) -> int {
       const char *name = lua_tostring(L, 2);
       return push_phreeqc_data(L, &Phreeqc::get_saturation_index, name);
     }},
    {"ACT",
     [](lua_State *L) -> int {
       const char *name = lua_tostring(L, 2);
       return push_phreeqc_data(L, &Phreeqc::get_activity, name);
     }},
    {"__newindex", err_no_newindex},
    {NULL, NULL}};
