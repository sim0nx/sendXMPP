#include <string>
#include <vector>
#include <gloox/connectionlistener.h>
#include <gloox/rostermanager.h>
#include <iostream>

using namespace gloox;

class SendXMPPConnectionListener : public ConnectionListener
{
 public:
	SendXMPPConnectionListener(Client *client, const std::vector<std::string> &receivers, const std::string &message,
		const std::string &subject)
		: j(client), msg(message), rcv(receivers), subj(subject)
	{
	}

	virtual void onConnect ()
	{
		//std::cout << "connected" << std::endl;

		RosterManager rm(j);
		std::vector<std::string>::iterator it;

		for ( it=rcv.begin() ; it < rcv.end(); ++it )
		{
			rm.ackSubscriptionRequest(*it, true);
			sendMessage(*it, msg, subj);
		}

		j->disconnect();
	}

	virtual void onDisconnect ( ConnectionError e ){}
	

	void sendMessage(const std::string &receiver, const std::string &message, const std::string &subject="")
	{
		JID jidReceiver(receiver);
		Stanza *s = Stanza::createMessageStanza(jidReceiver, message, StanzaMessageChat, subject);
		j->send(s);
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
};
