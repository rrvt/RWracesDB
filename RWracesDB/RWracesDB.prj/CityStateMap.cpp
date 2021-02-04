// CityState Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "CityStateMap.h"
#include "MapData.h"
#include "NotePad.h"


CityStateMap::MyMap CityStateMap::myMap;


bool CityStateMap::add(CityStateRecord& rcd) {
CtySIter::Pair pair;

  if (!rcd.CityStateID) rcd.CityStateID = nextKey();

  pair = myMap.insert(make_pair(rcd.CityStateID, rcd));

  if (pair.second) setKey(rcd.CityStateID);

  return pair.second;
  }


bool CityStateDB::toTable(AceRecordSet& records, CityStateMap& myTable) {
AceFields       fields(records);
AFIter          iter(fields);
AceFieldDsc*    dsc;
int             i;
variant_t       v;
CityStateRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0: rcd.CityStateID = v; break;
      case  1: rcd.City        = v; break;
      case  2: rcd.State       = v; break;
      case  3: rcd.Zip         = v; break;
      default: return false;
      }
    }

  return myTable.add(rcd);
  }


bool CityStateDB::toDatabase(CityStateMap& myTable) {
CtySIter         iter(myTable);
CityStateRecord* r;

  if (!maps.openRcdSet(_T("CityState"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {remove(r->CityStateID); iter.remove(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool CityStateDB::remove(long key) {return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();}


bool CityStateDB::wrt(CityStateRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.CityStateID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0: rcd.CityStateID = dsc->value; continue;
      case  1: v               = rcd.City; break;
      case  2: v               = rcd.State; break;
      case  3: v               = rcd.Zip; break;
      default: return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String CityStateRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), CityStateID); return s;}
    case  1 :return City;
    case  2 :return State;
    case  3 :return Zip;
    }

  return _T("");
  }


void CityStateRecord::copy(const CityStateRecord& r) {
  MapRecord::copy(r); CityStateID = r.CityStateID; City = r.City; State = r.State; Zip = r.Zip;
  }
