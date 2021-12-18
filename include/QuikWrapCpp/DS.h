#pragma once
#include "Lua.h"
#include "Logger.h"
#include "DateTime.h"
#include "AbstractEventHandler.h"

namespace Qlua
{
	using namespace Lua;
 
	// DataSet - Класс хранит данные баров по инструменту
	class DS
	{
		CLua lua;

	public:
		std::string Class_code; // Класс бумаги
		std::string Sec_code; // Бумага
		std::string Symbol; // формат sec_code@class_code
		std::string ID; // указатель на luaL_ref

		void CreateDataSource(lua_State *L, const std::string class_code, const std::string sec_code, int interval, const std::string param = ""); // Функция заказывает свечи с сервера
		double O(int index); // Получает Open свечи с индексом index
		double H(int index); // Получает High свечи с индексом index
		double L(int index); // Получает Low свечи с индексом index
		double C(int index); // Получает Close свечи с индексом index
		double V(int index); // Получает Volume свечи с индексом index
		DateTime T(int index); // Получает Дату и всемя свечи с индексом index
		unsigned int Size(); // Функция возвращает текущее количество свечек в источнике данных.
		bool Close(); // Функция закрывает источник данных, и терминал прекращает получать данные с сервера.

		bool SetUpdateCallback(); // Начать получать события изменения свечей

		// Событие изменения свечи
		// int - номер свечи
		// DS* - указатель на DataSet
		TEvent<int, DS*> onBarUpdate; 

	private:
		// Функция qlua, обратного вызова при изменении свечи
		static int qluaCallback(lua_State* L);


	};
}