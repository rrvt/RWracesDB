// AssgnPref Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct AssgnPrefRecord : public MapRecord {
long   AssgnPrefID;
String APKey;
String Txt;

  AssgnPrefRecord() : AssgnPrefID(0), APKey(), Txt() {}
  AssgnPrefRecord(const AssgnPrefRecord& r) {copy(r);}
 ~AssgnPrefRecord() {}

  AssgnPrefRecord& operator= (const AssgnPrefRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const AssgnPrefRecord& r);
  };


class AssgnPrefMap;


class AssgnPrefDB {
AceRecordSet rcdSet;
protected:

  AssgnPrefDB() : rcdSet() {}
 ~AssgnPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AssgnPrefMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AssgnPrefMap& myTable);

private:

  bool wrt(AssgnPrefRecord& src);
  bool remove(long key);

  friend class AssgnPrefMap;
  };


class AssgnPrefMap : public MapBase {

typedef map<const long, AssgnPrefRecord> MyMap;

static MyMap myMap;
AssgnPrefDB  myDB;

protected:

  AssgnPrefMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("AssgnPref"));
    }

  bool add(AssgnPrefRecord& rcd);

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

  friend class AgPfIter;
  friend class AssgnPrefDB;
  };

