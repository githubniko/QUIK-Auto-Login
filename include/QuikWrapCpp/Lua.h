#pragma once
#include "stdafx.h"

#define TypeIcon int
#define NONE 0
#define INFO 1
#define WARNING 2
#define ERR 3

#define LUA_LIB
#define LUA_BUILD_AS_DLL
#include "lua.hpp"


using namespace std;

namespace Lua
{
	static std::mutex lua_mutex;

	// регистрируем внешние функции, вызываемые из lua скрипта
	static struct luaL_Reg ls_lib[] = {
		{ nullptr, nullptr }
	};

	typedef map<string, string> ROW; // строка таблицы ассоцитиативного массива
	typedef map<string, ROW> TABLE; // 



	class CLua
	{

	private:
		bool isowner;

	public:
		lua_State*lua;
		


	public:

		CLua();
		CLua(lua_State*lua_state);
		~CLua();
		void LoadAllStdLibs();
		void DoStr(std::string str);
		void DoFile(std::string str);
		int RegFunction(std::string name, int(*poin)(lua_State*st));
		void GetGlobal(std::string field);
		void SetGlobal(std::string field);
		void GetField(int i, std::string field);
		int ToInteger(int index);
		double ToNumber(int index);
		string ToString(int index);
		lua_CFunction ToFunction(int index); // получает указатель на функцию
		bool ToBool(int index);
		void Push(int i);
		void Push(bool i);
		void Push(const char*str);
		void Push(string str);
		void PushNil();
		void PushNumber(double d);
		void PushValue(int i);
		void PushCClosure(lua_CFunction func, int i);
		void PushFunction(lua_CFunction func);
		void Pop(int count);
		int GetTop();
		void SetTop(int top);
		int GetType(int index);
		std::string GetTypeName(int TypeCode);
		int Call(int nargs); // Не возвращает результат
		int Call(int nargs, int nresult); // Возвращет результат
		void Error();
		int IsFunction();
		int Exception(std::string str);
		int isNil(int i); //Возвращает 1 если значение в заданном допустимом (acceptable) индексе – nil, и 0 в противном случае.
		void SetField(int i, std::string field);
		double collectgarbage(string name); // вызывает сборщи мусора


		ROW GetRow(); // Преобразует таблицу в 1-мерый массив	
		TABLE GetTable(); // Преобразует несколько строк в 2х-мерный массив

		//template<typename T>
		//TABLE<T> GetTable(int len); // преобразует несколько строк в 2х-мерный массив c числовым ключем

		void stack_dump();
	};

}