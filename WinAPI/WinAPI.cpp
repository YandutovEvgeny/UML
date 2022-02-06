//WinAPI
#include<Windows.h>
#include"resource.h"

//#define MESSAGE_BOX

//Прототип процедуры окна:
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPAram);
//Процедура любого окна принимает всего 4 параметра:
	//1) Окно
	//2) Сообщение
	//3) Два параметра сообщения

INT WINAPI WinMain   //Главная функция, на подобии main(), всегда принимает следующие параметры:
	(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef MESSAGE_BOX
	MessageBox(NULL, "Hello World!", "Info",
		MB_YESNOCANCEL | MB_ICONASTERISK | MB_SYSTEMMODAL | MB_HELP | MB_DEFBUTTON2 |
		MB_RIGHT | MB_SETFOREGROUND);
	//MessageBox - функция для создания окна сообщения, всегда принимает 4 параметра:
		//1) Родительское окно, если его нет ставим NULL
		//2) Сообщение
		//3) Заголовок окна
		//4) Значок и набор кнопок окна, например MB_OK, добавляет кнопку ок в окне
#endif // MESSAGE_BOX

	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	//DialogBoxParam - функция для вызова диалогового окна
		
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPAram)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:break;  //Инициализация окна
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
	}
	break;     
	case WM_CLOSE:  //Закрытие окна
		EndDialog(hwnd, 0);
	}
	return FALSE;
}