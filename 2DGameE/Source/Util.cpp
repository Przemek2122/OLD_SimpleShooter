#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include "Util.h"
#include <chrono>
#include <filesystem> // or #include <experimental/filesystem> // for creating directory in LogInit()

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif


namespace Util
{
	bool isLoggingEnabled = false;
	int loggingLevel = 1;
	std::string logDir = "log";
	std::string logPrefix = "log_";
	std::string logFilePath = logDir + "/" + logPrefix + GetCurrentTimeNoSpecial();

	/* Call before calling logging functions.
	 * It will don't create any error otherwise
	 * but will don't log anthing to file. */
	void LogInit(bool enableLogging, int logLevel)
	{
		// @TODO - Create directory error if doesn't exist (Windows only)
		// @TODO - Crossplatform

		if (enableLogging)
		{

// Windows check if log folder exists
#if defined(_WIN32) || defined(_WIN64)
			namespace fs = std::experimental::filesystem;

			if (!fs::is_directory(logDir) || !fs::exists(logDir)) // Check if folder exists
			{
				// Create folder if not
				fs::create_directory(logDir);
			}
#endif

// Linux
#ifdef linux
// TODO create dir on linux
			Util::Warning("Creating directory on linux isn't implemented yet. Please create one or log will don't be created");
#endif
			isLoggingEnabled = true;
			Util::Info("Logging to: " + logFilePath);
		}
		else
		{
			isLoggingEnabled = false;
		}

		loggingLevel = logLevel;
	}

	/* Return current Milisecond */
	inline long long int GetMiliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	/* Starts delay you need variable long long int and pass it as reference */
	void startDelay(long long int &startMs)
	{
		startMs = GetMiliseconds();
	}

	/* Use this to check pass startMs 
	 * (start with startDelay() first!)
	 * delayMs is refernce for performance */
	bool isDelayed(long long int &startMs, long int &delayMs)
	{
		if (GetMiliseconds() >= startMs + delayMs)
			return true;
		// else
		return false;
	}

	/* Return simple rawtime */
	time_t GetRawtime()
	{
		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		return rawtime;
	}
	
	/* Returns current time in format: 
	 * day_month_year_hour_minute_second 
	 * eg: 6_04_2018_11_7_59 */
	std::string GetCurrentTimeNoSpecial() 
	{
		std::string MonthTable[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		std::string ctm = std::to_string(timeinfo.tm_mday) + "_" + MonthTable[timeinfo.tm_mon] + "_" + std::to_string(timeinfo.tm_year + 1900) + "_"
			+ std::to_string(timeinfo.tm_hour) + "_" + std::to_string(timeinfo.tm_min) + "_" + std::to_string(timeinfo.tm_sec);

		return ctm;
	}

	/* Returns current time in format:
	 *  */
	std::string GetCurrTime() 
	{
		std::string MonthTable[12] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		std::string ctm = std::to_string(timeinfo.tm_mday) + "-" + MonthTable[timeinfo.tm_mon] + "-" + std::to_string(timeinfo.tm_year + 1900) + " "
			+ std::to_string(timeinfo.tm_hour) + ":" + std::to_string(timeinfo.tm_min) + ":" + std::to_string(timeinfo.tm_sec);

		return ctm;
	}

	void Info(std::string message) 
	{
		message = GetCurrTime() + " (Info): " + message;
		PrintToConsole(message);

		if (isLoggingEnabled)
		{
			std::ofstream LogFile;
			LogFile.open(logFilePath);
			LogFile << message << std::endl;
			LogFile.close();
		}
	}

	void Debug(std::string message) 
	{
#ifdef _DEBUG // if debug
		message = GetCurrTime() + " (Debug): " + message;
		PrintToConsole(message, 5);

		if (isLoggingEnabled)
		{
			std::ofstream LogFile;
			LogFile.open(logFilePath);
			LogFile << message << std::endl;
			LogFile.close();
		}
#endif
	}

	void Warning(std::string message) 
	{
		message = GetCurrTime() + " (Warrning): " + message;
		PrintToConsole(message, 6);

		if (isLoggingEnabled)
		{
			std::ofstream LogFile;
			LogFile.open(logFilePath);
			LogFile << message << std::endl;
			LogFile.close();
		}
	}

	void Error(std::string message) 
	{
		message = GetCurrTime() + " (Error): " + message;
		PrintToConsole(message, 4);

		if (isLoggingEnabled)
		{
			std::ofstream LogFile;
			LogFile.open(logFilePath);
			LogFile << message << std::endl;
			LogFile.close();
		}
	}

	void PrintToConsole(std::string &message, int color)
	{
#if defined(_WIN32) || defined(_WIN64)
		// Change color to red
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // text color
		SetConsoleTextAttribute(hConsole, color);
#endif

		std::cout << message << std::endl;

#if defined(_WIN32) || defined(_WIN64)
		// Change color back to white
		SetConsoleTextAttribute(hConsole, 7);
#endif
	}
}