// Backup CSV Records


#pragma once
#include "CSVRcdB.h"
#include "CSVRcdsT.h"




class BackupRcd : public CSVRcdB {
public:
String badgeNumber;
String mbrFirstName;
String mbrMiddleInitial;
String mbrLastName;
String mbrSuffix;
String mbrStreet;
String mbrAptSuite;
String mbrCity;
String mbrState;
String mbrZip;
String mbrAddrIsPO;
String mbrLocationZip;
String mbrEmail;
String mbrPhone;
String mbrCell;
String txtDevPrim;
String txtDevSec;
String callSign;
String fccExpiration;
String startDate;
String dswDate;
String badgeExpDate;
String responder;
String SecondaryEmail;
String emplFirstName;
String emplMiddleInitial;
String emplLastName;
String emplSuffix;
String emplStreet;
String emplAptSuite;
String emplCity;
String emplState;
String emplZip;
bool   emplAddrIsPO;
String emplLocationZip;
String emplEmail;
String emplPhone;
String emplCell;
String iceFirstName;
String iceMiddleInitial;
String iceLastName;
String iceSuffix;
String iceStreet;
String iceAptSuite;
String iceCity;
String iceState;
String iceZip;
bool   iceAddrIsPO;
String iceLocationZip;
String iceEmail;
String icePhone;
String iceCell;
String Handheld;
String portMobile;
String portPacket;
String otherEquip;
String multilingual;
String otherCapabilities;
String limitations;
String AssgnPrefKey;
String AssgnPrefDsc;
String LocationPrefKey;
String LocationPref;
String comments;
String shirtSize;
bool   isOfficer;
String StatusAbr;
String StatusDsc;
String skillCertifications;
String eoc_Certifications;
String updateDate;
bool   badgeOK;
String Cell_2;
bool   SMS_1;
bool   SMS_2;

  BackupRcd() {clear();}

  virtual BackupRcd& operator= (BackupRcd& r) {copy(r); return *this;}

protected:

  virtual void    put(TCchar* p);

  virtual void    copy(BackupRcd& r);
  };




typedef RcdPtrT<BackupRcd> BackupRcdP;

typedef CSVRcdsT<BackupRcd, BackupRcdP> BackupRcds;
typedef CSVIterT<BackupRcd, BackupRcdP> BkpIter;

extern BackupRcds backupRcds;

