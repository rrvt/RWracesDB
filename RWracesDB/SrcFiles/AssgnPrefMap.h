// AssgnPref Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct AssgnPrefRecord : public MapRecord {
long   AssgnPrefID;
String APKey;
String Txt;

  AssgnPrefRecord() : AssgnPrefID(0), APKey(), Txt() {}
  AssgnPrefRecord(const AssgnPrefRecord& r) : MapRecord(r), AssgnPrefID(r.AssgnPrefID),
           APKey(r.APKey), Txt(r.Txt) {}
 ~AssgnPrefRecord() {}

  AssgnPrefRecord operator= (AssgnPrefRecord& r) {
    copy(r, *this); AssgnPrefID = r.AssgnPrefID; APKey = r.APKey;
    Txt = r.Txt;
    }

  String getFldVal(int i);
  };


class AssgnPrefTable;


class AssgnPrefDB {
AceRecordSet rcdSet;
public:

  AssgnPrefDB() : rcdSet() {}
 ~AssgnPrefDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, AssgnPrefTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(AssgnPrefTable& myTable);

private:

  bool wrt(AssgnPrefRecord& src);
  bool erase(long key);
  };


class AssgnPrefTable : public MapTable {

typedef map<const long, AssgnPrefRecord> MyMap;

static MyMap myMap;
long         maxKey;
AssgnPrefDB  myDB;

public:

  AssgnPrefTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("AssgnPref"));
    }

  bool add(AssgnPrefRecord& rcd);

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

  friend class AgPfIter;
  };


class AgPfIter {

typedef AssgnPrefTable::MyMap MyMap;
typedef MyMap::iterator       MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  AgPfIter(AssgnPrefTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  AssgnPrefRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  AssgnPrefRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  AssgnPrefRecord* operator-- (int) {return decr();}

  AssgnPrefRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  AssgnPrefRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  AgPfIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

