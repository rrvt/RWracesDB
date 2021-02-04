// A little class to initialize of the Table classes and load the data from the database
// MapData Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.


#include "stdafx.h"
#include "MapData.h"
#include "IniFile.h"
#include "NotePad.h"


TCchar* FileSection    = _T("DataBase File Names");
TCchar* DBFileKey      = _T("DataBase File");
TCchar* GenFilePathKey = _T("GenFilePath");


Maps maps;


void MapData::initializeMaps() {
TLIter     iter(tblList);
TblDsc*    dsc;
AceTables  aceTables(dao);
ATIter     atIter(aceTables);
TableDesc* atDsc;

  tblList.add(addressTable);
  tblList.add(assgnPrefTable);
  tblList.add(cityStateTable);
  tblList.add(entityTable);
  tblList.add(locationPrefTable);
  tblList.add(memberTable);
  tblList.add(statusTable);

  for (dsc = iter(); dsc; dsc = iter++) if (dsc->mapTable) dsc->mapTable->initialize();

  for (atDsc = atIter(); atDsc; atDsc = atIter++) tblList.add(atDsc->name, 0);
  }


bool MapData::openDB(TCchar* path) {return dao.open(path);}


void MapData::closeDB() {dao.close();}


bool MapData::openRcdSet(TCchar* name, DaoOptions option, AceRecordSet& rcdSet) {
AceTables tables(dao);

  return rcdSet.open(tables.find(name), DaoDenyWrite);
  }


bool MapData::openFldDscs(TCchar* name, AceFieldNames& fldDscs) {
AceTables  tables(dao);
TableDesc* tableDsc = tables.find(name);       if (!tableDsc) return 0;

  return fldDscs.open(tableDsc);
  }

