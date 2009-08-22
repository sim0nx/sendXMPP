#include <vector>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include "SendXMPPConnectionListener.h"

using namespace gloox;


class SendXMPP
{
 public:
	SendXMPP(const std::string &username, const std::string &password, const std::vector<std::string> &receivers, const std::string &message)
	{
		JID jid(username);
		j = new Client( jid, password );
		j->setTls(TLSRequired);
		
		sxConnList = new SendXMPPConnectionListener(j, receivers, message);
		j->registerConnectionListener( sxConnList );
		j->setPresence( PresenceAvailable, 5 );
		j->connect();
	}


 private:
	Client* j;
	SendXMPPConnectionListener *sxConnList;
};
