// Entity Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


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
                   AddrID(0), CityStID(0), AddrIsPO(), LocationZip(), eMail(), Phone1(), Phone2() {}
  EntityRecord(const EntityRecord& r) {copy(r);}
 ~EntityRecord() {}

  EntityRecord& operator= (const EntityRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const EntityRecord& r);
  };


class EntityMap;


class EntityDB {
AceRecordSet rcdSet;
protected:

  EntityDB() : rcdSet() {}
 ~EntityDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, EntityMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(EntityMap& myTable);

private:

  bool wrt(EntityRecord& src);
  bool remove(long key);

  friend class EntityMap;
  };


class EntityMap : public MapBase {

typedef map<const long, EntityRecord> MyMap;

static MyMap myMap;
EntityDB     myDB;

protected:

  EntityMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("Entity"));
    }

  bool add(EntityRecord& rcd);

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

  friend class EntyIter;
  friend class EntityDB;
  };

