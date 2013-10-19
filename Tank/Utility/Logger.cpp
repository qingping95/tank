/* This file is part of Tank.
 *
 * Tank is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * the GNU Lesser General Public Licence along with Tank. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 (©) Jamie Bayne, David Truby, David Watson.
 */

#include "Logger.hpp"

namespace tank
{

void Logger::log(const std::string& s)
{
    logFile_ << "["
             << fileName_
             << ": "
             << timer_.getHumanTime()
             << "] "
             << s;
#ifdef DEBUG
    std::clog << "["
              << fileName_
              << ": "
              << timer_.getHumanTime()
              << "] "
              << s;
#endif
}

Logger::Logger(std::string file) : std::ostream(&buf_)
    ,fileName_{file}
    ,logFile_{fileName_}
    ,buf_{[this](const std::string& s){this->log(s);}}
{
    timer_.start();
    *this << "Log file created";
}

/*Logger::~Logger()
{
    logHelper_ << '\n';
}*/

}