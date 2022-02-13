//MainWindow
#include<Windows.h>
#include<stdio.h>
#include"resource.h"

CONST CHAR g_szCLASS_NAME[] = "MyWindowClass";	//Глобальная переменная имя класса
CONST CHAR g_szTitle[] = "MyFirstTitleWindow";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;	//Создаём объект структуры WindowClassExtended	//wc - window class
	//Инициализация полей структуры:
	wc.cbSize = sizeof(WNDCLASSEX);	//Размер структуры
	wc.style = 0;	//Стилей никаких нет
	wc.lpfnWndProc = WndProc;		//Указатель на процедуру окна. lp - long pointer, fn - function
	wc.cbClsExtra = 0;	//Дополнительная память для окна нам не нужна
	wc.cbWndExtra = 0;	
	wc.hInstance = hInstance;	//Наш первый принимаемый параметр
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_GLOBAL));  //Иконка в панели задач
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_GLOBAL)); //Small icon(Заголовок окна)
	wc.hIcon = (HICON)LoadImage(hInstance, "Icon1.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "ConnectGlobe.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));	//Установление курсора
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//Установление заливки фона окна
	wc.lpszClassName = g_szCLASS_NAME;		//g_sz - global string zero
	wc.lpszMenuName = NULL;	//Меню отсутствует

	if (!RegisterClassEx(&wc))	//Если не зарегистрирован класс окна
	{
		//Выдаём окно сообщения с ошибкой:
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)Создание окна:
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,	//exStyle
		g_szCLASS_NAME,		//Имя класса окна
		g_szCLASS_NAME,		//Заголовок окна
		WS_OVERLAPPEDWINDOW,//Стиль окна overlapped всегда задаётся для главного окна программы
		window_start_x, window_start_y, //Позиция окна на экране
		window_width, window_height, //Размер окна
		NULL,		//Родительсоке окно
		NULL,		//Меню отсутвует
		hInstance,	//*.exe - файл окна
		NULL		//Последний параметр всегда равен NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation faild", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);		//Задаём режим отображения окна
	UpdateWindow(hwnd);		//Прорисовка окна (отправляем сообщение WM_PAINT)

	//3)Запускаем цикл сообщений:
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
	case WM_CREATE:		//Создаются элементы окна
		break;
	case WM_COMMAND:	//Обработка комманд нажатия кнопок, и других элементов окна
		break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CONST INT SIZE = 256;
		CHAR buffer[SIZE]{};
		SendMessage(hwnd, WM_GETTEXT, SIZE, (LPARAM)buffer);
		sprintf
		(
			buffer, "%s Position: %dx%d, Size: %dx%d",
			g_szTitle,
			rect.left, rect.top,	//позиция окна
			rect.right - rect.left, rect.bottom - rect.top	//Размер окна
		);
			//%s - строка
			//%d - decimal(десятичное число)
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_CLOSE:		//Закрытие окна
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Шо, внатуре?", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			//MessageBox(hwnd, "Та лучше б двери закрыли :-)", "Info", MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd); break;
		//case IDNO:MessageBox(hwnd, "Это хорошо", "Info", MB_OK | MB_ICONINFORMATION); break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}