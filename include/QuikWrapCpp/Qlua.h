#pragma once
#pragma warning(disable:4503)
#include "Windows.h"
#include "Lua.h"
#include "DS.h"
#include "AbstractEventHandler.h"

#define FLAG0 1
#define FLAG1 2
#define FLAG2 4
#define FLAG3 8
#define FLAG4 10
#define FLAG5 20
#define FLAG6 40
#define FLAG7 80
#define FLAG8 100
#define FLAG9 200

namespace Qlua
{
	using namespace Lua;
	typedef map<string, TABLE> QuoteTable;// Содержит стакан


	struct Quote
	{
		string Symbol;
		QuoteTable Value;
	};

	enum class TimeFrame :int
	{
		INTERVAL_TICK = 0,
		INTERVAL_M1 = 1,
		INTERVAL_M2 = 2,
		INTERVAL_M3 = 3,
		INTERVAL_M4 = 4,
		INTERVAL_M5 = 5,
		INTERVAL_M6 = 6,
		INTERVAL_M10 = 10,
		INTERVAL_M15 = 15,
		INTERVAL_M20 = 20,
		INTERVAL_M30 = 30,
		INTERVAL_H1 = 60,
		INTERVAL_H2 = 120,
		INTERVAL_H4 = 240,
		INTERVAL_D1 = 1440,
		INTERVAL_W1 = 10080,
		INTERVAL_MN1 = 23200
	};

	class Qlua :
		public CLua
	{
	public:
		int memoryClear = 96; // кол-во памяти(Кб), при привышении которого принудительно вызывается сборщик мусора lua
		
		Qlua() :CLua() { };
		Qlua(lua_State*lua_state) :CLua(lua_state) { 
			Main(); // запускаем основной поток в lua скриптеы
			EventSubscribe_OnStop(); // событие остановки скрипта или закрытия QUIK
		};

		// Подписывается на все события
		void EventSubscribeAll();
		
		// Подписывается на получение изменений лимита по бумагам.
		void EventSubscribe_OnDepoLimit();
		// Подписывается на получение новой заявки или при изменении параметров существующей заявки.
		void EventSubscribe_OnOrder();
		// Подписывается на получение новой стоп-заявки или при изменении параметров существующей стоп-заявки.
		void EventSubscribe_OnStopOrder();
		// Подписывается на получение сделки или при изменении параметров существующей сделки.
		void EventSubscribe_OnTrade();
		// Подписывается на получение изменения стакана котировок
		void EventSubscribe_OnQuote();


		// Функция отображает сообщения в терминале QUIK. Возвращает "0" при ошибке выполнения 
		//или при обнаружении ошибки во входных параметрах. В остальных случаях возвращает «1».
		int message(std::string s, TypeIcon icon = INFO);

		// Время, на которое приостанавливается выполнение lua, в миллисекундах 
		int sleep(int time);

		//Функция предназначена для определения состояния подключения клиентского места к серверу. 
		//Возвращает «1», если клиентское место подключено и «0», если не подключено. 
		int isConnected();

		// Автоматически авторизует пользователя в QUIK
		void Auth(LPCWSTR login, LPCWSTR pass);

		// Функция возвращает таблицу Lua, содержащую информацию о данных из строки с номером «Index» из таблицы с именем «TableName». 
		ROW getItem(std::string tableName, int index);

		// Функция возвращает количество записей в таблице «TableName».
		int getNumberOf(std::string tableName);

		// Функция предназначена для получения информации по бумаге
		ROW getSecurityInfo(std::string class_code, std::string sec_code);

		// Функции предназначены для создания заявок и отправки их в торговую систему
		// Возвращает строку диагностики ошибок
		const char* sendTransaction(ROW params);

		// Функция возвращает номер Торгового счета
		string getTradeAccounts();

		// Функция возвращает стакан по указанному классу и бумаге
		Quote getQuoteLevel2(string class_code, string sec_code);

		// Заказывает бары и возвращает указатель на объект DS. Указатель
		// также сохраняется в std::deque<DS> ds_; для хранения баров и подписки на событие onBarUpdate(int, DS*)
		DS* CreateDataSource(const std::string class_code, const std::string sec_code, int interval, const std::string param = "");
	
		// События
		TEvent<> onMainEvent; // Событие вызывается сразу после запуска lua скрипта
		TEvent<> onStopEvent; // Событие остановки lua скрипта
		TEvent<ROW> onDepoLimitEvent;
		TEvent<ROW> onOrderEvent;
		TEvent<ROW> onStopOrderEvent;
		TEvent<ROW> onTradeEvent;
		TEvent<const std::string&, const std::string&> onQuoteEvent; // Событие изменения стакана
		
		

	private:
		std::deque<DS> ds_; // Содержит заказанные бары

		// Функция возвращает map<string, TABLE> из стека
		QuoteTable GetTableQuote();
		// Найти дискриптор окна по индексу
		static HWND Qlua::FindWindowByIndex(HWND hWndParent, int index, LPCWSTR type);

		// Реализация основного потока выполнения в lua-скрипте
		void Main();
		// Подписка на события остановки lua скрипта из диалога управления и при закрытии терминала QUIK
		void EventSubscribe_OnStop();

		// Обработчики событий из qlua
		static int lua_main(lua_State*st); // Поток main() lua
		static int lua_OnStop(lua_State *st);
		static int lua_OnDepoLimit(lua_State *st);
		static int lua_OnOrder(lua_State *st);
		static int lua_OnStopOrder(lua_State *st);
		static int lua_OnTrade(lua_State *st);
		static int lua_OnQuote(lua_State *st);

		// Флаги на подписанные события
		bool flagMain = false;
		bool flagOnStop = false;
		bool flagOnDepoLimit = false;
		bool flagOnOrder = false;
		bool flagOnStopOrder = false;
		bool flagOnTrade = false;
		bool flagOnQuote = false;
	};

	// Знаю что глобальные переменные это плохо, но 
	// пока не знаю как по другому реализовать события
	extern Qlua _qlua;
}




