// Backup CSV Records


#pragma once
#include "CSVRcdB.h"
#include "CSVRcdsT.h"




class BackupRcd : public CSVRcdB {
public:
String BadgeNumber;
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
String CallSign;
String FCCExpiration;
String StartDate;
String DSWDate;
String BadgeExpDate;
String Responder;
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
String PortMobile;
String PortPacket;
String OtherEquip;
String Multilingual;
String OtherCapabilities;
String Limitations;
String AssgnPrefKey;
String AssgnPrefDsc;
String LocationPrefKey;
String LocationPref;
String Comments;
String ShirtSize;
bool   IsOfficer;
String StatusAbr;
String StatusDsc;
String SkillCertifications;
String EOC_Certifications;
String UpdateDate;
bool   BadgeOK;
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

