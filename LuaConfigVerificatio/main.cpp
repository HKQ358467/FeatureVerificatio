extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <iostream>

int main() {
    lua_State *lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
	std::string scriptPath = "config.lua";
	int status = luaL_loadfile(lua_state, scriptPath.c_str()) || lua_pcall(lua_state, 0, LUA_MULTRET, 0);

    if (status != LUA_OK) {
        std::cerr << "Cannot run config file: " << lua_tostring(lua_state, -1);
        return 1;
    }

    lua_getglobal(lua_state, "ip");
    lua_getglobal(lua_state, "port");

    if (!lua_isstring(lua_state, -2)) {
        std::cerr << "IP should be a string\n";
        return 1;
    }

    if (!lua_isnumber(lua_state, -1)) {
        std::cerr << "Port should be a number\n";
        return 1;
    }

    std::string ip = lua_tostring(lua_state, -2);
    int port = lua_tonumber(lua_state, -1);

    std::cout << "IP: " << ip << "\n";
    std::cout << "Port: " << port << "\n";

    lua_close(lua_state);

    return 0;
}