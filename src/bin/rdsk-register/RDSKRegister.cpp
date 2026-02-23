// =============================================================================
// RDSK Monitoring Server CMake File
// -----------------------------------------------------------------------------
//     Copyright (C) 2026 Petr Kulhanek (kulhanek@chemi.muni.cz)
//
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2.1 of the License, or (at your option) any later version.
//
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.
//
//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 51 Franklin Street, Fifth Floor,
//     Boston, MA  02110-1301  USA
// =============================================================================

#include <ErrorSystem.hpp>
#include "RDSKRegister.hpp"
#include "DatagramSender.hpp"

//------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------

CRDSKRegister Client;

MAIN_ENTRY_OBJECT(Client)

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CRDSKRegister::CRDSKRegister(void)
{

}

//------------------------------------------------------------------------------

CRDSKRegister::~CRDSKRegister(void)
{
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CRDSKRegister::Init(int argc, char* argv[])
{
    // encode program options, all check procedures are done inside of CABFIntOpts
    int result = Options.ParseCmdLine(argc,argv);

    // should we exit or was it error?
    if( result != SO_CONTINUE ) return(result);

    // stdout is used for shell processor
    Console.Attach(stdout);

    // attach verbose stream to terminal stream and set desired verbosity level
    vout.Attach(Console);
    if( Options.GetOptVerbose() ) {
        vout.Verbosity(CVerboseStr::high);
    } else {
        vout.Verbosity(CVerboseStr::low);
    }

    CSmallTimeAndDate dt;
    dt.GetActualTimeAndDate();

    vout << high;
    vout << endl;
    vout << "# ==============================================================================" << endl;
    vout << "# rdsk-register started at " << dt.GetSDateAndTime() << endl;
    vout << "# ==============================================================================" << endl;

    return(SO_CONTINUE);
}

//------------------------------------------------------------------------------

bool CRDSKRegister::Run(void)
{
    CDatagramSender sender;

    CSmallString value;
    value = GetSystemVariable("AMS_SITE");
    sender.Datagram.SetSite(value);
    vout << "AMS_SITE       = " << value << endl;

    value = GetSystemVariable("USER");
    sender.Datagram.SetUser(value);
    vout << "USER           = " << value << endl;

    value = GetSystemVariable("HOSTNAME");
    sender.Datagram.SetHostName(value);
    vout << "HOSTNAME       = " << value << endl;

    value = GetSystemVariable("AMS_HOST_GROUP");
    sender.Datagram.SetHostGroup(value);
    vout << "AMS_HOST_GROUP = " << value << endl;

    CSmallTimeAndDate dt;
    dt.GetActualTimeAndDate();
    sender.Datagram.SetTimeAndDate(dt);

    sender.Datagram.Finish();

    return(sender.SendDataToServer(Options.GetArgServerName(),Options.GetArgServerPort()));
}

//------------------------------------------------------------------------------

const CSmallString CRDSKRegister::GetSystemVariable(const CSmallString& name)
{
    if( name == NULL ) return("");
    return(CSmallString(getenv(name)));
}

//------------------------------------------------------------------------------

void CRDSKRegister::Finalize(void)
{
    CSmallTimeAndDate dt;
    dt.GetActualTimeAndDate();

    vout << high;
    vout << endl;
    vout << "# ==============================================================================" << endl;
    vout << "# rdsk-register terminated at " << dt.GetSDateAndTime() << endl;
    vout << "# ==============================================================================" << endl;

    if( ErrorSystem.IsError() || Options.GetOptVerbose() ){
        ErrorSystem.PrintErrors(vout);
    }

    vout << endl;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
