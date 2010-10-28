/*
 * LoggerFactory.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: Petko
 */

#include "LoggerFactory.h"

namespace jw
{
namespace log
{

ConsoleLogger jw::log::LoggerFactory::logger("xxx");

IJWLogger * jw::log::LoggerFactory::getLogger(const char * name)
{
	return &logger;
}

}

}
