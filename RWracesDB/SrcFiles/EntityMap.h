// Entity Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


struct EntityRecord : public MapRecord {
long   EntityID;
String FirstName;
String MiddleInitial;
String LastName;
String Suffix;
long   AddrID;
long   CityStID;
bool   AddrIsPO;
String LocationZip;
String eMail;
String Phone1;
String Phone2;

  EntityRecord() : EntityID(0), FirstName(), MiddleInitial(), LastName(), Suffix(),
           AddrID(0), CityStID(0), AddrIsPO(), LocationZip(), eMail(),
           Phone1(), Phone2() {}
  EntityRecord(const EntityRecord& r) : MapRecord(r), EntityID(r.EntityID),
           FirstName(r.FirstName), MiddleInitial(r.MiddleInitial), LastName(r.LastName),
           Suffix(r.Suffix), AddrID(r.AddrID), CityStID(r.CityStID),
           AddrIsPO(r.AddrIsPO), LocationZip(r.LocationZip), eMail(r.eMail),
           Phone1(r.Phone1), Phone2(r.Phone2) {}
 ~EntityRecord() {}

  EntityRecord operator= (EntityRecord& r) {
    copy(r, *this); EntityID = r.EntityID; FirstName = r.FirstName;
    MiddleInitial = r.MiddleInitial; LastName = r.LastName; Suffix = r.Suffix;
    AddrID = r.AddrID; CityStID = r.CityStID; AddrIsPO = r.AddrIsPO;
    LocationZip = r.LocationZip; eMail = r.eMail; Phone1 = r.Phone1;
    Phone2 = r.Phone2;
    }

  String getFldVal(int i);
  };


class EntityTable;


class EntityDB {
AceRecordSet rcdSet;
public:

  EntityDB() : rcdSet() {}
 ~EntityDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, EntityTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(EntityTable& myTable);

private:

  bool wrt(EntityRecord& src);
  bool erase(long key);
  };


class EntityTable : public MapTable {

typedef map<const long, EntityRecord> MyMap;

static MyMap myMap;
long         maxKey;
EntityDB     myDB;

public:

  EntityTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Entity"));
    }

  bool add(EntityRecord& rcd);

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

  friend class EntyIter;
  };


class EntyIter {

typedef EntityTable::MyMap MyMap;
typedef MyMap::iterator    MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  EntyIter(EntityTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  EntityRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  EntityRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  EntityRecord* operator-- (int) {return decr();}

  EntityRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  EntityRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  EntyIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

