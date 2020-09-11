// Status Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "StatusMap.h"
#include "MapData.h"
#include "NotePad.h"


StatusTable::MyMap StatusTable::myMap;


bool StatusTable::add(StatusRecord& rcd) {
SttsIter::Pair pair;

  if (!rcd.StsID) rcd.StsID = maxKey + 1;

  pair = myMap.insert(make_pair(rcd.StsID, rcd));

  if (pair.second && rcd.StsID > maxKey) maxKey = rcd.StsID;

  return pair.second;
  }


bool StatusDB::toTable(AceRecordSet& records, StatusTable& myTable) {
AceFields    fields(records);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;
StatusRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0 : rcd.StsID        = v; break;
      case  1 : rcd.Abbreviation        = v; break;
      case  2 : rcd.Description        = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool StatusDB::toDatabase(StatusTable& myTable) {
SttsIter      iter(myTable);
StatusRecord* r;

  if (!maps.openRcdSet(_T("Status"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {erase(r->StsID); iter.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool StatusDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool StatusDB::wrt(StatusRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.StsID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0 : rcd.StsID = dsc->value; continue;
      case  1 : v = rcd.Abbreviation; break;
      case  2 : v = rcd.Description; break;
      default : return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String StatusRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), StsID); return s;}
    case  1 :return Abbreviation;
    case  2 :return Description;
    }

  return _T("");
  }
