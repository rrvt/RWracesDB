// Status Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct StatusRecord : public MapRecord {
long   StsID;
String Abbreviation;
String Description;

  StatusRecord() : StsID(0), Abbreviation(), Description() {}
  StatusRecord(const StatusRecord& r) {copy(r);}
 ~StatusRecord() {}

  StatusRecord& operator= (const StatusRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const StatusRecord& r);
  };


class StatusMap;


class StatusDB {
AceRecordSet rcdSet;
protected:

  StatusDB() : rcdSet() {}
 ~StatusDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, StatusMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(StatusMap& myTable);

private:

  bool wrt(StatusRecord& src);
  bool remove(long key);

  friend class StatusMap;
  };


class StatusMap : public MapBase {

typedef map<const long, StatusRecord> MyMap;

static MyMap myMap;
StatusDB     myDB;

protected:

  StatusMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("Status"));
    }

  bool add(StatusRecord& rcd);

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

  friend class SttsIter;
  friend class StatusDB;
  };

