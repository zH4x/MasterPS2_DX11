#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif

#include <SDKDDKVer.h>

// C RunTime Header Files
#include <windows.h>
#include <string>

// D3d Related Files
#include <DXGI.h>
#include <d3d11.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3dx9.lib")
#pragma comment(lib, "D3DCompiler.lib")

// Imgui Files
//#include "ImGui/imgui.h"
//#include "ImGui/imgui_impl_dx11.h"
//#include "ImGui/imgui_internal.h"

#include <Detours/detours.h>
#pragma comment( lib, "detours.lib" )

# define M_PI           3.14159265358979323846  /* pi */

typedef unsigned int uint;
