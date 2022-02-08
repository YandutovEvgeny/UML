//WinAPI
#include<Windows.h>
#include"resource.h"

//#define MESSAGE_BOX

CONST CHAR LOGININVITATION[] = "Введите логин:";
CONST CHAR PASSWORDINVITATION[] = "Введите пароль:";

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
	//hwnd - Handler to Window (окно)
	//nMsg - сообщение
	//wParam, lParam - параметры сообщения
	switch (uMsg)  //Обрабатываем сообщение
	{
	case WM_INITDIALOG:		   //Инициализация окна, здесь будут добавлятся компоненты
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		//SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETFOCUS, 0, 0);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)LOGININVITATION);
	}
	break;
	case WM_COMMAND:           //Обработчик команд кнопок, полей ввода и тд
	{
		switch (LOWORD(wParam))
		{
		case IDC_BTN_COPY:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);  //Получаем handler текстового поля по номеру его ресурса(IDC_EDIT1)
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)buffer);  //Читает текст
			SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_SETTEXT, 0, (LPARAM)buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		case IDC_EDIT1:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(buffer, LOGININVITATION) == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
				//SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)buffer);
				if (strcmp(buffer, "") == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETTEXT, 0, (LPARAM)LOGININVITATION);
				break;
			}
			break;
		}
		case IDC_EDIT2: 
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE]{};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_GETTEXT, SIZE, (LPARAM)buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(buffer, PASSWORDINVITATION) == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
				if (strcmp(buffer, "") == 0)SendMessage(GetDlgItem(hwnd, IDC_EDIT2), WM_SETTEXT, 0, (LPARAM)PASSWORDINVITATION);
				break;
			}
			break;
		}
		}
	}
	break;
	case WM_CLOSE:  //Обработка закрытия окна пользователем
		EndDialog(hwnd, 0);
	}
	return FALSE;
}