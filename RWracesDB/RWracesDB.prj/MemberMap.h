// Member Map logic, Version 1.5.15.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapBase.h"


struct MemberRecord : public MapRecord {
long   MemberID;
long   BadgeNumber;
long   MbrEntityID;
long   EmplEntityID;
long   ICE_EntityID;
long   AssgnPrefID;
long   LocationPrefID;
long   StatusID;
String CallSign;
String FCCExpiration;
String StartDate;
String DSWDate;
String BadgeExpDate;
String Responder;
String SecondaryEmail;
String TextMsgPh1;
String TextMsgPh2;
String HandHeld;
String PortMobile;
String PortPacket;
String OtherEquip;
String Multilingual;
String OtherCapabilities;
String Limitations;
String Comments;
String ShirtSize;
bool   IsOfficer;
String SkillCertifications;
String EOC_Certifications;
String UpdateDate;
bool   BadgeOK;
String Image;

  MemberRecord() : MemberID(0), BadgeNumber(0), MbrEntityID(0), EmplEntityID(0),
                   ICE_EntityID(0), AssgnPrefID(0), LocationPrefID(0), StatusID(0), CallSign(),
                   FCCExpiration(), StartDate(), DSWDate(), BadgeExpDate(), Responder(), SecondaryEmail(),
                   TextMsgPh1(), TextMsgPh2(), HandHeld(), PortMobile(), PortPacket(), OtherEquip(),
                   Multilingual(), OtherCapabilities(), Limitations(), Comments(), ShirtSize(),
                   IsOfficer(), SkillCertifications(), EOC_Certifications(), UpdateDate(), BadgeOK(),
                   Image() {}
  MemberRecord(const MemberRecord& r) {copy(r);}
 ~MemberRecord() {}

  MemberRecord& operator= (const MemberRecord& r) {copy(r); return *this;}

  String getFldVal(int i);

private:

  void copy(const MemberRecord& r);
  };


class MemberMap;


class MemberDB {
AceRecordSet rcdSet;
protected:

  MemberDB() : rcdSet() {}
 ~MemberDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TblDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, MemberMap& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(MemberMap& myTable);

private:

  bool wrt(MemberRecord& src);
  bool remove(long key);

  friend class MemberMap;
  };


class MemberMap : public MapBase {

typedef map<const long, MemberRecord> MyMap;

static MyMap myMap;
MemberDB     myDB;

protected:

  MemberMap() {initialize();}

  void initialize() {
    if (!myMap.empty()) myMap.clear();
    MapBase::initialize(_T("Member"));
    }

  bool add(MemberRecord& rcd);

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

  friend class MmbrIter;
  friend class MemberDB;
  };

