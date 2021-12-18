#pragma once
#include "Lua.h"
#include "Logger.h"
#include "DateTime.h"
#include "AbstractEventHandler.h"

namespace Qlua
{
	using namespace Lua;
 
	// DataSet - ����� ������ ������ ����� �� �����������
	class DS
	{
		CLua lua;

	public:
		std::string Class_code; // ����� ������
		std::string Sec_code; // ������
		std::string Symbol; // ������ sec_code@class_code
		std::string ID; // ��������� �� luaL_ref

		void CreateDataSource(lua_State *L, const std::string class_code, const std::string sec_code, int interval, const std::string param = ""); // ������� ���������� ����� � �������
		double O(int index); // �������� Open ����� � �������� index
		double H(int index); // �������� High ����� � �������� index
		double L(int index); // �������� Low ����� � �������� index
		double C(int index); // �������� Close ����� � �������� index
		double V(int index); // �������� Volume ����� � �������� index
		DateTime T(int index); // �������� ���� � ����� ����� � �������� index
		unsigned int Size(); // ������� ���������� ������� ���������� ������ � ��������� ������.
		bool Close(); // ������� ��������� �������� ������, � �������� ���������� �������� ������ � �������.

		bool SetUpdateCallback(); // ������ �������� ������� ��������� ������

		// ������� ��������� �����
		// int - ����� �����
		// DS* - ��������� �� DataSet
		TEvent<int, DS*> onBarUpdate; 

	private:
		// ������� qlua, ��������� ������ ��� ��������� �����
		static int qluaCallback(lua_State* L);


	};
}