// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"
#include "windowsx.h"

int g_is_clicked = 0;
RECT g_rect = { 10, 10, 50, 50 };
POINT g_prev_pos;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_LBUTTONDOWN) {
		/*
		// SelectObject 실습
		HDC h_dc = GetDC(hWnd);

		HGDIOBJ h_old_brush = SelectObject(h_dc, GetStockObject(GRAY_BRUSH));
		Rectangle(h_dc, 20, 20, 80, 80);
		SelectObject(h_dc, GetStockObject(NULL_BRUSH));
		Rectangle(h_dc, 60, 60, 120, 120);
		SelectObject(h_dc, h_old_brush);

		ReleaseDC(hWnd, h_dc);
		*/

		/*
		// CreateSolidBrush 실습
		HDC h_dc = GetDC(hWnd);

		HBRUSH h_blue_brush = CreateSolidBrush(RGB(0, 0, 255));
		HGDIOBJ h_old_brush = SelectObject(h_dc, h_blue_brush);
		HPEN h_null_pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		HGDIOBJ h_old_pen = SelectObject(h_dc, h_null_pen);
		Rectangle(h_dc, 10, 10, 100, 100);
		SelectObject(h_dc, h_old_brush);
		SelectObject(h_dc, h_old_pen);
		DeleteObject(h_blue_brush);
		DeleteObject(h_null_pen);

		ReleaseDC(hWnd, h_dc);
		*/

		// CreateHatchBrush
		HDC h_dc = GetDC(hWnd);
		HBRUSH h_brush;

		// Brush의 속성을 비교하기 위해 사용할 Brush 객체에서 사용가능한 속성 명칭을 지정한다.
		const char *p_style_string[6] = { "HS_BDIAGONAL", "HS_CROSS", "HS_DIAGCROSS", "HS_FDIAGONAL", "HS_HORIZONTAL", "HS_VERTICAL" };
		// Brush의 속성을 비교하기 위해 사용할 Brush 객체의 속성 인자 값들을 지정한다.
		int brush_style[6] = { HS_BDIAGONAL, HS_CROSS, HS_DIAGCROSS, HS_FDIAGONAL, HS_HORIZONTAL, HS_VERTICAL };
		// 선의 경우 표시되지 않는 부분의 색상이 배경색으로 출력되지 않도록 배경색을 투명하게 하는 옵션을 설정한다.
		SetBkMode(h_dc, TRANSPARENT);
		// 현재 DC에 설정된 Brush 핸들 값을 얻는다.
		HGDIOBJ h_old_brush = GetCurrentObject(h_dc, OBJ_BRUSH);


		// 위에서 지정한 6가지의 속성별로 사각형을 그린다. 
		for (int i = 0; i < 6; i++) {
			// Brush의 속성별 명칭을 화면에 출력한다.
			TextOutA(h_dc, 10, 10 + i * 30, p_style_string[i], strlen(p_style_string[i]));
			// 저장한 Brush의 속성값으로 파란색 Brush 객체를 생성한다.
			h_brush = CreateHatchBrush(brush_style[i], RGB(0, 0, 255));
			// DC에 생성한 Brush 객체를 연결한다.
			SelectObject(h_dc, h_brush);

			Rectangle(h_dc, 200, 5 + i * 30, 400, 30 + i * 30);  // 사각형 그리기

			// 사용이 끝난 Brush 객체는 제거한다.
			DeleteObject(h_brush);
		}
		// 기존에 사용하던 Brush 객체로 복구한다.
		SelectObject(h_dc, h_old_brush);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}