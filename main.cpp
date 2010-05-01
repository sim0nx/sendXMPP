/*
    Copyright (C) 2010 Georges Toth <georges@trypill.org>


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "SendXMPP.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


std::string removeSpace(const std::string &to)
{
	size_t pos(0);
	std::string _to(to);

	while ((pos = _to.find(" ")) != std::string::npos)
	{
		_to.erase(pos, 1);
	}

	return _to;
}

void printHelp(const char *progName)
{
	std::cout << "Usage: " << progName << " [OPTION]" << std::endl << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t-c <configfile>\t" << "path to the configuration file" << std::endl;
	std::cout << "\t-m <message>\t" << "message to send to the recipients" << std::endl;
	std::cout << "\t-s <subject>\t" << "subject to set" << std::endl;
	std::cout << "\t-r <receiver1,receiver2,...>\t" << "comma seperated list of receivers" << std::endl;
	std::cout << std::endl;
	std::cout << "If a message is piped to " << progName << ", the \"-m\" parameter may be omitted" << std::endl;
	std::cout << std::endl;
}

bool testArgCount(const int &argc, const int &count)
{
	if (count >= argc)
		return false;

	return true;
}

std::vector<std::string> splitReceivers(const std::string &receivers)
{
	std::string _receivers( removeSpace(receivers) );
	size_t oldpos(0);
	size_t pos(0);
	std::vector<std::string> receiversVect;

	while ((pos = _receivers.find(",", pos)) != std::string::npos)
	{
		receiversVect.push_back( removeSpace( _receivers.substr(oldpos, pos) ) );

		++pos;
		oldpos = pos;
	}

	if (oldpos != std::string::npos)
		receiversVect.push_back( _receivers.substr(oldpos) );


	return receiversVect;
}


int main( int argc, char* argv[] )
{
	std::string config;
	std::string message;
	std::string subject;
	std::string receivers;
	bool initialized(true);

	std::string param;
	for(int i=0;i<argc;++i)
	{
		param = argv[i];

		if (param == "-c")
		{
			++i;
			if ((initialized = testArgCount(argc, i)) == false)
				break;

			param = argv[i];
			config = param;
		}

		if (param == "-m")
		{
			++i;
			if ((initialized = testArgCount(argc, i)) == false)
				break;

			param = argv[i];
			message = param;
		}

		if (param == "-s")
		{
			++i;
			if ((initialized = testArgCount(argc, i)) == false)
				break;

			param = argv[i];
			subject = param;
		}

		if (param == "-r")
		{
			++i;
			if ((initialized = testArgCount(argc, i)) == false)
				break;

			param = argv[i];
			receivers = param;
		}
	}

	if (initialized)
	{
		if (!isatty(fileno(stdin)))
		{
			message.clear();
	                while(!std::cin.eof())
				message.push_back(std::cin.get());

			message.erase( message.end()-2, message.end() );
		}

	
		if ((config.size() > 0) && (message.size() > 0))
		{
			std::string line;
			std::ifstream myfile (config.c_str());
			std::vector<std::string> receiversVect;

			if (myfile.is_open())
			{
				std::string username("");
				std::string password("");
				size_t pos = 0;

				while (! myfile.eof() )
				{
					getline (myfile,line);

					if ((pos = line.find("=")) != std::string::npos)
					{
						if (line.find("receivers") != std::string::npos)
						{
							if (receivers.compare("") == 0)
								receivers = line.substr(pos+1);
						}else if (line.find("username") != std::string::npos)
							username = line.substr(pos+1);
						else if (line.find("password") != std::string::npos)
							password = line.substr(pos+1);
					}
				}

				myfile.close();

				username = removeSpace(username);
				password = removeSpace(password);


				if ((receivers.compare("") != 0)
					&& (username.compare("") != 0)
					&& (password.compare("") != 0)
					)
				{
					receiversVect = splitReceivers(receivers);

					SendXMPP sendXMPP(username, password, receiversVect, message, subject);

					return 0;
				}
			}
			else
				std::cout << "Error: unable to open config file \"" << config << "\"" << std::endl << std::endl;
		}
	}

	printHelp(argv[0]);
	return 1;
}
