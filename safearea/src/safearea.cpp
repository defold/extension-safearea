#define LIB_NAME "safearea"

#include "safearea.h"
#include <dmsdk/sdk.h>

static dmExtension::Result AppInitializeSafearea(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static int GetInsets(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 2);

    safeareans::Insets insets = {
        .bottom = 0.0f,
        .left = 0.0f,
        .right = 0.0f,
        .top = 0.0f,
    };

    safeareans::SafeAreaStatus status = safeareans::GetInsets(&insets);

    lua_newtable(L);
    lua_pushnumber(L, insets.bottom);
    lua_setfield(L, -2, "bottom");
    lua_pushnumber(L, insets.left);
    lua_setfield(L, -2, "left");
    lua_pushnumber(L, insets.right);
    lua_setfield(L, -2, "right");
    lua_pushnumber(L, insets.top);
    lua_setfield(L, -2, "top");

    lua_pushnumber(L, status);

    return 2;
}

static int SetBackgroundColor(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmVMath::Vector4* value = dmScript::CheckVector4(L, 1);

    safeareans::SetBackgroundColor(value->getX(), value->getY(), value->getZ(), value->getW());
    return 0;
}


static const luaL_reg SafeArea_methods[] =
{   
    {"get_insets", GetInsets},
    {"set_background_color", SetBackgroundColor},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, "safearea", SafeArea_methods);

#define SETCONSTANT(name, val) \
    lua_pushnumber(L, (lua_Number) val); \
    lua_setfield(L, -2, #name);\

    SETCONSTANT(STATUS_OK, safeareans::STATUS_OK)
    SETCONSTANT(STATUS_NOT_AVAILABLE, safeareans::STATUS_NOT_AVAILABLE)
    SETCONSTANT(STATUS_NOT_READY_YET, safeareans::STATUS_NOT_READY_YET)

#undef SETCONSTANT
    
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result InitializeSafearea(dmExtension::Params* params)
{
    float bg_color[3] = {0.0f, 0.0f, 0.0f};
    bg_color[0] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_red", bg_color[0]);
    bg_color[1] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_green", bg_color[1]);
    bg_color[2] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_blue", bg_color[2]);

    if (dmConfigFile::GetInt(params->m_ConfigFile, "safearea.resize_game_view", 1)) {
        safeareans::ResizeGameView(bg_color);
    }

    LuaInit(params->m_L);

    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(safearea, LIB_NAME, 0, 0, InitializeSafearea, 0, 0, 0)
