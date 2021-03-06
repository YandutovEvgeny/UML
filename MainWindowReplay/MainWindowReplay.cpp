//MainWindowReplay
#include<Windows.h>
#include"resource.h"

CONST CHAR g_szCLASS_NAME[] = "Окно авторизации";
CONST CHAR g_szGREAT_LOGIN[] = "admin";
CONST CHAR g_szGREAT_PASSWORD[] = "admin";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WebDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_GLOBAL));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_GLOBAL));
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
			"BUTTON", "Авторизироваться", WS_VISIBLE | WS_CHILD,
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

//Процедура вызова диалогового окна отвечающего за авторизацию:
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_GLOBAL));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDENTER:
		{
			CHAR buffer[MAX_PATH]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
			if (strcmp(buffer, g_szGREAT_LOGIN) == 0)
			{
				SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_GETTEXT, MAX_PATH, (LPARAM)buffer);
				if (strcmp(buffer, g_szGREAT_PASSWORD) == 0)
				{
					//MessageBox(hwnd, "Успешный вход", "Info", MB_OK | MB_ICONINFORMATION); break;
					DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, WebDlgProc, 0);
				}
			}
			else MessageBox(hwnd, "Неверный пароль или логин", "Error", MB_OK | MB_ICONERROR); break;
		}
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

//Процедура вызова диалогового окна отвечающего за "Wed-интерфейс роутера":
BOOL CALLBACK WebDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_GLOBAL));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTN_RELOAD: MessageBox(hwnd, "Конфигурация обновлена!", "Info", MB_OK | MB_ICONINFORMATION); break;
		}
		break;
	case WM_SIZE:
	{
		SCROLLINFO scrInfo;
		scrInfo.cbSize = sizeof(SCROLLINFO);
		scrInfo.nPage = HIWORD(lParam);
		scrInfo.nMin = 0;
		scrInfo.nMax = 1000;
		scrInfo.fMask = SIF_RANGE | SIF_PAGE;
		SetScrollInfo(hwnd, SB_VERT, &scrInfo, TRUE);
	}
	break;
	case WM_VSCROLL:
	{
		SCROLLINFO scrInfo;
		scrInfo.cbSize = sizeof(SCROLLINFO);
		scrInfo.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SB_VERT, &scrInfo);
		int currentPos = scrInfo.nPos;
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:scrInfo.nPos -= 1; break;
		case SB_LINEDOWN:scrInfo.nPos += 1; break;
		case SB_THUMBTRACK:scrInfo.nPos = scrInfo.nTrackPos; break;
		default:break;
		}
		scrInfo.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &scrInfo, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &scrInfo);
		int yScroll = currentPos - scrInfo.nPos;
		ScrollWindow(hwnd, 0, yScroll, NULL, NULL);
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}