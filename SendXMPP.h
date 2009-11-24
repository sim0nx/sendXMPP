#include <vector>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include "SendXMPPConnectionListener.h"

using namespace gloox;


class SendXMPP
{
 public:
	SendXMPP(const std::string &username, const std::string &password, const std::vector<std::string> &receivers, const std::string &message,
			const std::string &subject)
	{
/*		StringList ca;
		ca.push_back("/home/simon/root.crt");
		ca.push_back("/home/simon/trypillCA-cacert.pem");
		ca.push_back("/home/simon/class3.crt");*/

		JID jid(username);
		j = new Client( jid, password );
		j->setTls(TLSRequired);
//		j->setCACerts( ca );
		
		sxConnList = new SendXMPPConnectionListener(j, receivers, message, subject);
		j->registerConnectionListener( sxConnList );
		j->setPresence( PresenceAvailable, 5 );
		j->connect();
	}


 private:
	Client* j;
	SendXMPPConnectionListener *sxConnList;
};
