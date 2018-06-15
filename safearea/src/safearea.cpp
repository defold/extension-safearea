#define LIB_NAME "safearea"

#include "safearea.h"
#include <dmsdk/sdk.h>

static dmExtension::Result AppInitializeSafearea(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeSafearea(dmExtension::Params* params)
{
    float bg_color[3] = {0.0f, 0.0f, 0.0f};
    bg_color[0] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_red", bg_color[0]);
    bg_color[1] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_green", bg_color[1]);
    bg_color[2] = dmConfigFile::GetFloat(params->m_ConfigFile, "safearea.background_blue", bg_color[2]);

    return safeareans::Init(bg_color) ? dmExtension::RESULT_OK : dmExtension::RESULT_INIT_ERROR;
}

DM_DECLARE_EXTENSION(safearea, LIB_NAME, 0, 0, InitializeSafearea, 0, 0, 0)
