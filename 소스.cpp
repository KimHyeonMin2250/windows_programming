#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
int px[1000], py[1000];
int bx[1000], by[1000];
int iCount; //그려진 점의 개수
int oCount;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;
	HBRUSH hBrush1;
	//Message Driven Architecture
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;

	case WM_LBUTTONDOWN: //왼쪽 버튼을 누르면
		hdc = GetDC(hWnd);//윈도우 달려있는 그리기도구상자(DC) 열기
		//x = LOWORD(lParam);
		//y = HIWORD(lParam); 
		px[iCount] = x = (WORD)(lParam);
		py[iCount] = y = (WORD)((lParam)>>16);
		iCount++;
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, x-10, y-10, x+10, y+10);//그리기 api, 사각형을 그려라
		return 0;
	case WM_RBUTTONDOWN: //왼쪽 버튼을 누르면
		hdc = GetDC(hWnd);//윈도우 달려있는 그리기도구상자(DC) 열기
		//x = LOWORD(lParam);
		//y = HIWORD(lParam); 
		bx[oCount] = x = (WORD)(lParam);
		by[oCount] = y = (WORD)((lParam) >> 16);
		oCount++;
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);//그리기 api, 사각형을 그려라
		return 0;
	case WM_PAINT://다시 그려라
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < iCount; i++)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, px[i] - 10, py[i] - 10, px[i] + 10, py[i] + 10);
		}
		for (int i = 0; i < oCount; i++)
		{
			hBrush1 = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush1);
			Ellipse(hdc, bx[i] - 10, by[i] - 10, bx[i] + 10, by[i] + 10);
		}
		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
