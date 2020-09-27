// Status Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct StatusRecord : public MapRecord {
long   StsID;
String Abbreviation;
String Description;

  StatusRecord() : StsID(0), Abbreviation(), Description() {}
  StatusRecord(const StatusRecord& r) : MapRecord(r), StsID(r.StsID),
           Abbreviation(r.Abbreviation), Description(r.Description) {}
 ~StatusRecord() {}

  StatusRecord operator= (StatusRecord& r) {
    copy(r, *this); StsID = r.StsID; Abbreviation = r.Abbreviation;
    Description = r.Description;
    }

  String getFldVal(int i);
  };


class StatusTable;


class StatusDB {
AceRecordSet rcdSet;
public:

  StatusDB() : rcdSet() {}
 ~StatusDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, StatusTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(StatusTable& myTable);

private:

  bool wrt(StatusRecord& src);
  bool erase(long key);
  };


class StatusTable : public MapTable {

typedef map<const long, StatusRecord> MyMap;

static MyMap myMap;
long         maxKey;
StatusDB     myDB;

public:

  StatusTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Status"));
    }

  bool add(StatusRecord& rcd);

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

  friend class SttsIter;
  };


class SttsIter {

typedef StatusTable::MyMap MyMap;
typedef MyMap::iterator    MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  SttsIter(StatusTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  StatusRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  StatusRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  StatusRecord* operator-- (int) {return decr();}

  StatusRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  StatusRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  SttsIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

