// Dead Record Removal


#include "stdafx.h"
#include "DeadRcds.h"
#include "AddressTbl.h"
#include "CityStateTbl.h"
#include "EntityTbl.h"
#include "MemberTbl.h"
#include "NotePad.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"


void DeadRcds::fix() {
int n = 0;

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  notePad << nBeginLine << _T("Deleted Entity Records") << nEndLine << nCrlf;
  n += removeDeadEntityRcds();
  notePad << nBeginLine << _T("Deleted Address Records") << nEndLine << nCrlf;
  n += removeDeadAddrRcds();
  notePad << nBeginLine << _T("Deleted City/State Records") << nEndLine << nCrlf;
  n += removeDeadCityRcds();
  notePad << _T("Deleted ") <<  n << _T(" records.") << nCrlf;
  }


int DeadRcds::removeDeadEntityRcds() {
EntIter    iter(entityTbl);
EntityRcd* rcd;
long       id;
String     dsp;
int        n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->id;   dsp = rcd->firstName + _T(" ") + rcd->lastName;

    if (!entityRcdNeeded(id))
      {rcd->del();  notePad << dsp << nCrlf; n++;}
    }

  entityTbl.store();   return n;
  }


bool DeadRcds::entityRcdNeeded(long id) {
MbrIter    iter(memberTbl);
MemberRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->mbrEntityID  == id) return true;
    if (rcd->emplEntityID == id) return true;
    if (rcd->ice_EntityID == id) return true;
    }

  return false;
  }


int DeadRcds::removeDeadAddrRcds() {
AdrIter     iter(addressTbl);
AddressRcd* rcd;
long        id;
String      dsp;
int         n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->id;    dsp = rcd->address1;

    if (!addrRcdNeeded(id))
      {rcd->del();  notePad << dsp << nCrlf; n++;}
    }

  addressTbl.store();   return n;
  }



bool DeadRcds::addrRcdNeeded(long id) {
EntIter    iter(entityTbl);
EntityRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->id  == id) return true;

  return false;
  }


int DeadRcds::removeDeadCityRcds() {
CtyIter         iter(cityStateTbl);
CityStateRcd* rcd;
long             id;
String           dsp;
int              n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->id;   dsp = rcd->city + _T(", ") + rcd->state + _T(" ") + rcd->zip;

    if (!cityRcdNeeded(id))
      {rcd->del();   notePad << dsp << nCrlf; n++;}
    }

  cityStateTbl.store();   return n;
  }



bool DeadRcds::cityRcdNeeded(long id) {
EntIter    iter(entityTbl);
EntityRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->cityStID  == id) return true;

  return false;
  }


