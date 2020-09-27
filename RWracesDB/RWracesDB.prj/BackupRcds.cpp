// Backup CSV Records


#include "stdafx.h"
#include "BackupRcds.h"


BackupRcds backupRcds;


void BackupRcd::put(TCchar* p) {
String s = p;

  switch (putI) {
    case  0 : BadgeNumber         = s;        break;
    case  1 : mbrFirstName        = s;        break;
    case  2 : mbrMiddleInitial    = s;        break;
    case  3 : mbrLastName         = s;        break;
    case  4 : mbrSuffix           = s;        break;
    case  5 : mbrStreet           = s;        break;
    case  6 : mbrAptSuite         = s;        break;
    case  7 : mbrCity             = s;        break;
    case  8 : mbrState            = s;        break;
    case  9 : mbrZip              = s;        break;
    case 10 : mbrAddrIsPO         = s;        break;
    case 11 : mbrLocationZip      = s;        break;
    case 12 : mbrEmail            = s;        break;
    case 13 : SecondaryEmail      = s;        break;
    case 14 : mbrPhone            = s;        break;
    case 15 : mbrCell             = s;        break;
    case 16 : txtDevPrim          = s;        break;
    case 17 : txtDevSec           = s;        break;
    case 18 : CallSign            = s;        break;
    case 19 : FCCExpiration       = s;        break;
    case 20 : StartDate           = s;        break;
    case 21 : DSWDate             = s;        break;
    case 22 : BadgeExpDate        = s;        break;
    case 23 : Responder           = s;        break;
    case 24 : emplFirstName       = s;        break;
    case 25 : emplMiddleInitial   = s;        break;
    case 26 : emplLastName        = s;        break;
    case 27 : emplSuffix          = s;        break;
    case 28 : emplStreet          = s;        break;
    case 29 : emplAptSuite        = s;        break;
    case 30 : emplCity            = s;        break;
    case 31 : emplState           = s;        break;
    case 32 : emplZip             = s;        break;
    case 33 : emplAddrIsPO        = s == "1"; break;
    case 34 : emplLocationZip     = s;        break;
    case 35 : emplEmail           = s;        break;
    case 36 : emplPhone           = s;        break;
    case 37 : emplCell            = s;        break;
    case 38 : iceFirstName        = s;        break;
    case 39 : iceMiddleInitial    = s;        break;
    case 40 : iceLastName         = s;        break;
    case 41 : iceSuffix           = s;        break;
    case 42 : iceStreet           = s;        break;
    case 43 : iceAptSuite         = s;        break;
    case 44 : iceCity             = s;        break;
    case 45 : iceState            = s;        break;
    case 46 : iceZip              = s;        break;
    case 47 : iceAddrIsPO         = s == "1"; break;
    case 48 : iceLocationZip      = s;        break;
    case 49 : iceEmail            = s;        break;
    case 50 : icePhone            = s;        break;
    case 51 : iceCell             = s;        break;
    case 52 : Handheld            = s;        break;
    case 53 : PortMobile          = s;        break;
    case 54 : PortPacket          = s;        break;
    case 55 : OtherEquip          = s;        break;
    case 56 : Multilingual        = s;        break;
    case 57 : OtherCapabilities   = s;        break;
    case 58 : Limitations         = s;        break;
    case 59 : AssgnPrefKey        = s;        break;
    case 60 : AssgnPrefDsc        = s;        break;
    case 61 : LocationPrefKey     = s;        break;
    case 62 : LocationPref        = s;        break;
    case 63 : Comments            = s;        break;
    case 64 : ShirtSize           = s;        break;
    case 65 : IsOfficer           = s == "1"; break;
    case 66 : StatusAbr           = s;        break;
    case 67 : StatusDsc           = s;        break;
    case 68 : SkillCertifications = s;        break;
    case 69 : EOC_Certifications  = s;        break;
    case 70 : UpdateDate          = s;        break;
    case 71 : BadgeOK             = s == "1"; break;
    }
  }


void BackupRcd::copy(BackupRcd& r) {
  BadgeNumber           = r.BadgeNumber;
  mbrFirstName          = r.mbrFirstName;
  mbrMiddleInitial      = r.mbrMiddleInitial;
  mbrLastName           = r.mbrLastName;
  mbrSuffix             = r.mbrSuffix;
  mbrStreet             = r.mbrStreet;
  mbrAptSuite           = r.mbrAptSuite;
  mbrCity               = r.mbrCity;
  mbrState              = r.mbrState;
  mbrZip                = r.mbrZip;
  mbrAddrIsPO           = r.mbrAddrIsPO;
  mbrLocationZip        = r.mbrLocationZip;
  mbrEmail              = r.mbrEmail;
  mbrPhone              = r.mbrPhone;
  mbrCell               = r.mbrCell;
  txtDevPrim            = r.txtDevPrim;
  txtDevSec             = r.txtDevSec;
  CallSign              = r.CallSign;
  FCCExpiration         = r.FCCExpiration;
  StartDate             = r.StartDate;
  DSWDate               = r.DSWDate;
  BadgeExpDate          = r.BadgeExpDate;
  Responder             = r.Responder;
  SecondaryEmail        = r.SecondaryEmail;
  emplFirstName         = r.emplFirstName;
  emplMiddleInitial     = r.emplMiddleInitial;
  emplLastName          = r.emplLastName;
  emplSuffix            = r.emplSuffix;
  emplStreet            = r.emplStreet;
  emplAptSuite          = r.emplAptSuite;
  emplCity              = r.emplCity;
  emplState             = r.emplState;
  emplZip               = r.emplZip;
  emplAddrIsPO          = r.emplAddrIsPO;
  emplLocationZip       = r.emplLocationZip;
  emplEmail             = r.emplEmail;
  emplPhone             = r.emplPhone;
  emplCell              = r.emplCell;
  iceFirstName          = r.iceFirstName;
  iceMiddleInitial      = r.iceMiddleInitial;
  iceLastName           = r.iceLastName;
  iceSuffix             = r.iceSuffix;
  iceStreet             = r.iceStreet;
  iceAptSuite           = r.iceAptSuite;
  iceCity               = r.iceCity;
  iceState              = r.iceState;
  iceZip                = r.iceZip;
  iceAddrIsPO           = r.iceAddrIsPO;
  iceLocationZip        = r.iceLocationZip;
  iceEmail              = r.iceEmail;
  icePhone              = r.icePhone;
  iceCell               = r.iceCell;
  Handheld              = r.Handheld;
  PortMobile            = r.PortMobile;
  PortPacket            = r.PortPacket;
  OtherEquip            = r.OtherEquip;
  Multilingual          = r.Multilingual;
  OtherCapabilities     = r.OtherCapabilities;
  Limitations           = r.Limitations;
  AssgnPrefKey          = r.AssgnPrefKey;
  AssgnPrefDsc          = r.AssgnPrefDsc;
  LocationPrefKey       = r.LocationPrefKey;
  LocationPref          = r.LocationPref;
  Comments              = r.Comments;
  ShirtSize             = r.ShirtSize;
  IsOfficer             = r.IsOfficer;
  StatusAbr             = r.StatusAbr;
  StatusDsc             = r.StatusDsc;
  SkillCertifications   = r.SkillCertifications;
  EOC_Certifications    = r.EOC_Certifications;
  UpdateDate            = r.UpdateDate;
  BadgeOK               = r.BadgeOK;
  Cell_2                = r.Cell_2;
  SMS_1                 = r.SMS_1;
  SMS_2                 = r.SMS_2;
  CSVRcdB::copy(r);
  }
