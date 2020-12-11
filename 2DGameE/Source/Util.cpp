//

#include "Util.h"
#include "Engine.PCH.h"
#include "FileSystem.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

namespace FUtil
{
	bool isLoggingEnabled = false;
	int loggingLevel = 1;
	std::string LogDir = "log";
	std::string LogPrefix = "log_";
	std::string LogFilePath = logDir + "/" + logPrefix + GetCurrentTimeNoSpecial();

	bool keepLogging = true;
	SDL_Thread *thread;
	CQueueSafe messagesQueue;

	void LogInit(bool EnableLogging)
	{
		// @TODO - Create directory error if doesn't exist (Windows only)
		// @TODO - Crossplatform

		if (EnableLogging)
		{

// Windows check if log folder exists
#if defined(_WIN32) || defined(_WIN64)
			FFilesystem::CreateDirrectory(LogDir);

			//namespace fs = std::experimental::filesystem;
			//if (!fs::is_directory(logDir) || !fs::exists(logDir)) // Check if folder exists
			//{
			//	// Create folder if not
			//	fs::create_directory(logDir);
			//}
#endif

// Linux
#ifdef linux
// TODO create dir on linux
			Util::Warn("Creating directory on linux isn't implemented yet. Please create one or log will don't be created");
#endif
			isLoggingEnabled = true;
			std::cout << "Logging to: " << logFilePath << std::endl;
		}
		else
		{
			isLoggingEnabled = false;
		}

		SDL_CreateThread(MessagesPrinter, "Log", (void *)NULL);
	}

	static int MessagesPrinter(void * ptr)
	{
		while (keepLogging) 
			if (messagesQueue.m_queque.size() <= 0)
			{ 
				SDL_Delay(2);
			}
			else
			{
				FLogMessage& Message = MessagesQueue.PeekLast();

				switch (Message.Type)
				{
				case ELogMessageType::Message_Info:
					PrintToConsole(Message.Text, 7);
					break;

				case ELogMessageType::Message_Debug:
#ifdef _DEBUG
					PrintToConsole(Message.Text, 5);
#endif // _DEBUG
					break;

				case ELogMessageType::Message_Warning:
					PrintToConsole(Message.Text, 6);
					break;

				case ELogMessageType::Message_Error:
					PrintToConsole(Message.Text, 4);
					break;

				default:
					// Should be impossible (infinite loop may happen)
					// @TODO Create type assert
					break;
				}

				if (isLoggingEnabled)
				{
					std::ofstream LogFile;
					LogFile.open(logFilePath, std::ios_base::app);
					LogFile << Message.Text << std::endl;
					LogFile.close();
				}

				// Remove item
				MessagesQueue.PopSafe();
			}

		return 0;
	}

	/* Return current Milisecond */
	inline long long unsigned int GetMiliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	/* Starts delay you need variable long long int and pass it as reference */
	void StartDelay(long long unsigned int &startMs)
	{
		startMs = GetMiliseconds();
	}

	bool IsDelayed(long long unsigned int &startMs, long long unsigned int &delayMs)
	{
		if (GetMiliseconds() >= startMs + delayMs)
			return true;

		return false;
	}

	time_t GetRawtime()
	{
		time_t rawtime;
		time(&rawtime);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		return rawtime;
	}
	
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
		Message = GetCurrTime() + " (Info): " + Message;
		
		messagesQueue.safePush({ Message_Info , Message });
	}

	void Debug(std::string message) 
	{
#ifdef _DEBUG // if debug
		Message = GetCurrTime() + " (Debug): " + Message;

		messagesQueue.safePush({ Message_Debug , Message });
#endif
	}

	void Warning(std::string Message) 
	{
		Message = GetCurrTime() + " (Warning): " + Message;
		
		MessagesQueue.SafePush({ Message_Warning , Message });
	}

	void Error(std::string Message) 
	{
		Message = GetCurrTime() + " (Error): " + Message;
		
		messagesQueue.safePush({ Message_Error , Message });
	}

	void PrintToConsole(std::string &Message, int Color)
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

