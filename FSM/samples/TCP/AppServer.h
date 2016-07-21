#ifndef _H_APPSERVER
#define _H_APPSERVER

//
// The contents of this file are subject to the Mozilla Public
// License Version 1.1 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy
// of the License at http://www.mozilla.org/MPL/
// 
// Software distributed under the License is distributed on an
// "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
// implied. See the License for the specific language governing
// rights and limitations under the License.
// 
// The Original Code is State Machine Compiler (SMC).
// 
// The Initial Developer of the Original Code is Charles W. Rapp.
// Portions created by Charles W. Rapp are
// Copyright (C) 2000 - 2003 Charles W. Rapp.
// All Rights Reserved.
// 
// Contributor(s): 
//
// Name
//  AppServer.h
//
// Description
//  Encapsulates a TcpServer object.
//
// RCS ID
// $Id: AppServer.h,v 1.6 2009/03/01 18:20:38 cwrapp Exp $
//
// CHANGE LOG
// $Log: AppServer.h,v $
// Revision 1.6  2009/03/01 18:20:38  cwrapp
// Preliminary v. 6.0.0 commit.
//
// Revision 1.5  2007/12/28 12:34:40  cwrapp
// Version 5.0.1 check-in.
//
// Revision 1.4  2005/05/28 13:31:18  cwrapp
// Updated C++ examples.
//
// Revision 1.0  2003/12/14 19:35:24  charlesr
// Initial revision
//

#include "TcpServer.h"
#include "TcpClient.h"
#include "TcpConnectionListener.h"
#include "TimerListener.h"

// Foward declarations.
class AppClient;

class AppServer :
    /* implements */ public TcpConnectionListener,
    /* implements */ public TimerListener
{
// Member functions.
public:

    // Default constructor.
    AppServer();

    // Destructor.
    virtual ~AppServer();

    // Create a TCP server object and open it.
    void open(unsigned short port);

    // Close the TCP service.
    void close();

    // Accepted client socket closed.
    void clientClosed(const AppClient& client);

    // TCP connection listener callback methods.
    void opened(TcpConnection& connection);
    void openFailed(const char *reason,
                    TcpConnection& connection);
    inline void halfClosed(TcpConnection&)
    {};
    void closed(const char *reason,
                TcpConnection& connection);
    void accepted(TcpClient& client, TcpServer& server);

    // These callbacks are never generated by a TCP server.
    void transmitted(TcpConnection&) {};
    void transmitFailed(const char*, TcpConnection&) {};
    void receive(const char*, int, TcpConnection&) {};

    // The "delete clients" timer has expired.
    void handleTimeout(const char *name);

protected:
private:

// Nested classes.
public:
protected:
private:

    class ClientEntry
    {
    public:
        ClientEntry(AppClient& client)
        : _client(&client),
          _next(NULL)
        {};

        ~ClientEntry() {};

        AppClient* getClient() const
        { return(_client);};

        ClientEntry* getNext() const
        { return(_next);};

        void setNext(ClientEntry *entry)
        { _next = entry; };

    private:
        AppClient *_client;
        ClientEntry *_next;

        friend class AppServer;
    };

// Member data.
public:
protected:
private:

    // The TCP service itself.
    TcpServer *_server;

    // Keep track of all the accepted client connections.
    // When this application terminates, they will all be
    // closed and deleted.
    ClientEntry *_clientList;

    // Delete these clients when the timer expires.
    ClientEntry *_deleteList;
};

#endif