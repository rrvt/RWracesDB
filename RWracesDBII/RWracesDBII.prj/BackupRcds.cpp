// Backup CSV Records


#include "stdafx.h"
#include "BackupRcds.h"


BackupRcds backupRcds;


void BackupRcd::put(TCchar* p) {
String s = p;

  switch (putI) {
    case  0 : badgeNumber         = s;        break;
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
    case 18 : callSign            = s;        break;
    case 19 : fccExpiration       = s;        break;
    case 20 : startDate           = s;        break;
    case 21 : dswDate             = s;        break;
    case 22 : badgeExpDate        = s;        break;
    case 23 : responder           = s;        break;
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
    case 53 : portMobile          = s;        break;
    case 54 : portPacket          = s;        break;
    case 55 : otherEquip          = s;        break;
    case 56 : multilingual        = s;        break;
    case 57 : otherCapabilities   = s;        break;
    case 58 : limitations         = s;        break;
    case 59 : AssgnPrefKey        = s;        break;
    case 60 : AssgnPrefDsc        = s;        break;
    case 61 : LocationPrefKey     = s;        break;
    case 62 : LocationPref        = s;        break;
    case 63 : comments            = s;        break;
    case 64 : shirtSize           = s;        break;
    case 65 : isOfficer           = s == "1"; break;
    case 66 : StatusAbr           = s;        break;
    case 67 : StatusDsc           = s;        break;
    case 68 : skillCertifications = s;        break;
    case 69 : eoc_Certifications  = s;        break;
    case 70 : updateDate          = s;        break;
    case 71 : badgeOK             = s == "1"; break;
    }
  }


void BackupRcd::copy(BackupRcd& r) {
  badgeNumber           = r.badgeNumber;
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
  callSign              = r.callSign;
  fccExpiration         = r.fccExpiration;
  startDate             = r.startDate;
  dswDate               = r.dswDate;
  badgeExpDate          = r.badgeExpDate;
  responder             = r.responder;
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
  portMobile            = r.portMobile;
  portPacket            = r.portPacket;
  otherEquip            = r.otherEquip;
  multilingual          = r.multilingual;
  otherCapabilities     = r.otherCapabilities;
  limitations           = r.limitations;
  AssgnPrefKey          = r.AssgnPrefKey;
  AssgnPrefDsc          = r.AssgnPrefDsc;
  LocationPrefKey       = r.LocationPrefKey;
  LocationPref          = r.LocationPref;
  comments              = r.comments;
  shirtSize             = r.shirtSize;
  isOfficer             = r.isOfficer;
  StatusAbr             = r.StatusAbr;
  StatusDsc             = r.StatusDsc;
  skillCertifications   = r.skillCertifications;
  eoc_Certifications    = r.eoc_Certifications;
  updateDate            = r.updateDate;
  badgeOK               = r.badgeOK;
  Cell_2                = r.Cell_2;
  SMS_1                 = r.SMS_1;
  SMS_2                 = r.SMS_2;
  CSVRcdB::copy(r);
  }
