// CityState Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct CityStateRecord : public MapRecord {
long   CityStateID;
String City;
String State;
String Zip;

  CityStateRecord() : CityStateID(0), City(), State(), Zip() {}
  CityStateRecord(const CityStateRecord& r) : MapRecord(r), CityStateID(r.CityStateID),
           City(r.City), State(r.State), Zip(r.Zip) {}
 ~CityStateRecord() {}

  CityStateRecord operator= (CityStateRecord& r) {
    copy(r, *this); CityStateID = r.CityStateID; City = r.City;
    State = r.State; Zip = r.Zip;
    }

  String getFldVal(int i);
  };


class CityStateTable;


class CityStateDB {
AceRecordSet rcdSet;
public:

  CityStateDB() : rcdSet() {}
 ~CityStateDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, CityStateTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(CityStateTable& myTable);

private:

  bool wrt(CityStateRecord& src);
  bool erase(long key);
  };


class CityStateTable : public MapTable {

typedef map<const long, CityStateRecord> MyMap;

static MyMap myMap;
long         maxKey;
CityStateDB  myDB;

public:

  CityStateTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("CityState"));
    }

  bool add(CityStateRecord& rcd);

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

  friend class CtySIter;
  };


class CtySIter {

typedef CityStateTable::MyMap MyMap;
typedef MyMap::iterator       MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  CtySIter(CityStateTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  CityStateRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  CityStateRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  CityStateRecord* operator-- (int) {return decr();}

  CityStateRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  CityStateRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  CtySIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

