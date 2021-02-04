// LocationPref Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "LocationPrefMap.h"
#include "MapData.h"
#include "NotePad.h"


LocationPrefMap::MyMap LocationPrefMap::myMap;


bool LocationPrefMap::add(LocationPrefRecord& rcd) {
LcPfIter::Pair pair;

  if (!rcd.LocationPrefID) rcd.LocationPrefID = nextKey();

  pair = myMap.insert(make_pair(rcd.LocationPrefID, rcd));

  if (pair.second) setKey(rcd.LocationPrefID);

  return pair.second;
  }


bool LocationPrefDB::toTable(AceRecordSet& records, LocationPrefMap& myTable) {
AceFields          fields(records);
AFIter             iter(fields);
AceFieldDsc*       dsc;
int                i;
variant_t          v;
LocationPrefRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0: rcd.LocationPrefID = v; break;
      case  1: rcd.Key            = v; break;
      case  2: rcd.Txt            = v; break;
      default: return false;
      }
    }

  return myTable.add(rcd);
  }


bool LocationPrefDB::toDatabase(LocationPrefMap& myTable) {
LcPfIter            iter(myTable);
LocationPrefRecord* r;

  if (!maps.openRcdSet(_T("LocationPref"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {remove(r->LocationPrefID); iter.remove(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool LocationPrefDB::remove(long key) {return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();}


bool LocationPrefDB::wrt(LocationPrefRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.LocationPrefID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0: rcd.LocationPrefID = dsc->value; continue;
      case  1: v                  = rcd.Key; break;
      case  2: v                  = rcd.Txt; break;
      default: return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String LocationPrefRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), LocationPrefID); return s;}
    case  1 :return Key;
    case  2 :return Txt;
    }

  return _T("");
  }


void LocationPrefRecord::copy(const LocationPrefRecord& r) {
  MapRecord::copy(r); LocationPrefID = r.LocationPrefID; Key = r.Key; Txt = r.Txt;
  }
