// Member Map logic, Version 1.5.7.0
// Copyright Bob -- K6RWY, 2019.  All rights reserved.

#pragma once
#include "AceDao.h"
#include "MapTable.h"


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

  MemberRecord() : MemberID(0), BadgeNumber(0), MbrEntityID(0), EmplEntityID(0), ICE_EntityID(0),
           AssgnPrefID(0), LocationPrefID(0), StatusID(0), CallSign(), FCCExpiration(),
           StartDate(), DSWDate(), BadgeExpDate(), Responder(), SecondaryEmail(),
           TextMsgPh1(), TextMsgPh2(), HandHeld(), PortMobile(), PortPacket(),
           OtherEquip(), Multilingual(), OtherCapabilities(), Limitations(), Comments(),
           ShirtSize(), IsOfficer(), SkillCertifications(), EOC_Certifications(), UpdateDate(),
           BadgeOK(), Image() {}
  MemberRecord(const MemberRecord& r) : MapRecord(r), MemberID(r.MemberID),
           BadgeNumber(r.BadgeNumber), MbrEntityID(r.MbrEntityID), EmplEntityID(r.EmplEntityID),
           ICE_EntityID(r.ICE_EntityID), AssgnPrefID(r.AssgnPrefID), LocationPrefID(r.LocationPrefID),
           StatusID(r.StatusID), CallSign(r.CallSign), FCCExpiration(r.FCCExpiration),
           StartDate(r.StartDate), DSWDate(r.DSWDate), BadgeExpDate(r.BadgeExpDate),
           Responder(r.Responder), SecondaryEmail(r.SecondaryEmail), TextMsgPh1(r.TextMsgPh1),
           TextMsgPh2(r.TextMsgPh2), HandHeld(r.HandHeld), PortMobile(r.PortMobile),
           PortPacket(r.PortPacket), OtherEquip(r.OtherEquip), Multilingual(r.Multilingual),
           OtherCapabilities(r.OtherCapabilities), Limitations(r.Limitations), Comments(r.Comments),
           ShirtSize(r.ShirtSize), IsOfficer(r.IsOfficer), SkillCertifications(r.SkillCertifications),
           EOC_Certifications(r.EOC_Certifications), UpdateDate(r.UpdateDate), BadgeOK(r.BadgeOK),
           Image(r.Image) {}
 ~MemberRecord() {}

  MemberRecord operator= (MemberRecord& r) {
    copy(r, *this); MemberID = r.MemberID; BadgeNumber = r.BadgeNumber;
    MbrEntityID = r.MbrEntityID; EmplEntityID = r.EmplEntityID; ICE_EntityID = r.ICE_EntityID;
    AssgnPrefID = r.AssgnPrefID; LocationPrefID = r.LocationPrefID; StatusID = r.StatusID;
    CallSign = r.CallSign; FCCExpiration = r.FCCExpiration; StartDate = r.StartDate;
    DSWDate = r.DSWDate; BadgeExpDate = r.BadgeExpDate; Responder = r.Responder;
    SecondaryEmail = r.SecondaryEmail; TextMsgPh1 = r.TextMsgPh1; TextMsgPh2 = r.TextMsgPh2;
    HandHeld = r.HandHeld; PortMobile = r.PortMobile; PortPacket = r.PortPacket;
    OtherEquip = r.OtherEquip; Multilingual = r.Multilingual; OtherCapabilities = r.OtherCapabilities;
    Limitations = r.Limitations; Comments = r.Comments; ShirtSize = r.ShirtSize;
    IsOfficer = r.IsOfficer; SkillCertifications = r.SkillCertifications; EOC_Certifications = r.EOC_Certifications;
    UpdateDate = r.UpdateDate; BadgeOK = r.BadgeOK; Image = r.Image;
    }

  String getFldVal(int i);
  };


class MemberTable;


class MemberDB {
AceRecordSet rcdSet;
public:

  MemberDB() : rcdSet() {}
 ~MemberDB() {}

  // toTable copies all records from a database table into a map container in memory.  It is
  // called from MapsT<MapData>::loadRecords(TableDsc* tableDsc) which is in turn
  // called from MapsT<MapData>::loadAllMaps(String& path).  Essentially there is a table
  // with all the database tables and all the tables are copied into a corresponding map table.
  // The tables are implemented as trees for fast access and other properties (see std::map)

  bool toTable(AceRecordSet& records, MemberTable& myTable);

  // After all changes have been made in the map, call toDatabase to copy the changes
  // back to the database.

  bool toDatabase(MemberTable& myTable);

private:

  bool wrt(MemberRecord& src);
  bool erase(long key);
  };


class MemberTable : public MapTable {

typedef map<const long, MemberRecord> MyMap;

static MyMap myMap;
long         maxKey;
MemberDB     myDB;

public:

  MemberTable() {initialize();}

  void initialize() {
    maxKey = 0;   if (!myMap.empty()) myMap.clear();
    MapTable::initialize(_T("Member"));
    }

  bool add(MemberRecord& rcd);

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

  friend class MmbrIter;
  };


class MmbrIter {

typedef MemberTable::MyMap MyMap;
typedef MyMap::iterator    MyIter;

MyMap& myMap;
MyIter iter;

public:

typedef pair<MyIter, bool> Pair;

  MmbrIter(MemberTable& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  MemberRecord* operator() (bool fwd = true) {
    if (fwd) {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    else     {iter = myMap.end();   return decr();}
    }

  MemberRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  MemberRecord* operator-- (int) {return decr();}

  MemberRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  void erase() {iter = myMap.erase(iter);}

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isBbegin() {return iter == myMap.begin();}

private:

  MemberRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  MmbrIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator
  };

