/*
 * ConsoleLogger.h
 *
 *  Created on: Oct 28, 2010
 *      Author: Petko
 */

#ifndef CONSOLELOGGER_H_
#define CONSOLELOGGER_H_

#include "IJWLogger.h"
namespace jw
{
namespace log
{


class ConsoleLogger: public IJWLogger
{
private:
	void print(const char * str);
public:
	ConsoleLogger(const char * name);
	virtual ~ConsoleLogger();

	virtual void trace(const char* pattern, ...);
	virtual void debug(const char* pattern, ...);
	virtual void info(const char* pattern, ...);
	virtual void warn(const char* pattern, ...);
	virtual void error(const char* pattern, ...);
};

}
}
#endif /* CONSOLELOGGER_H_ */
