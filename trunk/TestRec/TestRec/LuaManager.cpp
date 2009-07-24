#include "LuaManager.h"

// --------------------------------------------------------------------
// LuaManager
// --------------------------------------------------------------------

LuaManager::LuaManager()
{
    m_luaState = lua_open();
    luaL_openlibs(m_luaState);
    WriteGlobal("__lua_manager", this);
}

LuaManager::~LuaManager()
{
    lua_close(m_luaState);
}

LuaManager* LuaManager::GetFromState(lua_State* state)
{
    LuaManager* luaManager;
    lua_getglobal(state, "__lua_manager");
    luaManager = (LuaManager*)lua_touserdata(state, -1);
    lua_pop(state, 1);
    return luaManager;
}

void LuaManager::DoFile(const std::string& path)
{
    int r = luaL_dofile(m_luaState, path.data());
    if(r != 0)
    {
        ReportError(path);
    }
}

void LuaManager::DoString(const std::string& buffer)
{
    int r = luaL_dostring(m_luaState, buffer.data());
    if(r != 0)
    {
        ReportError("buffer");
    }
}

void LuaManager::ReportError(const std::string& chunk)
{
    printf("Error in %s\n", chunk.data());
    const char* msg = lua_tostring(m_luaState, -1);
    if (msg != NULL)
    {
        printf("%s\n", msg);
    }
    assert(false);
}

void LuaManager::RegisterFunction(const std::string& name, lua_CFunction function)
{
    lua_register(m_luaState, name.data(), function);
}