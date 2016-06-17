// autest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

void pause() {
	system("pause");
}

int main()
{
	TCHAR str[999] = { 0 };
	GetCurrentDirectory(999, str);
	std::wcout << str << std::endl;

	system("curl");
	pause();
	return 0;
}

