// Fix Primary eMail


#include "stdafx.h"
#include "RWracesDBDOC.h"
#include "RWracesDB.h"
#include "NotePad.h"



void RWracesDBDoc::OnFixDeadRcds() {
int n = 0;

  notePad << nBeginLine << _T("Deleted Entity Records") << nEndLine << nCrlf;
  n += removeDeadEntityRcds();
  notePad << nBeginLine << _T("Deleted Address Records") << nEndLine << nCrlf;
  n += removeDeadAddrRcds();
  notePad << nBeginLine << _T("Deleted City/State Records") << nEndLine << nCrlf;
  n += removeDeadCityRcds();
  notePad << _T("Deleted ") <<  n << _T(" records.") << nCrlf;
  invalidate();
  }


int RWracesDBDoc::removeDeadEntityRcds() {
EntyIter      iter(entityTable);
EntityRecord* rcd;
long          id;
String        dsp;
int           n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->EntityID;   dsp = rcd->FirstName + _T(" ") + rcd->LastName;

    if (!entityRcdNeeded(id))
      {rcd->del();  notePad << dsp << nCrlf; n++;}
    }

  entityTable.toDatabase();   return n;
  }



bool RWracesDBDoc::entityRcdNeeded(long id) {
MmbrIter      iter(memberTable);
MemberRecord* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->MbrEntityID  == id) return true;
    if (rcd->EmplEntityID == id) return true;
    if (rcd->ICE_EntityID == id) return true;
    }

  return false;
  }



int RWracesDBDoc::removeDeadAddrRcds() {
AddsIter       iter(addressTable);
AddressRecord* rcd;
long           id;
String         dsp;
int            n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->AddressID;    dsp = rcd->Address1;

    if (!addrRcdNeeded(id))
      {rcd->del();  notePad << dsp << nCrlf; n++;}
    }

  addressTable.toDatabase();   return n;
  }



bool RWracesDBDoc::addrRcdNeeded(long id) {
EntyIter      iter(entityTable);
EntityRecord* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->AddrID  == id) return true;

  return false;
  }


int RWracesDBDoc::removeDeadCityRcds() {
CtySIter         iter(cityStateTable);
CityStateRecord* rcd;
long             id;
String           dsp;
int              n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->CityStateID;   dsp = rcd->City + _T(", ") + rcd->State + _T(" ") + rcd->Zip;

    if (!cityRcdNeeded(id))
      {rcd->del();   notePad << dsp << nCrlf; n++;}
    }

  cityStateTable.toDatabase();   return n;
  }



bool RWracesDBDoc::cityRcdNeeded(long id) {
EntyIter      iter(entityTable);
EntityRecord* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->CityStID  == id) return true;

  return false;
  }

