// Address Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct AddressRecord : public MapRecord {
long   AddressID;
String Address1;
String Address2;

  AddressRecord() : AddressID(0), Address1(), Address2() {}
  AddressRecord(const AddressRecord& r) : MapRecord(r), AddressID(r.AddressID),
           Address1(r.Address1), Address2(r.Address2) {}
 ~AddressRecord() {}

  AddressRecord operator= (AddressRecord& r) {
    copy(r, *this); AddressID = r.AddressID; Address1 = r.Address1;
    Address2 = r.Address2;
    }

  String getFldVal(int i);
  };


class AddressTable;


class AddressDB {
AceRecordSet rcdSet;
public:

  AddressDB() : rcdSet() {}
 ~AddressDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AddressTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AddressTable& myTable);

private:

  bool wrt(AddressRecord& src);
  bool erase(long key);
  };


class AddressTable : public MapTable {

typedef map<const long, AddressRecord> MyMap;

static MyMap myMap;
long         maxKey;
AddressDB    myDB;

public:

  AddressTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Address"));
    }

  bool add(AddressRecord& rcd);

  int  curSize() {return (int) myMap.size();}

  long nextKey() {return maxKey+1;}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records) {return myDB.toTable(records, *this);}

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase() {return myDB.toDatabase(*this);}

  friend class AddsIter;
  };


class AddsIter {

typedef AddressTable::MyMap MyMap;
typedef MyMap::iterator     MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  AddsIter(AddressTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  AddressRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 :&iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  AddressRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  AddressRecord* operator-- (int) {return decr();}

  AddressRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  AddressRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  AddsIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

