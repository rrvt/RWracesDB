// AssgnPref Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#include "stdafx.h"
#include "AssgnPrefMap.h"
#include "MapData.h"
#include "NotePad.h"


AssgnPrefTable::MyMap AssgnPrefTable::myMap;


bool AssgnPrefTable::add(AssgnPrefRecord& rcd) {
AgPfIter::Pair pair;

  if (!rcd.AssgnPrefID) rcd.AssgnPrefID = maxKey + 1;

  pair = myMap.insert(make_pair(rcd.AssgnPrefID, rcd));

  if (pair.second && rcd.AssgnPrefID > maxKey) maxKey = rcd.AssgnPrefID;

  return pair.second;
  }


bool AssgnPrefDB::toTable(AceRecordSet& records, AssgnPrefTable& myTable) {
AceFields       fields(records);
AFIter          iter(fields);
AceFieldDsc*    dsc;
int             i;
variant_t       v;
AssgnPrefRecord rcd;

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    v = dsc->value;
    switch (i) {
      case  0 : rcd.AssgnPrefID = v; break;
      case  1 : rcd.APKey = v; break;
      case  2 : rcd.Txt = v; break;
      default : return false;
      }
    }

  return myTable.add(rcd);
  }


bool AssgnPrefDB::toDatabase(AssgnPrefTable& myTable) {
AgPfIter         iter(myTable);
AssgnPrefRecord* r;

  if (!maps.openRcdSet(_T("AssgnPref"), DaoDenyWrite, rcdSet)) return false;

  for (r = iter(); r; r = iter++) {

    if (r->toDelete()) {erase(r->AssgnPrefID); iter.erase(); continue;}

    if (r->isDirty()) {wrt(*r); r->clearMarks();}
    }

  rcdSet.close();   return true;
  }


bool AssgnPrefDB::erase(long key) {
  return rcdSet.findRecord(key) && rcdSet.deleteCurrentRecord();
  }


bool AssgnPrefDB::wrt(AssgnPrefRecord& rcd) {
AceFields    fields(rcdSet);
AFIter       iter(fields);
AceFieldDsc* dsc;
int          i;
variant_t    v;

  if (rcdSet.findRecord(rcd.AssgnPrefID)) rcdSet.edit();
  else rcdSet.addNew();

  for (dsc = iter(), i = 0; dsc; dsc = iter++, i++) {
    switch (i) {
      case  0 : rcd.AssgnPrefID = dsc->value; continue;
      case  1 : v = rcd.APKey; break;
      case  2 : v = rcd.Txt; break;
      default : return false;
      }

    dsc->write(v);
    }

  return rcdSet.update() != 0;
  }


String AssgnPrefRecord::getFldVal(int i) {
  switch (i) {
    case  0 :{String s; s.format(_T("%i"), AssgnPrefID); return s;}
    case  1 :return APKey;
    case  2 :return Txt;
    }

  return _T("");
  }

