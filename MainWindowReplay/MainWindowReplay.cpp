//MainWindowReplay
#include<Windows.h>
#include"resource.h"

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";
CONST CHAR g_szGREAT_LOGIN[] = "UncleFactor";
CONST CHAR g_szGREAT_PASSWORD[] = "FiveHundredBullets5000";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_szCLASS_NAME;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		g_szCLASS_NAME,
		g_szCLASS_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND ButtonEnter = CreateWindow
		(
			"BUTTON", "Начать работу", WS_VISIBLE | WS_CHILD,
			500, 250, 130, 30, hwnd, (HMENU)IDC_BTN_ENTER, NULL, NULL
		);
		
	}
	/*case WM_LBUTTONDOWN:
	{
		CHAR sz_FileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(0);

		GetModuleFileName(hInstance, sz_FileName, MAX_PATH);
		MessageBox(hwnd, sz_FileName, "Данная программа находится в:", MB_OK | MB_ICONINFORMATION);
	}
		break;*/
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTN_ENTER:DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc, 0);
			break;
		}
		break;
	case WM_CLOSE:
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Info", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			DestroyWindow(hwnd); break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
	{
		/*CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};*/
	}
		switch (LOWORD(wParam))
		{
		case IDENTER:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)buffer);
			if (strcmp(buffer, g_szGREAT_LOGIN) == 0)
			{
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_GETTEXT, SIZE, (LPARAM)buffer);
				if (strcmp(buffer, g_szGREAT_PASSWORD) == 0)
				{
					MessageBox(hwnd, "Успешный вход", "info", MB_OK | MB_TASKMODAL | MB_ICONINFORMATION);
				}
				else MessageBox(hwnd, "Неверный пароль", "error", MB_OK | MB_TASKMODAL | MB_ICONERROR);
			}
			else MessageBox(hwnd, "Неверный логин", "error", MB_OK | MB_TASKMODAL | MB_ICONERROR);
			break;
		}
		case IDCANCEL: EndDialog(hwnd, 0); break;
		break;
		}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}