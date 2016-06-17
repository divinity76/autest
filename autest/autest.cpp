// autest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
void pause() {
	system("pause");
}
bool exists(char* path) {
	FILE* fp = fopen(path, "r");
	if (fp) {
		fclose(fp);
		return true;
	}
	return false;
}
int getOldVersion() {
	if (!exists("currentversion.txt")) {
		return 0;
	}
	char asciiversion[999] = { 0 };
	FILE* fp = fopen("currentversion.txt", "r");
	fread(asciiversion, sizeof(asciiversion), 1, fp);
	fclose(fp);
	return atoi(asciiversion);
}
void setCurrentVersion(int newVersion) {
	FILE* fp = fopen("currentversion.txt", "w");
	if (!fp) {
		throw new std::runtime_error("foo the shit");
	}
	char buf[99];
	itoa(newVersion, buf, 10);
	size_t len = strlen(buf);
	fwrite(buf, len, 1, fp);
	fclose(fp);
}
int getNewVersion() {
	system("curl --silent --location --insecure https://raw.githubusercontent.com/divinity76/autest/master/version.txt >newversion.txt");
	if (!exists("newversion.txt")) {
		return 0;
	}
	char asciiversion[999] = { 0 };
	FILE* fp = fopen("newversion.txt", "r");
	fread(asciiversion, sizeof(asciiversion), 1, fp);
	fclose(fp);
	return atoi(asciiversion);
}
int main()
{
	TCHAR str[999] = { 0 };
	GetCurrentDirectory(999, str);
	std::wcout << str << std::endl;
	int oldVersion = getOldVersion();
	int newVersion = getNewVersion();
	std::cout << "current version: " << oldVersion << ". new version: " << newVersion << std::endl;
	if (newVersion != oldVersion) {
		std::cout << "updating... " << std::endl;
		std::cout << "updating outcast.exe ... " << std::endl;
		system("curl --location --insecure https://github.com/divinity76/autest/blob/master/Outcast.exe?raw=true >Outcast.exe");
		setCurrentVersion(newVersion);
	}
	pause();
	return 0;
}

