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
	std::cout << "-c <configfile>\t" << "path to the configuration file" << std::endl;
	std::cout << "-m <message>\t" << "message to send to the recipients" << std::endl;
	std::cout << "-m <subject>\t" << "subject to set" << std::endl;
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

int main( int argc, char* argv[] )
{
	std::string config;
	std::string message;
	std::string subject;
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
				std::string receivers("");
				std::string username("");
				std::string password("");
				size_t pos = 0;

				while (! myfile.eof() )
				{
					getline (myfile,line);

					if ((pos = line.find("=")) != std::string::npos)
					{
						if (line.find("receivers") != std::string::npos)
							receivers = line.substr(pos+1);
						else if (line.find("username") != std::string::npos)
							username = line.substr(pos+1);
						else if (line.find("password") != std::string::npos)
							password = line.substr(pos+1);
					}
				}

				myfile.close();

				receivers = removeSpace(receivers);
				username = removeSpace(username);
				password = removeSpace(password);


				if ((receivers.compare("") != 0)
					&& (username.compare("") != 0)
					&& (password.compare("") != 0)
					)
				{
					size_t oldpos(0);
					size_t pos(0);

					while ((pos = receivers.find(",", pos)) != std::string::npos)
					{
						receiversVect.push_back( receivers.substr(oldpos, pos) );

						++pos;
						oldpos = pos;
					}

					if (oldpos != std::string::npos)
						receiversVect.push_back( receivers.substr(oldpos) );


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
