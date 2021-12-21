#include "windows.h"

#include <string>

#define LUA_LIB
#define LUA_BUILD_AS_DLL

#include "lua.hpp"
#include "Qlua.h"

using namespace std;

Qlua::Qlua *qlua = &Qlua::_qlua;



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

int lua_auth(lua_State* L)
{
	Qlua::CLua lua(L);
	int n = lua.GetTop(); // получаем кол-во 

	if (n != 2) 
		return 0;

	std::wstring QUIK_LOGIN = s2ws(lua.ToString(1));
	std::wstring QUIK_PASSW = s2ws(lua.ToString(2));

	qlua->Auth(QUIK_LOGIN.c_str(), QUIK_PASSW.c_str());

	return 1;
}

extern "C" LUALIB_API int luaopen_AutoLogin(lua_State *L) {
	*qlua = Qlua::Qlua(L);
	qlua->RegFunction("Auth", &lua_auth); // регистрирую новую функцию в lua
	return 0;
}