#include "Logger.h"

std::string Logger::GetTimeStamp()
{
	
		using namespace std::chrono;

		const auto now = system_clock::now();

		time_t tt = system_clock::to_time_t(now);

		auto ms = duration_cast<milliseconds>(now.time_since_epoch() % 100);

		std::stringstream ss;

		ss << std::put_time(std::localtime(&tt), "%F %T");

		return ss.str();

	
}

std::string Logger::GetThreadID()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return ss.str();
}

std::string Logger::WrapTextInBlock(const std::string& value, const std::string& prefix, const std::string& suffix)
{
	return prefix + value + suffix;
}

Logger::Logger()
= default;

Logger::~Logger()
= default;

Logger::Logger(const Logger&)
{
}

Logger& Logger::GetLogger()
{
	static Logger self;
	return self;
}

void Logger::InitLogger(const std::string& filename, const LogOutput output)
{

	m_filename = filename;
	m_output = output;
}

void Logger::OpenLogger()
{
	std::ifstream f(m_filename.c_str());
	if (f.good() == true)
	{
		m_file.open(m_filename, std::ios::app);
		this->LogData("",LogSeverity::info);
		this->LogData("**************New Game Instance*************",LogSeverity::debug);
		this->LogData("",LogSeverity::info);
		return;
	}

	if (m_output == LogOutput::everywhere || m_output == LogOutput::file)
	{
		m_file.open(m_filename, std::ios::out);
		m_isOpened = m_file.is_open();

		if (!m_isOpened)
		{
			throw std::runtime_error("Couldn't OpenLogger a log file");
		}
	}
	m_isOpened = true;
}

void Logger::CloseLogger()
{
	FlushLogger();
	if (m_output == LogOutput::everywhere || m_output == LogOutput::file)
	{
		m_file.close();
	}
}

void Logger::FlushLogger()
{
	if (m_output == LogOutput::everywhere || m_output == LogOutput::file)
	{
		m_file.flush();
	}
}

void Logger::LogData(const std::string& msg, const LogSeverity severity)
{
	const std::string result = WrapTextInBlock(GetTimeStamp()) + " " +
		WrapTextInBlock(TransformLogSeverityIntoString(severity)) + " "
		+ msg;

	if (m_output == LogOutput::console)
	{
		std::cout << result << std::endl;
	}
	if (m_output == LogOutput::file)
	{
		m_file << result << std::endl;
	}
	if (m_output == LogOutput::everywhere)
	{
		std::cout << result << std::endl;
		m_file << result << std::endl;
	}
}

Logger globalLogger;