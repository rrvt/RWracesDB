// Database Restoration


#include "stdafx.h"
#include "DataBase.h"
#include "AddressTbl.h"
#include "Archive.h"
#include "AssgnPrefTbl.h"
#include "BackupRcds.h"
#include "CityStateTbl.h"
#include "EntityTbl.h"
#include "GetPathDlg.h"
#include "LocationPrefTbl.h"
#include "MemberTbl.h"
#include "RWutilities.h"
#include "StatusTbl.h"



struct Status {
TCchar* key;
TCchar* desc;
};


static void FixedInit(Status sts[], int n, DBtable& tbl);


static Status locPref[5]    = {{_T("A"), _T("Available to be dispatched anywhere needed")},
                               {_T("5"), _T("Available to be dispatched within 5 miles of location")},
                               {_T("1"), _T("Available to be dispatched within 1 mile of location")},
                               {_T("N"), _T("Available to accept assignments in neighborhood")},
                               {_T("O"), _T("Not available for RACES dispatch.")}
                               };

static Status statusList[3] = {{_T("Act"), _T("Member is Active")},
                               {_T("InA"), _T("Member is deemed inactive but still a member")},
                               {_T("Fmr"), _T("Member is a former member and not active")}
                               };

static Status asnPref[6] = {
                        {_T("P"), _T("RACES is first call, ready to be dispatched immediately")},
                        {_T("E"), _T("RACES is second call, ready to be dispatched immediately")},
                        {_T("G"), _T("Will probably respond, may take some time to assemble equipment")},
                        {_T("A"), _T("ARES only")},
                        {_T("L"), _T("Last resort resource")},
                        {_T("O"), _T("Pending regained health")}
                        };


void DataBase::restore() {
String     path;
BkpIter    iter(backupRcds);
BackupRcd* csv;
int        i;

  initDefaultBadgeNo();

  FixedInit(statusList, noElements(statusList), statusTbl);
  FixedInit(locPref,    noElements(locPref),    locationPrefTbl);
  FixedInit(asnPref,    noElements(asnPref),    assgnPrefTbl);

  csv = iter();   if (csv && csv->callSign == _T("CallSign")) csv = iter++;

  for (i = 0; csv; i++, csv = iter++) {
    if (!rstrRcd(*csv)) {
      notePad << _T("Unable to upload: ") << csv->mbrFirstName << _T(" ") << csv->mbrLastName << _T(" ");
      notePad << csv->callSign << nCrlf;
      }
    }

  memberTbl.store();   entityTbl.store();
  }


void FixedInit(Status sts[], int n, DBtable& tbl) {
int i;

  for (i = 0; i < n; i++) {
    Status& itm = sts[i];

      tbl.add(itm.key, itm.desc);
    }
  }


void DataBase::load(Archive& ar) {backupRcds.load(ar);}


bool DataBase::rstrRcd(BackupRcd& csv) {
MemberRcd* mbr     = rstrMbr(csv);     if (!mbr) return false;
EntityRcd* mbrEnt  = rstrMbrEnt(csv);
EntityRcd* emplEnt = rstrEmpEnt(csv);
EntityRcd* iceEnt  = rstrICEent(csv);

  if (isEmpty(&csv.mbrLastName, &csv.mbrFirstName, &csv.callSign, 0)) return false;

  if (mbrEnt)  mbr->mbrEntityID  = mbrEnt->id;
  if (emplEnt) mbr->emplEntityID = emplEnt->id;
  if (iceEnt)  mbr->ice_EntityID = iceEnt->id;

  mbr->mark();   return true;
  }


MemberRcd* DataBase::rstrMbr(BackupRcd& csv) {
MemberRcd* mbr = 0;

  mbr = memberTbl.find(csv.callSign);
  if (!mbr) {MemberRcd rcd;  rcd.callSign = csv.callSign;  mbr = memberTbl.add(rcd);}

  mbr->badgeNumber         = sanitizeBadgeNo(csv.badgeNumber);
  mbr->fccExpiration       = sanitizeDate(csv.fccExpiration);
  mbr->startDate           = sanitizeDate(csv.startDate);
  mbr->dswDate             = sanitizeDate(csv.dswDate);
  mbr->badgeExpDate        = sanitizeDate(csv.badgeExpDate);
  mbr->responder           = sanitizeDate(csv.responder);
  mbr->secondaryEmail      = csv.SecondaryEmail;
  mbr->textMsgPh1          = csv.txtDevPrim;
  mbr->textMsgPh2          = csv.txtDevSec;
  mbr->handHeld            = quoted.remDbl(csv.Handheld);
  mbr->portMobile          = quoted.remDbl(csv.portMobile);
  mbr->portPacket          = quoted.remDbl(csv.portPacket);
  mbr->otherEquip          = quoted.remDbl(csv.otherEquip);
  mbr->multilingual        = quoted.remDbl(csv.multilingual);
  mbr->otherCapabilities   = quoted.remDbl(csv.otherCapabilities);
  mbr->limitations         = quoted.remDbl(csv.limitations);
  mbr->comments            = quoted.remDbl(csv.comments);
  mbr->shirtSize           = csv.shirtSize;
  mbr->skillCertifications = csv.skillCertifications;
  mbr->eoc_Certifications  = csv.eoc_Certifications;
  mbr->updateDate          = csv.updateDate;

  mbr->assgnPrefID         = assgnPrefTbl.add(csv.AssgnPrefKey, csv.AssgnPrefDsc)->id;

  mbr->locationPrefID      = locationPrefTbl.add(csv.LocationPrefKey, csv.LocationPref)->id;
  mbr->isOfficer           = csv.isOfficer;
  mbr->statusID            = statusTbl.add(csv.StatusAbr, csv.StatusDsc)->id;
  mbr->badgeOK             = csv.badgeOK;

  return mbr;
  }


EntityRcd* DataBase::rstrMbrEnt(BackupRcd& csv) {
EntityRcd*    entRcd  = 0;
AddressRcd*   adrRcd  = 0;
CityStateRcd* ctyRcd  = 0;

  entRcd = rstrEnt(csv.mbrFirstName, csv.mbrLastName, csv.mbrEmail, csv.mbrPhone, csv.mbrCell);
  if (!entRcd) return 0;
  rstrRest(entRcd, csv.mbrMiddleInitial, csv.mbrSuffix, csv.mbrAddrIsPO == "1", csv.mbrLocationZip);

  adrRcd = rstrAddr(sanitizeAddr(csv.mbrStreet), sanitizeAddr(csv.mbrAptSuite));
  if (adrRcd) entRcd->addrID = adrRcd->id;

  ctyRcd = rstrCitySt(csv.mbrCity, csv.mbrState, csv.mbrZip);
  if (ctyRcd) entRcd->cityStID = ctyRcd->id;

  return entRcd;
  }


EntityRcd* DataBase::rstrEmpEnt(BackupRcd& csv) {
EntityRcd*    entRcd = 0;
AddressRcd*   adrRcd = 0;
CityStateRcd* ctyRcd = 0;

  entRcd = rstrEnt(csv.emplFirstName, csv.emplLastName, csv.emplEmail, csv.emplPhone, csv.emplCell);
  if (!entRcd) return 0;
  rstrRest(entRcd, csv.emplMiddleInitial, csv.emplSuffix, csv.emplAddrIsPO, csv.emplLocationZip);

  adrRcd = rstrAddr(sanitizeAddr(csv.emplStreet), sanitizeAddr(csv.emplAptSuite));
  if (adrRcd) entRcd->addrID = adrRcd->id;

  ctyRcd = rstrCitySt(csv.emplCity, csv.emplState, csv.emplZip);
  if (ctyRcd) entRcd->cityStID = ctyRcd->id;

  return entRcd;
  }


EntityRcd* DataBase::rstrICEent(BackupRcd& csv) {
EntityRcd*    entRcd = 0;
AddressRcd*   adrRcd = 0;
CityStateRcd* ctyRcd = 0;

  entRcd = rstrEnt(csv.iceFirstName, csv.iceLastName, csv.iceEmail, csv.icePhone, csv.iceCell);
  if (!entRcd) return 0;
  rstrRest(entRcd, csv.iceMiddleInitial, csv.iceSuffix, csv.iceAddrIsPO, csv.iceLocationZip);

  adrRcd = rstrAddr(sanitizeAddr(csv.iceStreet), sanitizeAddr(csv.iceAptSuite));
  if (adrRcd) entRcd->addrID = adrRcd->id;

  ctyRcd = rstrCitySt(csv.iceCity, csv.iceState, csv.iceZip);
  if (ctyRcd) entRcd->cityStID = ctyRcd->id;

  return entRcd;
  }




EntityRcd* DataBase::rstrEnt(String& first, String& last, String& eMail, String& ph1, String& ph2) {
EntityRcd* r = entityTbl.find(first, last, eMail, ph1, ph2);   if (r) return r;

  EntityRcd rcd;
  rcd.firstName = first;
  rcd.lastName  = last;
  rcd.eMail     = eMail;
  rcd.phone1    = ph1;
  rcd.phone2    = ph2;

  return entityTbl.add(rcd);
  }


void DataBase::rstrRest(EntityRcd* rcd, String& midInit, String& suffix, bool isPO, String& locZip) {
  rcd->middleInitial = midInit;
  rcd->suffix        = suffix;
  rcd->addrIsPO      = isPO;
  rcd->locationZip   = locZip;
  rcd->mark();
  }


AddressRcd* DataBase::rstrAddr(String& addr1, String& addr2) {
AddressRcd* r = addressTbl.find(addr1, addr2);   if (r) return r;

  AddressRcd rcd;   rcd.address1 = addr1;   rcd.address2 = addr2;   return addressTbl.add(rcd);
  }


CityStateRcd* DataBase::rstrCitySt(String& city, String& state, String& zip) {
CityStateRcd* r = cityStateTbl.find(city, zip);    if (r) return r;

  CityStateRcd rcd;   rcd.city  = city;   rcd.state = state;   rcd.zip   = zip;

  return cityStateTbl.add(rcd);
  }


#if 0
  mbr = memberTbl.find(csv.callSign);
  if (!mbr) {MemberRcd rcd;  rcd.callSign = csv.callSign;  mbr = memberTbl.add(rcd);}

  mbr->badgeNumber         = sanitizeBadgeNo(csv.badgeNumber);
  mbr->fccExpiration       = sanitizeDate(csv.fccExpiration);
  mbr->startDate           = sanitizeDate(csv.startDate);
  mbr->dswDate             = sanitizeDate(csv.dswDate);
  mbr->badgeExpDate        = sanitizeDate(csv.BadgeExpDate);
  mbr->responder           = sanitizeDate(csv.responder);
  mbr->secondaryEmail      = csv.SecondaryEmail;
  mbr->textMsgPh1          = csv.txtDevPrim;
  mbr->textMsgPh2          = csv.txtDevSec;
  mbr->handHeld            = quoted.remDbl(csv.Handheld);
  mbr->portMobile          = quoted.remDbl(csv.portMobile);
  mbr->portPacket          = quoted.remDbl(csv.portPacket);
  mbr->otherEquip          = quoted.remDbl(csv.otherEquip);
  mbr->multilingual        = quoted.remDbl(csv.multilingual);
  mbr->otherCapabilities   = quoted.remDbl(csv.otherCapabilities);
  mbr->limitations         = quoted.remDbl(csv.limitations);
  mbr->comments            = quoted.remDbl(csv.comments);
  mbr->shirtSize           = csv.shirtSize;
  mbr->skillCertifications = csv.skillCertifications;
  mbr->eoc_Certifications  = csv.eoc_Certifications;
  mbr->updateDate          = csv.updateDate;

  mbr->assgnPrefID         = assgnPrefTbl.add(csv.AssgnPrefKey, csv.AssgnPrefDsc)->id;

  mbr->locationPrefID      = locationPrefTbl.add(csv.LocationPrefKey, csv.LocationPref)->id;
  mbr->isOfficer           = csv.isOfficer;
  mbr->statusID            = statusTbl.add(csv.StatusAbr, csv.StatusDsc)->id;
  mbr->badgeOK             = csv.badgeOK;
#endif


#if 0
  mbrEnt = entityTbl.find(csv.mbrFirstName, csv.mbrLastName, csv.mbrEmail, csv.mbrPhone, csv.mbrCell);

  if (!mbrEnt) {
    EntityRcd rcd;
    rcd.firstName = csv.mbrFirstName;
    rcd.lastName  = csv.mbrLastName;
    rcd.eMail     = csv.mbrEmail;
    rcd.phone1    = csv.mbrPhone;
    rcd.phone2    = csv.mbrCell;
    mbrEnt = entityTbl.add(rcd);
    }

  if (mbrEnt) {
    mbrEnt->middleInitial  = csv.mbrMiddleInitial;
    mbrEnt->suffix         = csv.mbrSuffix;
    mbrEnt->addrIsPO       = csv.mbrAddrIsPO == "1";
    mbrEnt->locationZip    = csv.mbrLocationZip;
    mbrEnt->mark();

    mbrAdr = addressTbl.get(sanitizeAddr(csv.mbrStreet), sanitizeAddr(csv.mbrAptSuite));
    if (mbrAdr) mbrEnt->addrID = mbrAdr->AddressID;

    mbrCty = cityStateTbl.get(csv.mbrCity , csv.mbrState, csv.mbrZip);
    if (mbrCty) mbrEnt->CityStID = mbrCty->CityStateID;

    mbr->mbrEntityID  = mbrEnt->EntityID;
    }
#endif


#if 0
  emplEnt = entityTbl.get(csv.emplFirstName, csv.emplLastName,
                                                             csv.emplEmail, csv.emplPhone, csv.emplCell);
  if (emplEnt) {
    emplEnt->middleInitial = csv.emplMiddleInitial;
    emplEnt->suffix        = csv.emplSuffix;
    emplEnt->AddrIsPO      = csv.emplAddrIsPO;
    emplEnt->LocationZip   = csv.emplLocationZip;
    emplEnt->mark();

    emplAdr             = addressTbl.get(sanitizeAddr(csv.emplStreet), sanitizeAddr(csv.emplAptSuite));
    if (emplAdr) emplEnt->addrID = emplAdr->AddressID;

    emplCty                = cityStateTbl.get(csv.emplCity, csv.emplState, csv.emplZip);
    if (emplCty) emplEnt->CityStID = emplCty->CityStateID;

    mbr->emplEntityID = emplEnt->EntityID;
    }
#endif
#if 0
  iceEnt = entityTbl.get(csv.iceFirstName, csv.iceLastName, csv.iceEmail, csv.icePhone, csv.iceCell);

  if (iceEnt) {
    iceEnt->middleInitial  = csv.iceMiddleInitial;
    iceEnt->suffix         = csv.iceSuffix;
    iceEnt->AddrIsPO       = csv.iceAddrIsPO;
    iceEnt->LocationZip    = csv.iceLocationZip;
    iceEnt->mark();

    iceAdr = addressTbl.get(sanitizeAddr(csv.iceStreet), sanitizeAddr(csv.iceAptSuite));
    if (iceAdr) iceEnt->addrID = iceAdr->AddressID;

    iceCty = cityStateTbl.get(csv.iceCity, csv.iceState, csv.iceZip);
    if (iceCty) iceEnt->CityStID = iceCty->CityStateID;

    mbr->ice_EntityID = iceEnt->EntityID;
    }
#endif
#if 0
  if (!entRcd) {
    EntityRcd rcd;
    rcd.firstName = csv.mbrFirstName;
    rcd.lastName  = csv.mbrLastName;
    rcd.eMail     = csv.mbrEmail;
    rcd.phone1    = csv.mbrPhone;
    rcd.phone2    = csv.mbrCell;
    entRcd = entityTbl.add(rcd);
    }

    entRcd->middleInitial  = csv.mbrMiddleInitial;
    entRcd->suffix         = csv.mbrSuffix;
    entRcd->addrIsPO       = csv.mbrAddrIsPO == "1";
    entRcd->locationZip    = csv.mbrLocationZip;
    entRcd->mark();
#endif
#if 0
  if (iceEnt) {
    iceEnt->middleInitial  = csv.iceMiddleInitial;
    iceEnt->suffix         = csv.iceSuffix;
    iceEnt->AddrIsPO       = csv.iceAddrIsPO;
    iceEnt->LocationZip    = csv.iceLocationZip;
    iceEnt->mark();
#endif
#if 0
  adrRcd = addressTbl.find(sanitizeAddr(csv.mbrStreet), sanitizeAddr(csv.mbrAptSuite));
  if (!adrRcd) {
    AddressRcd rcd;
    rcd.address1 = sanitizeAddr(csv.mbrStreet);
    rcd.address2 = sanitizeAddr(csv.mbrAptSuite);
    adrRcd = addressTbl.add(rcd);
    }
#endif
#if 0
  ctyRcd = cityStateTbl.find(csv.mbrCity, csv.mbrZip);        //csv.mbrState
  if (!ctyRcd) {
    CityStateRcd rcd;
    rcd.city  = csv.mbrCity;
    rcd.state = csv.mbrState;
    rcd.zip   = csv.mbrZip;
    ctyRcd  = cityStateTbl.add(rcd);
    }
#endif

