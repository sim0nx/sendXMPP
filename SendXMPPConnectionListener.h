#include <string>
#include <vector>
#include <gloox/connectionlistener.h>
#include <gloox/rostermanager.h>
#include <iostream>

using namespace gloox;

class SendXMPPConnectionListener : public ConnectionListener
{
 public:
	SendXMPPConnectionListener(Client *client, const std::vector<std::string> &receivers, const std::string &message)
	{
		j = client;
		msg = message;
		rcv = receivers;
	}

	virtual void onConnect ()
	{
		//std::cout << "connected" << std::endl;

		RosterManager rm(j);
		std::vector<std::string>::iterator it;

		for ( it=rcv.begin() ; it < rcv.end(); ++it )
		{
			rm.ackSubscriptionRequest(*it, true);
			sendMessage(*it, msg);
		}

		j->disconnect();
	}

	virtual void onDisconnect ( ConnectionError e ){}
	

	void sendMessage(const std::string &receiver, const std::string &message)
	{
		JID jidReceiver(receiver);
		Stanza *s = Stanza::createMessageStanza(jidReceiver, message);
		j->send(s);
	}

	virtual bool onTLSConnect ( const CertInfo &info ){}



 private:
	Client *j;
	std::string msg;
	std::vector<std::string> rcv;
};
