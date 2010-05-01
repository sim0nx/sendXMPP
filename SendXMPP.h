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


#include <vector>
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include "SendXMPPConnectionListener.h"

using namespace gloox;


class SendXMPP
{
 public:
	SendXMPP(const std::string &username, const std::string &password, const std::vector<std::string> &receivers, const std::string &message,
			const std::string &subject, bool verbose)
		: j( JID(username), password ), sxConnList(&j, receivers, message, subject, verbose)
	{
/*		StringList ca;
		ca.push_back("/home/simon/root.crt");
		ca.push_back("/home/simon/trypillCA-cacert.pem");
		ca.push_back("/home/simon/class3.crt");*/

		//JID jid(username);
		//j = new Client( jid, password );
		j.setTls(TLSRequired);
//		j->setCACerts( ca );
		
		//sxConnList = new SendXMPPConnectionListener(&j, receivers, message, subject);
		j.registerConnectionListener( &sxConnList );
		j.setPresence( Presence::Available, 5 );
		j.connect();
	}


 private:
	Client j;
	SendXMPPConnectionListener sxConnList;
};
