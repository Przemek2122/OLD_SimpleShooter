#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>


namespace Util
{
	/* Use this function as one of first functions.
	 * @param enableLogging specify wheater to log to file or not
	 * @param logLevel changes level of log. */
	void LogInit(bool enableLogging = true, int logLevel = 1);

	/* Returns current milisecond since epoch(1 January 1970) in long long int */
	long long int GetMiliseconds();
	/* Starts delay.
	 * @param startMs should be long long int &.
	 * This functions sets time in ms. */
	void startDelay(long long int & startMs);
	/* Checks and returns true if it's delayed enough.
	 * @param startMs is long long int& set in startDelay().
	 * @param delayMs is time(in ms) which needs to pass untill this function will return true.*/
	bool isDelayed(long long int & startMs, long int & delayMs);

	/* Returns safe rawtime 
	 * @see http://www.cplusplus.com/reference/ctime/ctime/ */
	time_t GetRawtime();
	/* Returns current time in format 12_01_2019_12_37_23. */
	std::string GetCurrentTimeNoSpecial(); 
	/* Returns current time in format 12:01:2019 12:37:23. */
	std::string GetCurrTime();

	/* Logs (Info): with white(default) color.
	 * Logs to file when isLoggingEnabled is true. */
	void Info(std::string message); // __fastcall
	/* Logs (Debug): with log color.
	 * LOGS ONLY WHEN IN Debug mode.
	 * This is empty function in release.
	 * Logs to file when isLoggingEnabled is true. */
	void Debug(std::string message);
	/* Logs (Warnning): with yellow color. 
	 * Logs to file when isLoggingEnabled is true. */
	void Warning(std::string message);
	/* Logs (Error): with red color.
	 * Logs to file when isLoggingEnabled is true. */
	void Error(std::string message);

	/* Print text to console with specified color.
	 * @param color see link below.
	 * @see https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c for color types
	 * This function doesn't log to file. */
	inline void PrintToConsole(std::string &message, int color = 7);

	/* Path to file with log. */ 
	extern std::string logFilePath;
	/* Log directory. Deault: "log". */
	extern std::string logDir;
	/* Log prefix eg: log_13_01_19... Defult: "log_" */
	extern std::string logPrefix;
	/* Sets whether logging to file is enabled or not with LogInit() function. */
	extern bool isLoggingEnabled;
	/* Unused so far */
	extern int loggingLevel;
}