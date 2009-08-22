#include "SendXMPP.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::string removeSpace(const std::string &to)
{
	int pos = 0;
	std::string _to(to);

	while ((pos = _to.find(" ")) != std::string::npos)
	{
		_to.erase(pos, 1);
	}

	return _to;
}

int main( int argc, char* argv[] )
{
	if (argc == 2)
	{
		std::string message(argv[1]);
		std::string line;
		std::ifstream myfile ("/etc/sendXMPP.conf");
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
				int oldpos = 0;
				int pos = 0;

				while ((pos = receivers.find(",", pos)) != std::string::npos)
				{
					receiversVect.push_back( receivers.substr(oldpos, pos) );

					++pos;
					oldpos = pos;
				}

				if (oldpos != std::string::npos)
					receiversVect.push_back( receivers.substr(oldpos) );


				SendXMPP sendXMPP(username, password, receiversVect, message);

				return 0;
			}
		}
		else std::cout << "Unable to open file" << std::endl;
	}else{
		std::cout << "Usage: " << argv[0] << " \"<message>\"" << std::endl;
	}

	return 1;
}
