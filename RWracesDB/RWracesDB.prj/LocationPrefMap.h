// LocationPref Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct LocationPrefRecord : public MapRecord {
long   LocationPrefID;
String Key;
String Txt;

  LocationPrefRecord() : LocationPrefID(0), Key(), Txt() {}
  LocationPrefRecord(const LocationPrefRecord& r) : MapRecord(r), LocationPrefID(r.LocationPrefID),
           Key(r.Key), Txt(r.Txt) {}
 ~LocationPrefRecord() {}

  LocationPrefRecord operator= (LocationPrefRecord& r) {
    copy(r, *this); LocationPrefID = r.LocationPrefID; Key = r.Key;
    Txt = r.Txt;
    }

  String getFldVal(int i);
  };


class LocationPrefTable;


class LocationPrefDB {
AceRecordSet rcdSet;
public:

  LocationPrefDB() : rcdSet() {}
 ~LocationPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, LocationPrefTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(LocationPrefTable& myTable);

private:

  bool wrt(LocationPrefRecord& src);
  bool erase(long key);
  };


class LocationPrefTable : public MapTable {

typedef map<const long, LocationPrefRecord> MyMap;

static MyMap   myMap;
long           maxKey;
LocationPrefDB myDB;

public:

  LocationPrefTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("LocationPref"));
    }

  bool add(LocationPrefRecord& rcd);

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

  friend class LcPfIter;
  };


class LcPfIter {

typedef LocationPrefTable::MyMap MyMap;
typedef MyMap::iterator          MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  LcPfIter(LocationPrefTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  LocationPrefRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  LocationPrefRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  LocationPrefRecord* operator-- (int) {return decr();}

  LocationPrefRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  LocationPrefRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  LcPfIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

