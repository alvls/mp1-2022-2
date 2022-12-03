#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#include "functions.h"

#define MAXCALC 500
#define MAXTEXT 100
#define MINCALC 20
#define bt_mode1_id 1
#define bt_mode2_id 2
#define bt_done_id 3
#define cb_id 4
#define edt1_id 5
#define edt2_id 6
#define edt3_id 7

HWND hwnd;
HWND subtitle_4;
HWND subtitle_5;
HWND subtitle_7;
HWND edt_nmax;
HWND edt_x;
HWND edt_precision;
HWND exact_precision;
HWND exact_x;
HWND new_x;
HWND bt_mode1;
HWND bt_mode2;
HWND bt_done;
HWND output_zone;
HWND output_dif;
HWND output_n;
HWND output_x;
HWND standard;
HWND style_1;
HWND cb;

int number_of_func = 0, mode = 1, Nmax = 25;
int n, nc, id, id_for_gign;
double x = 0, precision = 0, prec_calc;
double prec_calc;
char text[MAXCALC], c[MAXTEXT];

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}

	else if (message == WM_COMMAND)
	{
		if (LOWORD(wparam) == edt1_id)
		{
			nc = HIWORD(wparam);
			GetWindowText(lparam, c, MAXTEXT);

			if (nc == EN_UPDATE)
			{
				SetWindowText(exact_x, c);
				Nmax = atoi(c);
			}
		}

		if (LOWORD(wparam) == edt2_id)
		{
			nc = HIWORD(wparam);
			GetWindowText(lparam, c, MAXTEXT);

			if (nc == EN_UPDATE)
			{	
				prec_calc = 0;
				char* new_c = c;
				char* temp;

				while (1)
				{
					temp = new_c;
					prec_calc = strtod(new_c, &new_c);

					if (prec_calc == 0 && temp == new_c)
					{
						break;
					}

					sprintf_s(text, MINCALC, "%lf", prec_calc);
					SetWindowText(exact_precision, text);
				}
			}

			GetWindowText(exact_precision, c, MAXTEXT);
			precision = strtod(c, NULL);
		}

		if (LOWORD(wparam) == edt3_id)
		{
			nc = HIWORD(wparam);
			GetWindowText(lparam, c, MAXTEXT);

			if (nc == EN_UPDATE)
			{	
				prec_calc = 0;
				char* new_c = c;
				char* temp;
				
				while (1)
				{
					temp = new_c;

					prec_calc = strtod(new_c, &new_c);

					if (prec_calc == 0 && temp == new_c)
					{
						break;
					}

					sprintf_s(text, MINCALC, "%lf", prec_calc);
					SetWindowText(new_x, text);
				}
			}

			GetWindowText(new_x, c, MAXTEXT);
			x = strtod(c, NULL);
		}

		if (LOWORD(wparam) == cb_id)
		{
			if (HIWORD(wparam) == CBN_SELCHANGE)
			{
				id = SendMessage(lparam, CB_GETCURSEL, 0, 0);
				number_of_func = id;
			}
		}

		if (bt_mode2 == lparam)
		{
			DestroyWindow(edt_precision);
			SetWindowText(subtitle_5, "");
			SetWindowText(subtitle_7, "");
			SetWindowText(exact_precision, "");
			SetWindowText(subtitle_4, "Число элементов\nряда (от 1 до 25):");

			SendMessage(edt_nmax, EM_SETLIMITTEXT, 2, 0);
			edt_precision = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 335, 80, 20, hwnd, NULL, NULL, NULL, NULL);
			
			mode = 2;
		}

		if (bt_mode1 == lparam)
		{
			edt_precision = CreateWindow("edit", "0,000000", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE, 10, 335, 80, 20, hwnd, edt2_id, NULL, NULL, NULL);

			SetWindowText(subtitle_4, "Число элементов\nряда (от 1 до 1000):");
			SetWindowText(subtitle_5, "Точность: >=0,000001");
			SetWindowText(subtitle_7, "Точность:");
			
			SendMessage(edt_precision, WM_SETFONT, style_1, TRUE);
			SendMessage(edt_nmax, EM_SETLIMITTEXT, 3, 0);

			mode = 1;
		}

		if (bt_done == lparam)
		{
			n = 1;

			if (mode == 2)
			{
				if (Nmax <= 25 && Nmax > 0)
				{
					SetWindowText(exact_x, "");

					double(*func[5])(int(*hyp)(), int(*m)()) = { sin_func, sin_func, cos_func, cos_func, exp_func };
					int(*hyp)() = hyperbolic;
					int(*m)() = comporator;
					
					DestroyWindow(output_n);
					DestroyWindow(output_x);
					DestroyWindow(output_dif);

					SetWindowText(output_zone, "Кол-во элементов:        Оценка:                      Расхождение:");

					func[number_of_func](hyp, m);
				}

				else
				{
					SetWindowText(exact_x, "Не верное!");
				}
			}
			
			else
			{
				if (Nmax > 0 && precision >= 0.000001)
				{
					SetWindowText(exact_x, "");
					SetWindowText(exact_precision, "");

					DestroyWindow(output_n);
					DestroyWindow(output_x);
					DestroyWindow(output_dif);

					SetWindowText(output_zone, "Результат:");

					double(*func[5])(int(*modes)(), int(*m)()) = { sin_func, sin_func, cos_func, cos_func, exp_func };
					int(*modes)() = hyperbolic;
					int(*m)() = comporator;

					func[number_of_func](modes, m);
				}

				if (Nmax == 0)
				{
					SetWindowText(exact_x, "Слишком мало!");
				}

				if (precision < 0.000001)
				{
					SetWindowText(exact_precision, "Слишком мала!");
				}
			}
		}
	}

	else
	{
		return DefWindowProcA(hwnd, message, wparam, lparam);
	}
}

void main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, "Rus");

	WNDCLASSA wcl;

		memset(&wcl, 0, sizeof(WNDCLASSA));
		wcl.lpszClassName = "Window";
		wcl.lpfnWndProc = WndProc;

	RegisterClassA(&wcl);

	hwnd = CreateWindow("Window", "Taylor's math", WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, 300, 100, 811, 700, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	HWND subtitle_1;
	subtitle_1 = CreateWindow("static", "Режим работы:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 9, 150, 25, hwnd, NULL, NULL, NULL);
	
	HWND subtitle_2;
	subtitle_2 = CreateWindow("static", "Функция:", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, 10, 120, 80, 25, hwnd, NULL, NULL, NULL);

	HWND subtitle_3;
	subtitle_3 = CreateWindow("static", " Точка:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 160, 80, 23, hwnd, NULL, NULL, NULL);
	
	HWND subtitle_6;
	subtitle_6 = CreateWindow("static", "Текущие значения:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 380, 182, 25, hwnd, NULL, NULL, NULL);
	
	HWND subtitle_8;
	subtitle_8 = CreateWindow("static", "Число элементов:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 465, 150, 20, hwnd, NULL, NULL, NULL);
	
	HWND subtitle_9;
	subtitle_9 = CreateWindow("static", "Точка:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 425, 150, 20, hwnd, NULL, NULL, NULL);
	
	HWND subtitle_10;
	subtitle_10 = CreateWindow("static", "Эталон:", WS_VISIBLE | WS_CHILD | WS_BORDER, 243, 630, 250, 25, hwnd, NULL, NULL, NULL);
	
	bt_mode1 = CreateWindow("button", "Однократный расчет", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 10, 43, 200, 20, hwnd, bt_mode1_id, NULL, NULL);

	bt_mode2 = CreateWindow("button", "Серия экспериментов", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER, 10, 73, 200, 20, hwnd, bt_mode2_id, NULL, NULL);

	cb = CreateWindow("combobox", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 100, 120, 80, 150, hwnd, cb_id, NULL, NULL);

	edt_x = CreateWindow("edit", "0", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 100, 160, 80, 23, hwnd, edt3_id, NULL, NULL, NULL);

	subtitle_4 = CreateWindow("static", "Число элементов\nряда (от 1 до 1000):", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 208, 170, 40, hwnd, NULL, NULL, NULL);

	edt_nmax = CreateWindow("edit", "25", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NUMBER, 10, 258, 80, 23, hwnd, edt1_id, NULL, NULL, NULL);

	subtitle_5 = CreateWindow("static", "Точность: >=0,000001", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 305, 170, 20, hwnd, NULL, NULL, NULL);

	edt_precision = CreateWindow("edit", "0,000000", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE, 10, 335, 80, 20, hwnd, edt2_id, NULL, NULL, NULL);

	output_zone = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 243, 20, 530, 580, hwnd, NULL, NULL, NULL);

	new_x = CreateWindow("static", "0,000000", WS_VISIBLE | WS_CHILD, 60, 426, 90, 17, hwnd, NULL, NULL, NULL);
	
	exact_x = CreateWindow("static", "25", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 495, 150, 20, hwnd, NULL, NULL, NULL);

	subtitle_7 = CreateWindow("static", "Точность:", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 540, 150, 20, hwnd, NULL, NULL, NULL);

	exact_precision = CreateWindow("static", "0,000000", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 570, 150, 20, hwnd, NULL, NULL, NULL);

	standard = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 322, 636, 160, 17, hwnd, NULL, NULL, NULL);

	bt_done = CreateWindow("button", "Расчитать!", WS_VISIBLE | WS_CHILD, 0, 601, 220, 60, hwnd, bt_done_id, NULL, NULL);
	
	style_1 = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"));

	HWND style_2;
	style_2 = CreateFont(23, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial Black"));

	HWND windows[24] = {hwnd, subtitle_4, subtitle_5, subtitle_7, edt_nmax, edt_x, edt_precision, exact_precision, exact_x, new_x, bt_mode1, bt_mode2, bt_done, output_zone, output_dif, output_n, output_x, standard, style_1, cb, subtitle_2, subtitle_3, subtitle_8, subtitle_9};

	for (int i = 0; i < 24; i++)
	{
		SendMessage(windows[i], WM_SETFONT, style_1, TRUE);
	}

	SendMessage(subtitle_1, WM_SETFONT, style_2, TRUE);
	SendMessage(subtitle_6, WM_SETFONT, style_2, TRUE);
	SendMessage(subtitle_10, WM_SETFONT, style_2, TRUE);
	SendMessage(bt_mode1, BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(edt_nmax, EM_SETLIMITTEXT, 3, 0);
	SendMessage(cb, CB_ADDSTRING, 0, "sin(x)");
	SendMessage(cb, CB_ADDSTRING, 0, "sinh(x)");
	SendMessage(cb, CB_ADDSTRING, 0, "cos(x)");
	SendMessage(cb, CB_ADDSTRING, 0, "cosh(x)");
	SendMessage(cb, CB_ADDSTRING, 0, "exp(x)");
	SendMessage(cb, CB_SETCURSEL, 0, 0);

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	MoveToEx(hdc, 220, 621, NULL);
	LineTo(hdc, 811, 621);
	MoveToEx(hdc, 220, 0, NULL);
	LineTo(hdc, 220, 700);
	MoveToEx(hdc, 0, 370, NULL);
	LineTo(hdc, 220, 370);
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 220, 600);

	EndPaint(hwnd, &ps);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}