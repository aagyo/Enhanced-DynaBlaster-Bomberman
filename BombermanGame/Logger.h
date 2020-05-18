#pragma once
#include <string>
#include <map>
#include <sstream>	
#include <fstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

namespace gits
{
	enum class LogSeverity
	{
		error,
		warning,
		info,
		debug
	};
	enum class LogOutput
	{
		console,
		file,
		everywhere
	};

	inline std::string TransformLogSeverityIntoString(const LogSeverity severity)
	{
		std::map < LogSeverity, std::string> S_SEVERITY_MAP =
		{
			{LogSeverity::error, "ERROR"},
			{LogSeverity::warning, "WARNING"},
			{LogSeverity::info, "INFO"},
			{LogSeverity::debug, "DEBUG"}
		};

		std::string result = "NONE";
		auto it = S_SEVERITY_MAP.find(severity);

		if (it != S_SEVERITY_MAP.end())
		{
			result = it->second;
		}
		
		return result;

	}
}

using namespace gits;
class Logger
{
	private:
		static std::string GetTimeStamp();

		static std::string GetThreadID();

		static std::string WrapTextInBlock(const std::string& value, const std::string& prefix = "[", const std::string& suffix = "]");
public:
		Logger();
		~Logger();
	public:
		static Logger& GetLogger();

	public:
		bool initialized = false;


	public:

		Logger(const Logger&);
		
		void InitLogger(const std::string& filename,
			const LogOutput output = LogOutput::everywhere);
		void OpenLogger();
		void CloseLogger();
		void FlushLogger();
		void LogData(const std::string& msg, const LogSeverity severity = LogSeverity::debug);
			
		template<class T>
		void LogData(const T& t, const LogSeverity severity = LogSeverity::debug);
	private:
		std::string m_filename;
		std::fstream m_file;
		LogOutput m_output = LogOutput::everywhere;

		bool m_isOpened = false; 
};

template<class T>
Logger& operator <<(Logger& logger, const T& t)
{
	logger.LogData(t);
	return logger;
}

static Logger& logObj()
{
	return Logger::GetLogger();
}

template<class T>
inline void Logger::LogData(const T& t, const LogSeverity severity)
{
	std::stringstream ss;
	ss << t;
	LogData(ss.str(), severity);
}

extern Logger globalLogger;