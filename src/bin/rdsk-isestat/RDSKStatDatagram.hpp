#ifndef RDSKStatDatagramH
#define RDSKStatDatagramH
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

#include <XMLDocument.hpp>
#include <SmallTimeAndDate.hpp>

//------------------------------------------------------------------------------

struct CRDSKStatDatagram {
    // constructor and destructors ------------------------------------------------
    CRDSKStatDatagram(void);

    // set methods ----------------------------------------------------------------
    void Finish(void);

    void SetSite(const CSmallString& site);
    void SetUser(const CSmallString& user);
    void SetHostName(const CSmallString& name);
    void SetHostGroup(const CSmallString& name);
    void SetTimeAndDate(const CSmallTimeAndDate& dt);

    // get methods ----------------------------------------------------------------
    bool IsValid(void);

    const CSmallString      GetSite(void) const;
    const CSmallString      GetUser(void) const;
    const CSmallString      GetHostName(void) const;
    const CSmallString      GetHostGroup(void) const;

    const CSmallTimeAndDate GetTimeAndDate(void) const;

    // section of private data ----------------------------------------------------
private:
    char            Magic[4];               // magic word
    unsigned char   Control[4];             // control sum
    char            Site[128];              // site name
    char            User[128];              // user name
    char            HostName[128];          // hostname
    char            HostGroup[128];         // host group
    unsigned char   Time[4];                // time in seconds from 00:00:00 UTC, January 1, 1970
};

//------------------------------------------------------------------------------

#endif
