// Dead Record Removal


#include "pch.h"
#include "DeadRcds.h"
#include "Database.h"
#include "NotePad.h"


void DeadRcds::fix(TCchar* path) {
int n = 0;

  notePad.clear();

  notePad << nBeginLine << _T("Deleted Entity Records") << nEndLine << nCrlf;
  n += removeDeadEntityRcds(path);
  notePad << nBeginLine << _T("Deleted Address Records") << nEndLine << nCrlf;
  n += removeDeadAddrRcds(path);
  notePad << nBeginLine << _T("Deleted City/State Records") << nEndLine << nCrlf;
  n += removeDeadCityRcds(path);
  notePad << _T("Deleted ") <<  n << _T(" records.") << nCrlf;
  }


int DeadRcds::removeDeadEntityRcds(TCchar* path) {
EntIter iter(entTbl);
EntRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();   dsp = rcd->firstName + _T(" ") + rcd->lastName;

    if (!entityRcdNeeded(id))
      {rcd->setRemove();  notePad << dsp << nCrlf; n++;}
    }

  entTbl.store(path);   return n;
  }


bool DeadRcds::entityRcdNeeded(long id) {
MbrIter iter(mbrTbl);
MbrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->mbrEntityID  == id) return true;
    if (rcd->emplEntityID == id) return true;
    if (rcd->iCE_EntityID == id) return true;
    }

  return false;
  }


int DeadRcds::removeDeadAddrRcds(TCchar* path) {
AdrIter iter(adrTbl);
AdrRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();    dsp = rcd->address1;

    if (!addrRcdNeeded(id))
      {rcd->setRemove();  notePad << dsp << nCrlf; n++;}
    }

  adrTbl.store(path);   return n;
  }



bool DeadRcds::addrRcdNeeded(long id) {
EntIter    iter(entTbl);
EntRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->addrID  == id) return true;

  return false;
  }


int DeadRcds::removeDeadCityRcds(TCchar* path) {
CtyIter iter(ctyTbl);
CtyRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();   dsp = rcd->city + _T(", ") + rcd->state + _T(" ") + rcd->zip;

    if (!cityRcdNeeded(id))
      {rcd->setRemove();   notePad << dsp << nCrlf; n++;}
    }

  ctyTbl.store(path);   return n;
  }



bool DeadRcds::cityRcdNeeded(long id) {
EntIter    iter(entTbl);
EntRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->cityStID  == id) return true;

  return false;
  }




#if 1
#else
#include "AddressTbl.h"
#include "CityStateTbl.h"
#include "EntityTbl.h"
#include "MemberTbl.h"
#endif
//#include "RWracesDB.h"
//#include "RWracesDBView.h"

