// Address Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct AddressRecord : public MapRecord {
long   AddressID;
String Address1;
String Address2;

  AddressRecord() : AddressID(0), Address1(), Address2() {}
  AddressRecord(const AddressRecord& r) {copy(r);}
 ~AddressRecord() {}

  AddressRecord& operator= (const AddressRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const AddressRecord& r);
  };


class AddressMap;


class AddressDB {
AceRecordSet rcdSet;
protected:

  AddressDB() : rcdSet() {}
 ~AddressDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AddressMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AddressMap& myTable);

private:

  bool wrt(AddressRecord& src);
  bool remove(long key);

  friend class AddressMap;
  };


class AddressMap : public MapBase {

typedef map<const long, AddressRecord> MyMap;

static MyMap myMap;
AddressDB    myDB;

protected:

  AddressMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("Address"));
    }

  bool add(AddressRecord& rcd);

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

  friend class AddsIter;
  friend class AddressDB;
  };

