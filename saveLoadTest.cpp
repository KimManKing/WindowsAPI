#include "pch.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) load();
}

void saveLoadTest::save()
{
	//파일 입출력
	//C - FILE* 기능이 없어 대신 빨라
	//C++ - ifstream, ofstream - 기능은 많습니다 대신 느림 (물론 체감...)
	//WIN32 - CreateFile() - 보편적이진 않음

	HANDLE file;
	DWORD write;

	char str[128] = "준포폴 화이팅이다 얘들아";

	file = CreateFile("29기.txt", GENERIC_WRITE, FALSE, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("29기.txt", GENERIC_READ, FALSE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "다음주 목요일 기획서 알지?", MB_OK);
}
