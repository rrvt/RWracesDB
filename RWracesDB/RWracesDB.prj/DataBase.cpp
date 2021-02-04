// Database Restoration


#include "stdafx.h"
#include "DataBase.h"
#include "Archive.h"
#include "BackupRcds.h"
#include "GetPathDlg.h"
#include "MapData.h"
#include "Utilities.h"




struct Status {
TCchar* key;
TCchar* desc;
};


static void FixedInit(Status sts[], int n, MapBase& tbl);


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

  FixedInit(statusList, noElements(statusList), statusTable);
  FixedInit(locPref,    noElements(locPref),    locationPrefTable);
  FixedInit(asnPref,    noElements(asnPref),    assgnPrefTable);

  csv = iter();   if (csv && csv->CallSign == _T("CallSign")) csv = iter++;

  for (i = 0; csv; i++, csv = iter++) {
    if (!restoreRcd(*csv)) {
      notePad << _T("Unable to upload: ") << csv->mbrFirstName << _T(" ") << csv->mbrLastName << _T(" ");
      notePad << csv->CallSign << nCrlf;
      }
    }

  memberTable.toDatabase();   entityTable.toDatabase();
  }


void FixedInit(Status sts[], int n, MapBase& tbl) {
int i;

  for (i = 0; i < n; i++) {Status& itm = sts[i];  tbl.add(itm.key, itm.desc);}
  }


void DataBase::load(Archive& ar) {backupRcds.load(ar);}


bool DataBase::restoreRcd(BackupRcd& csv) {
MemberRecord*    mbr     = 0;
EntityRecord*    mbrEnt  = 0;
AddressRecord*   mbrAdr  = 0;
CityStateRecord* mbrCty  = 0;
EntityRecord*    emplEnt = 0;
AddressRecord*   emplAdr = 0;
CityStateRecord* emplCty = 0;
EntityRecord*    iceEnt  = 0;
AddressRecord*   iceAdr  = 0;
CityStateRecord* iceCty  = 0;

  if (isEmpty(&csv.mbrLastName, &csv.mbrFirstName, &csv.CallSign, 0)) return false;

  mbr = memberTable.get(csv.CallSign);

  mbr->BadgeNumber         = sanitizeBadgeNo(csv.BadgeNumber);
  mbr->FCCExpiration       = sanitizeDate(csv.FCCExpiration);
  mbr->StartDate           = sanitizeDate(csv.StartDate);
  mbr->DSWDate             = sanitizeDate(csv.DSWDate);
  mbr->BadgeExpDate        = sanitizeDate(csv.BadgeExpDate);
  mbr->Responder           = sanitizeDate(csv.Responder);
  mbr->SecondaryEmail      = csv.SecondaryEmail;
  mbr->TextMsgPh1          = csv.txtDevPrim;
  mbr->TextMsgPh2          = csv.txtDevSec;
  mbr->HandHeld            = quoted.remDbl(csv.Handheld);
  mbr->PortMobile          = quoted.remDbl(csv.PortMobile);
  mbr->PortPacket          = quoted.remDbl(csv.PortPacket);
  mbr->OtherEquip          = quoted.remDbl(csv.OtherEquip);
  mbr->Multilingual        = quoted.remDbl(csv.Multilingual);
  mbr->OtherCapabilities   = quoted.remDbl(csv.OtherCapabilities);
  mbr->Limitations         = quoted.remDbl(csv.Limitations);
  mbr->Comments            = quoted.remDbl(csv.Comments);
  mbr->ShirtSize           = csv.ShirtSize;
  mbr->SkillCertifications = csv.SkillCertifications;
  mbr->EOC_Certifications  = csv.EOC_Certifications;
  mbr->UpdateDate          = csv.UpdateDate;

  mbr->AssgnPrefID         = assgnPrefTable.add(csv.AssgnPrefKey, csv.AssgnPrefDsc);

  mbr->LocationPrefID      = locationPrefTable.add(csv.LocationPrefKey, csv.LocationPref);
  mbr->IsOfficer           = csv.IsOfficer;
  mbr->StatusID            = statusTable.add(csv.StatusAbr, csv.StatusDsc);
  mbr->BadgeOK             = csv.BadgeOK;

  mbrEnt = entityTable.get(csv.mbrFirstName, csv.mbrLastName, csv.mbrEmail, csv.mbrPhone, csv.mbrCell);

  if (mbrEnt) {
    mbrEnt->MiddleInitial  = csv.mbrMiddleInitial;
    mbrEnt->Suffix         = csv.mbrSuffix;
    mbrEnt->AddrIsPO       = csv.mbrAddrIsPO == "1";
    mbrEnt->LocationZip    = csv.mbrLocationZip;
    mbrEnt->mark();

    mbrAdr = addressTable.get(sanitizeAddr(csv.mbrStreet), sanitizeAddr(csv.mbrAptSuite));
    if (mbrAdr) mbrEnt->AddrID = mbrAdr->AddressID;

    mbrCty = cityStateTable.get(csv.mbrCity , csv.mbrState, csv.mbrZip);
    if (mbrCty) mbrEnt->CityStID = mbrCty->CityStateID;

    mbr->MbrEntityID  = mbrEnt->EntityID;
    }

  emplEnt = entityTable.get(csv.emplFirstName, csv.emplLastName,
                                                             csv.emplEmail, csv.emplPhone, csv.emplCell);
  if (emplEnt) {
    emplEnt->MiddleInitial = csv.emplMiddleInitial;
    emplEnt->Suffix        = csv.emplSuffix;
    emplEnt->AddrIsPO      = csv.emplAddrIsPO;
    emplEnt->LocationZip   = csv.emplLocationZip;
    emplEnt->mark();

    emplAdr             = addressTable.get(sanitizeAddr(csv.emplStreet), sanitizeAddr(csv.emplAptSuite));
    if (emplAdr) emplEnt->AddrID = emplAdr->AddressID;

    emplCty                = cityStateTable.get(csv.emplCity, csv.emplState, csv.emplZip);
    if (emplCty) emplEnt->CityStID = emplCty->CityStateID;

    mbr->EmplEntityID = emplEnt->EntityID;
    }

  iceEnt = entityTable.get(csv.iceFirstName, csv.iceLastName, csv.iceEmail, csv.icePhone, csv.iceCell);

  if (iceEnt) {
    iceEnt->MiddleInitial  = csv.iceMiddleInitial;
    iceEnt->Suffix         = csv.iceSuffix;
    iceEnt->AddrIsPO       = csv.iceAddrIsPO;
    iceEnt->LocationZip    = csv.iceLocationZip;
    iceEnt->mark();

    iceAdr = addressTable.get(sanitizeAddr(csv.iceStreet), sanitizeAddr(csv.iceAptSuite));
    if (iceAdr) iceEnt->AddrID = iceAdr->AddressID;

    iceCty = cityStateTable.get(csv.iceCity, csv.iceState, csv.iceZip);
    if (iceCty) iceEnt->CityStID = iceCty->CityStateID;

    mbr->ICE_EntityID = iceEnt->EntityID;
    }

  mbr->mark();   return true;
  }


