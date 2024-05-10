#pragma once
#ifndef WINDOWTEXT_WGW
#define WINDOWTEXT_WGW
#include <Windows.h>
#include <string>
#include <sstream>

using std::string;
using std::istringstream;
using std::ostringstream;

inline void GetHWNDText(HWND hWnd, string &s)
{
	int length = GetWindowTextLength(hWnd) + 1;
	char* buffer = new char[length];
	GetWindowText(hWnd, buffer, length);
	s = buffer;
}

inline void GetHWNDText(HWND hWnd, __int8& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, int& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, long long& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, unsigned __int8& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, unsigned int& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, unsigned long long& i)
{
	string data = "";
	GetHWNDText(hWnd, data);
	if (data == "") return;
	istringstream is(data);
	is >> i;
}

inline void GetHWNDText(HWND hWnd, char &c)
{
	char* buffer = new char[2];
	GetWindowText(hWnd, buffer, 2);
	c = buffer[0];
}

inline void SetHWNDText(HWND hWnd, string s)
{
	SetWindowText(hWnd, s.c_str());
}

inline void SetHWNDText(HWND hWnd, __int8 x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, int x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, long long x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, unsigned __int8 x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, unsigned int x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, unsigned long long x)
{
	ostringstream os;
	os << x;
	SetWindowText(hWnd, os.str().c_str());
}

inline void SetHWNDText(HWND hWnd, char c)
{
	char* Buffer = new char[2];
	Buffer[0] = c;
	SetWindowText(hWnd, Buffer);
}

#endif