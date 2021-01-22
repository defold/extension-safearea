#define LIB_NAME "safearea"

#include "safearea.h"
#include <dmsdk/sdk.h>

static dmExtension::Result AppInitializeSafearea(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static int GetInsets(lua_State* L)
{
    safeareans::Insets insets = {
        .bottom = 0.0f,
        .left = 0.0f,
        .right = 0.0f,
        .top = 0.0f,
    };

    safeareans::GetInsets(&insets);

    lua_newtable(L);
    lua_pushnumber(L, insets.bottom);
    lua_setfield(L, -2, "bottom");
    lua_pushnumber(L, insets.left);
    lua_setfield(L, -2, "left");
    lua_pushnumber(L, insets.right);
    lua_setfield(L, -2, "right");
    lua_pushnumber(L, insets.top);
    lua_setfield(L, -2, "top");

    return 1;
}


static const luaL_reg SafeArea_methods[] =
{
    {"get_insets", GetInsets},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, "safearea", SafeArea_methods);
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
