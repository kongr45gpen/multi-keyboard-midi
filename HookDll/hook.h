#pragma once

#include "Windows.h"

#define UWM_HOOK_MSG \
	_T("UMW_HOOK-" \
        "{0631D5DB-7874-48ED-9DA8-D90B9694CE89}")

extern "C" {
#ifdef _COMPILING_0631D5DB_7874_48ED_9DA8_D90B9694CE89
#define LIBSPEC __declspec(dllexport)
#else
#define LIBSPEC __declspec(dllimport)
#endif // _COMPILING_0631D5DB_7874_48ED_9DA8_D90B9694CE89
	LIBSPEC BOOL WINAPI setHook(HWND hWnd);
	LIBSPEC BOOL WINAPI clearHook(HWND hWnd);
#undef LIBSPEC
}