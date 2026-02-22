#ifndef RDSKStatServerH
#define RDSKStatServerH
// =============================================================================
// RDSK Monitoring Server CMake File
// -----------------------------------------------------------------------------
//     Copyright (C) 2026 Petr Kulhanek (kulhanek@chemi.muni.cz)
//
//     This program is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License along
//     with this program; if not, write to the Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// =============================================================================

#include <FirebirdDatabase.hpp>
#include <FirebirdTransaction.hpp>
#include <XMLDocument.hpp>
#include <VerboseStr.hpp>
#include <TerminalStr.hpp>
#include "RDSKStatDatagram.hpp"
#include "ServerWatcher.hpp"
#include "RDSKStatServerOptions.hpp"

//------------------------------------------------------------------------------

class CRDSKStatServer {
public:
// constructor and destructors -------------------------------------------------
    CRDSKStatServer(void);
    ~CRDSKStatServer(void);

// main methods ----------------------------------------------------------------
    /// init options
    int Init(int argc,char* argv[]);

    /// main part of program
    bool Run(void);

    /// finalize
    void Finalize(void);

// input methods ---------------------------------------------------------------
    //! load server config
    bool LoadConfig(void);

    //! init server, e.g. open database
    bool InitServer(void);

// information methods ---------------------------------------------------------
    //! return the name of database
    const CSmallString GetDatabaseName(void);

    //! return the name of user for access to the database
    const CSmallString GetDatabaseUser(void);

    //! return the password for access to the database
    const CSmallString GetDatabasePassword(void);

    //! return the port number to listen on
    int GetPortNumber(void);

// execute server --------------------------------------------------------------
    //! execute server
    bool ExecuteServer(void);

    //! terminate server
    bool ShutdownServer(void);

// section of private data -----------------------------------------------------
private:
    CRDSKStatServerOptions   Options;
    CTerminalStr            Console;
    CVerboseStr             vout;
    CXMLDocument            ServerConfig;
    CFirebirdDatabase       Database;
    CFirebirdTransaction    Transaction;
    bool                    Terminated;
    int                     Socket;
    CServerWatcher          Watcher;

    //! is client authorized to write data to database?
    bool IsClientAuthorized(const char* p_name);

    //! interuption handler
    static void CtrlCSignalHandler(int signal);

    //! write datagram to database
    bool WriteDataToDatabase(CRDSKStatDatagram& datagram);

    //! get key id
    int GetKeyID(const CSmallString& key);
};

// -----------------------------------------------------------------------------

extern CRDSKStatServer Server;

// -----------------------------------------------------------------------------

#endif
