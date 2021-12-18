// взято из https://habr.com/ru/post/424593/
// нужен для реализации событий


#pragma once

#include <iostream>
#include <list>
#include <cassert>

using namespace std;

template<class ...TParams>
class AbstractEventHandler
{
public:
	virtual void call(TParams... params) = 0;
protected:
	AbstractEventHandler() {}
};

template<class ...TParams>
class TEvent
{
	using TEventHandler = AbstractEventHandler<TParams...>;
public:
	TEvent() :
		m_handlers()
	{
	}
	~TEvent()
	{
		for (TEventHandler* oneHandler : m_handlers)
			delete oneHandler;
		m_handlers.clear();
	}
	void operator()(TParams... params)
	{
		for (TEventHandler* oneHandler : m_handlers)
			oneHandler->call(params...);
	}
	// добавляет обрабочик события
	void operator+=(TEventHandler& eventHandler)
	{
		m_handlers.push_back(&eventHandler);
	}
private:
	std::list<TEventHandler*> m_handlers;
};

template<class TObject, class ...TParams>
class MethodEventHandler : public AbstractEventHandler<TParams...>
{
	using TMethod = void(TObject::*)(TParams...);
public:
	MethodEventHandler(TObject& object, TMethod method) :
		AbstractEventHandler<TParams...>(),
		m_object(object),
		m_method(method)
	{
			assert(m_method != nullptr);
		}
	virtual void call(TParams... params) override final
	{
		(m_object.*m_method)(params...);
	}
private:
	TObject& m_object;
	TMethod m_method;
};

template<class TObject, class ...TParams>
AbstractEventHandler<TParams...>& createMethodEventHandler(TObject& object, void(TObject::*method)(TParams...))
{
	return *new MethodEventHandler<TObject, TParams...>(object, method);
}

#define METHOD_HANDLER( Object, Method ) createMethodEventHandler( Object, &Method )
#define MY_METHOD_HANDLER( Method ) METHOD_HANDLER( *this, Method )