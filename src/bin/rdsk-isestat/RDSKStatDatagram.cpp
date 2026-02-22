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

#include "RDSKStatDatagram.hpp"
#include <ErrorSystem.hpp>
#include <string.h>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CRDSKStatDatagram::CRDSKStatDatagram(void)
{
    memset(Magic,0,sizeof(Magic));
    memset(Control,0,sizeof(Control));
    memset(Site,0,sizeof(Site));
    memset(User,0,sizeof(User));
    memset(HostName,0,sizeof(HostName));
    memset(HostGroup,0,sizeof(HostGroup));
    memset(Time,0,sizeof(Time));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CRDSKStatDatagram::Finish(void)
{
    // magic header
    memcpy(Magic,"RDSK",4);

    // controll sum
    int control_sum = 0;
    for(unsigned int i=0; i < sizeof(Magic); i++) control_sum += Magic[i];
    for(unsigned int i=0; i < sizeof(Site); i++) control_sum += Site[i];
    for(unsigned int i=0; i < sizeof(User); i++) control_sum += User[i];
    for(unsigned int i=0; i < sizeof(HostName); i++) control_sum += HostName[i];
    for(unsigned int i=0; i < sizeof(HostGroup); i++) control_sum += HostGroup[i];
    for(unsigned int i=0; i < sizeof(Time); i++) control_sum += Time[i];

    Control[0] = (unsigned char) ((control_sum >> 24) & 0xFF);
    Control[1] = (unsigned char) ((control_sum >> 16) & 0xFF);
    Control[2] = (unsigned char) ((control_sum >>  8) & 0xFF);
    Control[3] = (unsigned char) ((control_sum      ) & 0xFF);
}

//------------------------------------------------------------------------------

void CRDSKStatDatagram::SetSite(const CSmallString& site)
{
    // -1 for \0 termination character
    strncpy(Site,site,sizeof(Site)-1);
}

//------------------------------------------------------------------------------

void CRDSKStatDatagram::SetUser(const CSmallString& name)
{
    // -1 for \0 termination character
    strncpy(User,name,sizeof(User)-1);
}


//------------------------------------------------------------------------------

void CRDSKStatDatagram::SetHostName(const CSmallString& name)
{
    strncpy(HostName,name,sizeof(HostName)-1);
}

//------------------------------------------------------------------------------

void CRDSKStatDatagram::SetHostGroup(const CSmallString& name)
{
    strncpy(HostGroup,name,sizeof(HostGroup)-1);
}

//------------------------------------------------------------------------------

void CRDSKStatDatagram::SetTimeAndDate(const CSmallTimeAndDate& dt)
{
    int seconds = dt.GetSecondsFromBeginning();

    Time[0] = (unsigned char) ((seconds >> 24) & 0xFF);
    Time[1] = (unsigned char) ((seconds >> 16) & 0xFF);
    Time[2] = (unsigned char) ((seconds >>  8) & 0xFF);
    Time[3] = (unsigned char) ((seconds      ) & 0xFF);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CRDSKStatDatagram::IsValid(void)
{
    // magic header
    if( strncmp(Magic,"RDSK",4) != 0 ) {
        return(false);
    }

    // controll sum
    int control_sum = 0;
    for(unsigned int i=0; i < sizeof(Magic); i++) control_sum += Magic[i];
    for(unsigned int i=0; i < sizeof(Site); i++) control_sum += Site[i];
    for(unsigned int i=0; i < sizeof(User); i++) control_sum += User[i];
    for(unsigned int i=0; i < sizeof(HostName); i++) control_sum += HostName[i];
    for(unsigned int i=0; i < sizeof(HostGroup); i++) control_sum += HostGroup[i];
    for(unsigned int i=0; i < sizeof(Time); i++) control_sum += Time[i];

    int rec_control_sum;
    rec_control_sum = (Control[0] << 24) + (Control[1] << 16)
                      + (Control[2] << 8) + Control[3];

    if( rec_control_sum != control_sum ) {
        CSmallString error;
        error << "sum: " << CSmallString(rec_control_sum) << " rec: " << CSmallString(control_sum);
        ES_ERROR(error);
        return(false);
    }

    return(true);
}

//------------------------------------------------------------------------------

const CSmallString CRDSKStatDatagram::GetSite(void) const
{
    return(Site);
}

//------------------------------------------------------------------------------

const CSmallString CRDSKStatDatagram::GetUser(void) const
{
    return(User);
}

//------------------------------------------------------------------------------

const CSmallString CRDSKStatDatagram::GetHostName(void) const
{
    return(HostName);
}

//------------------------------------------------------------------------------

const CSmallString CRDSKStatDatagram::GetHostGroup(void) const
{
    return(HostGroup);
}

//------------------------------------------------------------------------------

const CSmallTimeAndDate CRDSKStatDatagram::GetTimeAndDate(void) const
{
    int seconds_from_beginning = (Time[0] << 24) + (Time[1] << 16) + (Time[2] << 8) + Time[3];

    CSmallTimeAndDate dt(seconds_from_beginning);
    return(dt);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
