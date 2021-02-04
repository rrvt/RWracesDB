// LocationPref Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct LocationPrefRecord : public MapRecord {
long   LocationPrefID;
String Key;
String Txt;

  LocationPrefRecord() : LocationPrefID(0), Key(), Txt() {}
  LocationPrefRecord(const LocationPrefRecord& r) {copy(r);}
 ~LocationPrefRecord() {}

  LocationPrefRecord& operator= (const LocationPrefRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const LocationPrefRecord& r);
  };


class LocationPrefMap;


class LocationPrefDB {
AceRecordSet rcdSet;
protected:

  LocationPrefDB() : rcdSet() {}
 ~LocationPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, LocationPrefMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(LocationPrefMap& myTable);

private:

  bool wrt(LocationPrefRecord& src);
  bool remove(long key);

  friend class LocationPrefMap;
  };


class LocationPrefMap : public MapBase {

typedef map<const long, LocationPrefRecord> MyMap;

static MyMap   myMap;
LocationPrefDB myDB;

protected:

  LocationPrefMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("LocationPref"));
    }

  bool add(LocationPrefRecord& rcd);

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

  friend class LcPfIter;
  friend class LocationPrefDB;
  };

