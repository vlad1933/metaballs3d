#pragma once

#include "Common.h"

#include "Lua.h"

typedef float LuaVector3[3];
typedef float LuaVector4[4];

// --------------------------------------------------------------------
// LuaManager
// --------------------------------------------------------------------

class LuaManager
{
public:
    LuaManager();
    virtual ~LuaManager();

    static LuaManager* GetFromState(lua_State* state);

    void DoFile(const std::string& path);
    void DoString(const std::string& buffer);
    void ReportError(const std::string& chunk);
    void RegisterFunction(const std::string& name, lua_CFunction function);

private:
    lua_State* m_luaState;

    // --------------------------------------------------------------------
    // Lua Stack manipulation
    // --------------------------------------------------------------------

public:
    template <class T> void WriteGlobal(const std::string& name, T value)
    {
        PushValue(value);
        lua_setglobal(m_luaState, name.data());
    }

    template <class T> bool ReadGlobal(const std::string& name, T* ref)
    {
        lua_getglobal(m_luaState, name.data());
        return PopValue(ref);
    }

    template <class T> void PushValue(T value)
    {
        lua_pushlightuserdata(m_luaState,(void*)value);
    }

    template <class T> bool PopValue(T* ref)
    {
        if(lua_isuserdata(m_luaState, -1))
        {
            *ref = (T)lua_touserdata(m_luaState,-1);
            lua_pop(m_luaState, 1);
            return true;
        }
        return false;
    }

    // --------------------------------------------------------------------
    // Template specializations
    // --------------------------------------------------------------------

    template <> void PushValue(const std::string& value)
    {
        lua_pushstring(m_luaState,value.data());
    }

    template <> void PushValue(float value)
    {
        lua_pushnumber(m_luaState,value);
    }

    template <> bool PopValue(std::string* ref)
    {
        if(lua_isstring(m_luaState, -1))
        {
            *ref = lua_tostring(m_luaState,-1);
            lua_pop(m_luaState, 1);
            return true;
        }
        return false;
    }

    template <> bool PopValue(float* ref)
    {
        if(lua_isnumber(m_luaState, -1))
        {
            *ref = (float)lua_tonumber(m_luaState,-1);
            lua_pop(m_luaState, 1);
            return true;
        }
        return false;
    }

    template <> bool PopValue(int* ref)
    {
        if(lua_isnumber(m_luaState, -1))
        {
            *ref = (int)lua_tonumber(m_luaState,-1);
            lua_pop(m_luaState, 1);
            return true;
        }
        return false;
    }

    template <> bool PopValue(LuaVector3* ref)
    {
        return PopValue(ref+2) && PopValue(ref+1) && PopValue(ref);
    }
};