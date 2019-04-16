// KeyboardTest3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "KeyboardTest3.h"
#include "guicon.h"
#include "hidusage.h"


#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HHOOK hHook;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	tagKBDLLHOOKSTRUCT* tag;
	tag = (tagKBDLLHOOKSTRUCT*) lParam;
	std::cout << nCode << " " << wParam << " " << tag->dwExtraInfo << " " << tag->flags << " " << tag->scanCode << " " << tag->time << " " << tag->vkCode << std::endl;
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

// register Scanner
void InitRawInput(HWND hwnd) {

	RAWINPUTDEVICE Rid[1];
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hwnd;
	if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == false)
	{
		std::cout << "Registration failed";
		return;
	}
	std::cout << "Registration updated";
}

int RawInput(HWND hwnd)
{
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;

	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
	{
		std::cout << "Errors...";
		return 1;
	}

	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
	{
		std::cout << "Initialization failed...";
		return 1;
	}

	int nNoOfDevices = 0;
	if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) == ((UINT)-1))
	{
		// Error
		return 1;
	}

	RID_DEVICE_INFO rdi;
	rdi.cbSize = sizeof(RID_DEVICE_INFO);

	for (int i = 0; i < nNoOfDevices; i++)
	{
		UINT size = 256;
		TCHAR tBuffer[256] = { 0 };
		tBuffer[0] = '\0';
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
		{
			// Error in reading device name
			std::cout << "error reading device name" << std::endl;
		}

		std::cout << "Device Name: " << tBuffer << std::endl;
		//_tprintf(L"Device Name: %s\n", tBuffer);

		UINT cbSize = rdi.cbSize;
		if (GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0)
		{
			// Error in reading information
		}

		if (rdi.dwType == RIM_TYPEKEYBOARD)
		{
			std::cout << "Keyboard Mode:" << rdi.keyboard.dwKeyboardMode << std::endl;
			std::cout << "Number of function keys:" << rdi.keyboard.dwNumberOfFunctionKeys << std::endl;
			std::cout << "Number of indicators:" << rdi.keyboard.dwNumberOfIndicators << std::endl;
			std::cout << "Number of keys total: " << rdi.keyboard.dwNumberOfKeysTotal << std::endl;
			std::cout << "Type of the keyboard: " << rdi.keyboard.dwType << std::endl;
			std::cout << "Subtype of the keyboard: " << rdi.keyboard.dwSubType << std::endl;
			std::cout << "UsagePage/Usage of the keyboard: " << rdi.hid.usUsagePage << " " << rdi.hid.usUsage << std::endl;
			std::cout << "Product ID: " << rdi.hid.dwProductId;
			std::cout << "***********************" << std::endl;
		}
	}

	free(pRawInputDeviceList);

	//HWND temper = (HWND)w.effectiveWinId();
	InitRawInput(hwnd);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KEYBOARDTEST3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	// THE CODE IS HERE!
	RedirectIOToConsole();
	fprintf(stdout, "Test output to stdout\n");
	fprintf(stderr, "Test output to stderr\n");
	std::cout << "Starting programme\r\n";
	// We don't need to do a normal hook, at least for now
	//hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYBOARDTEST3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYBOARDTEST3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KEYBOARDTEST3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   RedirectIOToConsole();
   RawInput(hWnd);

   UpdateWindow(hWnd);

   //RawInput(hWnd);


   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_INPUT: {
		UINT dwSize;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
			sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (lpb == NULL) {
			return 0;
		}

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize,
			sizeof(RAWINPUTHEADER)) != dwSize)
			OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			std::cout << "Make: " << raw->data.keyboard.MakeCode << std::endl;
			std::cout << "Flags: " << raw->data.keyboard.Flags << std::endl;
			std::cout << "Reserved: " << raw->data.keyboard.Reserved << std::endl;
			std::cout << "ExtraInformation: " << raw->data.keyboard.ExtraInformation << std::endl;
			std::cout << "Message: " << raw->data.keyboard.Message << std::endl;
			std::cout << "VKey: " << raw->data.keyboard.VKey << std::endl;
			std::cout << "Device: " << raw->header.hDevice << std::endl;
			std::cout << std::endl;
		}
		
		delete[] lpb;
		return 0;
	}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
