/*							[  28 / 03 / 2012 LVI ]
//         Copyright (c) Vitaly I. Lyaschenko e-mail: < lvix@ukrpost.ua >
//                              Header file
*/
#pragma once

#include <sstream>
// ������ ����������������
enum LogLevel_t
{
	logError = 0,
	logWarning,
	logInfo,
	logDebug,
	logDebug1,
	logDebug2,
	logDebug3,
};

template<typename T>
class Logger {
public:
	Logger( void );
	virtual ~Logger( void );

	std::ostringstream&	GetMsg(LogLevel_t level = logInfo);
	// ������������� ������� �����������
	static LogLevel_t&	ReportingLevel( void );
	
	static const char*	LevelToString(LogLevel_t level);
	static LogLevel_t	LevelFromString(const char* ch_level);

protected:
	std::ostringstream m_oss;
private:
	Logger(const Logger&);
	Logger& operator = (const Logger&);
};

/* 
	����� ���������� �� ���������� ������ ���������
	� �� ���������
*/
class OutStream {
public:
	// ��������������(������������) ���� ����
	static bool		InitLogFile(const char* nameFileLog);
	// ��������������� ������ ��������� � ����
	static bool		UseFile( void );
	// ��������������� ������ ��������� � �������
	static bool		UseStderr( void );
	// ���� �� �������� ����� ������� � ���
	static bool&	IsOutputTime( void );
};

class Log : public Logger<OutStream> {};

// ������������� ����� ����
#define LOG_FILE_INIT( x )		OutStream::InitLogFile(x)
// �������� �� � ��� ����� �������
#define LOG_IS_OUTPUT_TIME( x )	OutStream::IsOutputTime() = x;
// ��� ��������� ��������� � ����
#define LOG_USE_FILE			OutStream::UseFile();
// ��� ��������� ��������� � �������
#define LOG_USE_STDERR			OutStream::UseStderr();

#define STRINGIFY( X ) #X
#define TOSTRING( X ) STRINGIFY( X )
#define AT __FUNCTION__ " : " __FILE__ " : " TOSTRING( __LINE__ )

#define TO_LOG(level) \
	if (level > logDebug3); \
	else if(level  > Log::ReportingLevel()); \
	else Log().GetMsg(level)

#define LOG_ERROR		TO_LOG( logError ) << AT << "\n   "
#define LOG_WARNING		TO_LOG( logWarning ) << AT << "\n   "
#define LOG_INFO		TO_LOG( logInfo )

#define LOG_DEBUG		TO_LOG( logDebug )
#define LOG_DEBUG_1		TO_LOG( logDebug1 )
#define LOG_DEBUG_2		TO_LOG( logDebug2 )
#define LOG_DEBUG_3		TO_LOG( logDebug3 )
