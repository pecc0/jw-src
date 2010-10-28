/*
 * LoggerFactory.h
 *
 *  Created on: Oct 28, 2010
 *      Author: Petko
 */

#ifndef LOGGERFACTORY_H_
#define LOGGERFACTORY_H_

#include "ConsoleLogger.h"

namespace jw
{
namespace log
{
class LoggerFactory
{
	static ConsoleLogger logger;
public:

	static IJWLogger* getLogger(const char * name);
};
}
}



#endif /* LOGGERFACTORY_H_ */
