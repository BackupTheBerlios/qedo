/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

static char rcsid[] = "$Id: csa.cpp,v 1.1 2002/10/07 07:17:02 tom Exp $";

#include "ServerActivatorImpl.h"

#include <iostream>
#include <cstring>
#include <JTC/JTC.h>

using namespace std;

int
main (int argc, char** argv)
{
	try {
	cout << "Qedo Component Server Activator" << endl;

	// Check for debug mode
	bool debug_mode = false;

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp(argv[i], "--debug"))
		{
			debug_mode = true;
			break;
		}
	}

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	Qedo::ServerActivatorImpl* server_activator = new Qedo::ServerActivatorImpl (orb, debug_mode);

	try
	{
		server_activator->initialize();
	}
	catch (Qedo::ServerActivatorImpl::CannotInitialize&)
	{
		cerr << "Cannot initialize Component Server Activator... exiting." << endl;
		orb->destroy();
		exit (1);
	}

	orb->run();
	}
	catch (const JTCException&e )
	{
		cerr << "caught JTCException" << endl;
		cerr << e << endl;
	}
}

