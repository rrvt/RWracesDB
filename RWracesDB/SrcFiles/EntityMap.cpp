// Entity Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "EntityMap.h"
#include "MapData.h"
#include "NotePad.h"


EntityTable::MyMap EntityTable::myMap;


bool EntityTable::add(EntityRecord& rcd) {
EntyIter::Pair pair;

  if (!rcd.EntityID) rcd.EntityID = maxKey + 1;

  pair = myMap.insert(make_pair(rcd.EntityID, rcd));

  if (pair.second && rcd.EntityID > maxKey) maxKey = rcd.EntityID;

  return pair.second;
  }


bool EntityDB::toTable(AceRecordSet& records, EntityTable& myTable) {
AceFields    fields(records);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;
EntityRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0 : rcd.EntityID      = v; break;
      case  1 : rcd.FirstName      = v; break;
      case  2 : rcd.MiddleInitial      = v; break;
      case  3 : rcd.LastName      = v; break;
      case  4 : rcd.Suffix      = v; break;
      case  5 : rcd.AddrID      = v; break;
      case  6 : rcd.CityStID      = v; break;
      case  7 : rcd.AddrIsPO      = v; break;
      case  8 : rcd.LocationZip      = v; break;
      case  9 : rcd.eMail      = v; break;
      case 10 : rcd.Phone1      = v; break;
      case 11 : rcd.Phone2      = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool EntityDB::toDatabase(EntityTable& myTable) {
EntyIter      iter(myTable);
EntityRecord* r;

  if (!maps.openRcdSet(_T("Entity"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {erase(r->EntityID); iter.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool EntityDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool EntityDB::wrt(EntityRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.EntityID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0 : rcd.EntityID = dsc->value; continue;
      case  1 : v = rcd.FirstName; break;
      case  2 : v = rcd.MiddleInitial; break;
      case  3 : v = rcd.LastName; break;
      case  4 : v = rcd.Suffix; break;
      case  5 : v = rcd.AddrID; break;
      case  6 : v = rcd.CityStID; break;
      case  7 : v = rcd.AddrIsPO; break;
      case  8 : v = rcd.LocationZip; break;
      case  9 : v = rcd.eMail; break;
      case 10 : v = rcd.Phone1; break;
      case 11 : v = rcd.Phone2; break;
      default : return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String EntityRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), EntityID); return s;}
    case  1 :return FirstName;
    case  2 :return MiddleInitial;
    case  3 :return LastName;
    case  4 :return Suffix;
    case  5 :{String s; s.format(_T("%i"), AddrID); return s;}
    case  6 :{String s; s.format(_T("%i"), CityStID); return s;}
    case  7 :{String s; s.format(_T("%i"), AddrIsPO); return s;}
    case  8 :return LocationZip;
    case  9 :return eMail;
    case 10 :return Phone1;
    case 11 :return Phone2;
    }

  return _T("");
  }

