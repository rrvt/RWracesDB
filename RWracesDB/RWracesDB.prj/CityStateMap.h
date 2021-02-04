// CityState Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct CityStateRecord : public MapRecord {
long   CityStateID;
String City;
String State;
String Zip;

  CityStateRecord() : CityStateID(0), City(), State(), Zip() {}
  CityStateRecord(const CityStateRecord& r) {copy(r);}
 ~CityStateRecord() {}

  CityStateRecord& operator= (const CityStateRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const CityStateRecord& r);
  };


class CityStateMap;


class CityStateDB {
AceRecordSet rcdSet;
protected:

  CityStateDB() : rcdSet() {}
 ~CityStateDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, CityStateMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(CityStateMap& myTable);

private:

  bool wrt(CityStateRecord& src);
  bool remove(long key);

  friend class CityStateMap;
  };


class CityStateMap : public MapBase {

typedef map<const long, CityStateRecord> MyMap;

static MyMap myMap;
CityStateDB  myDB;

protected:

  CityStateMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("CityState"));
    }

  bool add(CityStateRecord& rcd);

  int  curSize() {return (int) myMap.size();}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase() {return myDB.toDatabase(*this);}

  friend class CtySIter;
  friend class CityStateDB;
  };

