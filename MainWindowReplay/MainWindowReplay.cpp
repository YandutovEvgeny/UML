//MainWindowReplay
#include<Windows.h>

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
			"BUTTON", "Войти", WS_VISIBLE | WS_CHILD,
			450, 500, 80, 30, hwnd, NULL, NULL, NULL
		);
		HWND ButtonRegistration = CreateWindow
		(
			"BUTTON", "Регистрация", WS_VISIBLE | WS_CHILD,
			550, 500, 120, 30, hwnd, NULL, NULL, NULL
		);
		break;
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

