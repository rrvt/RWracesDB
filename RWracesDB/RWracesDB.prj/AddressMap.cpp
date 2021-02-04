// Address Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "AddressMap.h"
#include "MapData.h"
#include "NotePad.h"


AddressMap::MyMap AddressMap::myMap;


bool AddressMap::add(AddressRecord& rcd) {
AddsIter::Pair pair;

  if (!rcd.AddressID) rcd.AddressID = nextKey();

  pair = myMap.insert(make_pair(rcd.AddressID, rcd));

  if (pair.second) setKey(rcd.AddressID);

  return pair.second;
  }


bool AddressDB::toTable(AceRecordSet& records, AddressMap& myTable) {
AceFields     fields(records);
AFIter        iter(fields);
AceFieldDsc*  dsc;
int           i;
variant_t     v;
AddressRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0: rcd.AddressID = v; break;
      case  1: rcd.Address1  = v; break;
      case  2: rcd.Address2  = v; break;
      default: return false;
      }
    }

  return myTable.add(rcd);
  }


bool AddressDB::toDatabase(AddressMap& myTable) {
AddsIter       iter(myTable);
AddressRecord* r;

  if (!maps.openRcdSet(_T("Address"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {remove(r->AddressID); iter.remove(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool AddressDB::remove(long key) {return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();}


bool AddressDB::wrt(AddressRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.AddressID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0: rcd.AddressID = dsc->value; continue;
      case  1: v             = rcd.Address1; break;
      case  2: v             = rcd.Address2; break;
      default: return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String AddressRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), AddressID); return s;}
    case  1 :return Address1;
    case  2 :return Address2;
    }

  return _T("");
  }


void AddressRecord::copy(const AddressRecord& r) {
  MapRecord::copy(r); AddressID = r.AddressID; Address1 = r.Address1; Address2 = r.Address2;
  }
