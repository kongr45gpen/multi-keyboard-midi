// dllmain.cpp : Defines the entry point for the DLL application.
#define _COMPILING_0631D5DB_7874_48ED_9DA8_D90B9694CE89

#include "Windows.h"
#include "hook.h"
#include <tchar.h>
#include <iostream>


#pragma data_seg(".SHR")
HWND hWndServer = NULL;
#pragma data_seg()
#pragma comment(linker, "/section:.SHR,rws")

HINSTANCE hInstance;
UINT UWM_HOOK;
HHOOK hook;


// Forward declaration
static LRESULT CALLBACK msghook(int nCode, WPARAM wParam, LPARAM lParam);

/****************************************************************
*                               DllMain
* Inputs:
*       HINSTANCE hInst: Instance handle for the DLL
*       DWORD Reason: Reason for call
*       LPVOID reserved: ignored
* Result: BOOL
*       TRUE if successful
*       FALSE if there was an error (never returned)
* Effect:
*       Initializes the DLL.
****************************************************************/

bool __stdcall DllMain(HINSTANCE hInst, DWORD Reason, LPVOID reserved)
{
	switch (Reason)
	{ /* reason */
	 //**********************************************
	 // PROCESS_ATTACH
	 //**********************************************
	case DLL_PROCESS_ATTACH:
		// Save the instance handle because we need it to set the hook later
		hInstance = hInst;
		// This code initializes the hook notification message
		UWM_HOOK = RegisterWindowMessage(UWM_HOOK_MSG);
		std::cout << "DLL process attached" << std::endl;
		setHook(NULL);
		return TRUE;

		//**********************************************
		// PROCESS_DETACH
		//**********************************************
	case DLL_PROCESS_DETACH:
		// If the server has not unhooked the hook, unhook it as we unload
		if (hWndServer != NULL)
			clearHook(hWndServer);
		std::cout << "DLL process detached" << std::endl;
		return TRUE;
	} /* reason */
}

__declspec(dllexport) BOOL WINAPI setHook(HWND hWnd)
{
	if (hWndServer != NULL)
		return FALSE;
	hook = SetWindowsHookEx(
		//WH_GETMESSAGE,
		WH_KEYBOARD,
		(HOOKPROC)msghook,
		hInstance,
		0);
	if (hook != NULL)
	{ /* success */
		std::cout << "Hook set in DLL" << std::endl;
		hWndServer = hWnd;
		return TRUE;
	} /* success */
	std::cout << "HOOK FAIL " << GetLastError() << std::endl;
	return FALSE;
} // SetMyHook

/****************************************************************
*                             clearMyHook
* Inputs:
*       HWND hWnd: Window whose hook is to be cleared
* Result: BOOL
*       TRUE if the hook is properly unhooked
*       FALSE if you gave the wrong parameter
* Effect:
*       Removes the hook that has been set.
****************************************************************/
__declspec(dllexport) BOOL WINAPI clearHook(HWND hWnd)
{
	if (hWnd != hWndServer)
		return FALSE;
	BOOL unhooked = UnhookWindowsHookEx(hook);
	if (unhooked)
		hWndServer = NULL;
	return unhooked;
}

/****************************************************************
*                              msghook
* Inputs:
*       int nCode: Code value
*       WPARAM wPaSram: parameter
*       LPARAM lParam: parameter
* Result: LRESULT
*
* Effect:
*
* Notes:
*       This must be a CALLBACK function or it will not work!
****************************************************************/

static LRESULT CALLBACK msghook(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0) {
		// Caps lock is off, pass
		return CallNextHookEx(hook, nCode, wParam, lParam);
	} else {
		// Caps lock is on, swallow the event
		return 1;
	}
} // msghook