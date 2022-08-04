#include "windows.h"

#include <string>

#define LUA_LIB
#define LUA_BUILD_AS_DLL

#include "lua.hpp"

using namespace std;

int message(lua_State* L, std::string s, int icon = 0)
{
	int top = lua_gettop(L);
	lua_getglobal(L, "message");
	if (!lua_isfunction(L, -1)) {
		lua_settop(L, top);
		return 0;
	}
	lua_pushstring(L, s.c_str());
	lua_pushinteger(L, icon);
	lua_pcall(L, 2, 1, 0);// NUMBER message(STRING message, NUMBER icon_type)
	lua_pop(L, 1);

	return 1;
}
int isConnected(lua_State* L)
{
	int top = lua_gettop(L);
	lua_getglobal(L, "isConnected");
	if (!lua_isfunction(L, -1)) {
		lua_settop(L, top);
		return 0;
	}
	lua_pcall(L, 0, 1, 0);
	int R = (int)lua_tointeger(L, -1);
	lua_pop(L,1);
	
	return R;
}
// Конвертирует std::string to std::wstring
// Взято с https://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
//
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

HWND FindWindowByIndex(HWND hWndParent, int index, LPCWSTR  type)
{
	if (index == 0)
		return hWndParent;
	else
	{
		int ct = 0;
		HWND result = NULL;
		do
		{
			result = FindWindowEx(hWndParent, result, type, NULL);
			if (result != NULL)
				++ct;
		} while (ct < index && result != NULL);
		return result;
	}
}

void Auth(lua_State* L, LPCWSTR login, LPCWSTR pass)
{
	LPWSTR windowsName1 = L"Установка сетевого соединения";
	LPWSTR windowsName2 = L"Войти в систему";

	if (!isConnected(L))
	{
		HWND hLoginWnd = 0;
		while (!hLoginWnd) { // Ждем пока появися окно идентификации
			Sleep(1000);
			if (hLoginWnd = FindWindow(NULL, windowsName1)) {
				HWND nBtnEnter = FindWindowByIndex(hLoginWnd, 3, L"Button"); // Ищим третью по счету кнопку
				// Нажимаем Кнопку Ввод
				SetFocus(nBtnEnter);
				PostMessage(nBtnEnter, BM_CLICK, 0, 0);
				hLoginWnd = 0; // Нужно, чтобы ждать окна авторизации
			}
			else if (hLoginWnd = FindWindow(NULL, windowsName2))
			{
				HWND nBtnOk = FindWindowByIndex(hLoginWnd, 2, L"Button"); // Ищим вторую по счету кнопку
				HWND hLogin = FindWindowByIndex(hLoginWnd, 1, L"Edit");
				HWND nPassw = FindWindowByIndex(hLoginWnd, 2, L"Edit");

				SetWindowText(hLogin, login);
				SetWindowText(nPassw, pass);

				// Нажимаем Кнопку Ввод
				SetFocus(nBtnOk);
				PostMessage(nBtnOk, BM_CLICK, 0, 0);
				return;
			}
		}

		if (!hLoginWnd)
			message(L, "Окно не найдено", 0);
	}
	else message(L, "Соединение уже установлено", 0);
}

int lua_auth(lua_State* L)
{
	std::wstring QUIK_LOGIN = s2ws(lua_tostring(L, 1));
	std::wstring QUIK_PASSW = s2ws(lua_tostring(L, 2));

	Auth(L, QUIK_LOGIN.c_str(), QUIK_PASSW.c_str());

	return 1;
}

extern "C" LUALIB_API int luaopen_AutoLogin(lua_State *L) {
	lua_register(L, "Auth", &lua_auth);
	return 0;
}