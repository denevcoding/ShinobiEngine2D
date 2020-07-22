#ifndef _STDAFX_H_
#define _STDAFX_H_

//=============================================================================
#ifdef _WIN32

#pragma pack(1)
#pragma warning(disable:4996) // Using open/close/read... for file access

// Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define WIN64_LEAN_AND_MEAN
#include <windows.h>

//This we can set the macros of GLFW
#include "glfw3.h"
#include "litegfx.h" //LiteGFX
#include "stb_image.h"
//Open GL
//Open AL

#include <io.h> //Averiguar que es
//=============================================================================
#elif defined(__APPLE__)

#include "TargetConditionals.h"

#if defined(__MACH__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
//#include <unistd.h>
//#include <GL/glfw.h>

#define GL_BGRA_EXT GL_BGRA

#endif
#endif
//=============================================================================
// PNG loading library
//#include "lodepng.h"
//=============================================================================
// Common includes
#include <vector>
#include <map>

#include <algorithm>    // std::min
#include <math.h> //Revisar includes que estan deprecados y no sirven


#include <iostream>
#include <fstream> 
#include <sstream>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <objBase.h>

#include <assert.h>

#include <ctime>
#include <tgmath.h>

//=============================================================================
//Maths


#endif







