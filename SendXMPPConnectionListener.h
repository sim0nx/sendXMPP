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


#include <string>
#include <vector>
#include <gloox/connectionlistener.h>
#include <gloox/rostermanager.h>
#include <gloox/message.h>
#include <iostream>

using namespace gloox;

class SendXMPPConnectionListener : public ConnectionListener
{
 public:
	SendXMPPConnectionListener(Client *client, const std::vector<std::string> &receivers, const std::string &message,
		const std::string &subject, bool verbose)
		: j(client), msg(message), rcv(receivers), subj(subject), _verbose(verbose)
	{
	}

	virtual void onConnect ()
	{
		if (_verbose)
			std::cout << "connected" << std::endl;

		RosterManager rm(j);
		std::vector<std::string>::iterator it;

		for ( it=rcv.begin() ; it < rcv.end(); ++it )
		{
			rm.ackSubscriptionRequest(*it, true);
			sendMessage(*it, msg, subj);

			if (_verbose)
				std::cout << "sent message to: " << *it << std::endl;
		}

		j->disconnect();
	}

	virtual void onDisconnect ( ConnectionError e )
	{
		if (_verbose)
			std::cout << "disconnected" << std::endl;
	}
	

	void sendMessage(const std::string &receiver, const std::string &message, const std::string &subject="")
	{
		JID jidReceiver(receiver);
		Message m(Message::Normal, jidReceiver, message, subject);
		j->send(m);
	}

	virtual bool onTLSConnect ( const CertInfo &info )
	{
		/*std::cout << info.status << std::endl;
		std::cout << info.chain << std::endl;
		std::cout << info.issuer << std::endl;
		std::cout << info.server << std::endl;
		std::cout << info.date_from << std::endl;
		std::cout << info.date_to << std::endl;
		std::cout << info.protocol << std::endl;
		std::cout << info.cipher << std::endl;
		std::cout << info.mac << std::endl;
		std::cout << info.compression << std::endl;*/


		return true;
	}



 private:
	Client *j;
	std::string msg;
	std::vector<std::string> rcv;
	std::string subj;
	bool _verbose;
};
