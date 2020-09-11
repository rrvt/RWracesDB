// Restore Backup File


#include "stdafx.h"
#include "RWracesDBDoc.h"
#include "Utilities.h"



void RWracesDBDoc::restoreBackupCSV() {
AddressTable&      addressTable      = maps.data.addressTable;
AssgnPrefTable&    assgnPrefTable    = maps.data.assgnPrefTable;
CityStateTable&    cityStTable       = maps.data.cityStateTable;
EntityTable&       entityTable       = maps.data.entityTable;
LocationPrefTable& locationPrefTable = maps.data.locationPrefTable;
MemberTable&       memberTable       = maps.data.memberTable;
StatusTable&       statusTable       = maps.data.statusTable;

NewCsvData*        csv;
int                i;

  initDefaultBadgeNo();  initStatusTable();   initLocPrefTable();   initAsnPrefTable();

  for (i = 0, csv = newCSV.startLoop(); csv; i++, csv = newCSV.nextCSV()) {
    if (!restoreOneBackupRcd(*csv)) {
      notePad << "Unable to upload: " << csv->mbrFirstName << " " << csv->mbrLastName << " ";
      notePad << csv->CallSign << nCrlf;
      }
    }

  memberTable.updateDatabase();
  }


bool RWracesDBDoc::restoreOneBackupRcd(NewCsvData& csv) {
MemberTable&     memberTable  = maps.data.memberTable;
EntityTable&     entityTable  = maps.data.entityTable;
AddressTable&    addressTable = maps.data.addressTable;
CityStateTable&  cityTable    = maps.data.cityStateTable;

MemberRecord*    mbr;
EntityRecord*    mbrEnt;
AddressRecord*   mbrAdr;
CityStateRecord* mbrCty;
EntityRecord*    emplEnt;
AddressRecord*   emplAdr;
CityStateRecord* emplCty;
EntityRecord*    iceEnt;
AddressRecord*   iceAdr;
CityStateRecord* iceCty;

  if (isEmpty(&csv.mbrLastName, &csv.mbrFirstName, &csv.CallSign, 0)) return false;

  mbr = getMbrRcd(csv.CallSign);

  mbr->BadgeNumber         = sanitizeBadgeNo(csv.BadgeNumber);
  mbr->CallSign            = csv.CallSign;
  mbr->FCCExpiration       = sanitizeDate(csv.FCCExpiration);
  mbr->StartDate           = sanitizeDate(csv.StartDate);
  mbr->DSWDate             = sanitizeDate(csv.DSWDate);
  mbr->BadgeExpDate        = sanitizeDate(csv.BadgeExpDate);
  mbr->Responder           = sanitizeDate(csv.Responder);
  mbr->SecondaryEmail      = csv.SecondaryEmail;
  mbr->TextMsgPh1          = csv.txtDevPrim;
  mbr->TextMsgPh2          = csv.txtDevSec;
  mbr->HandHeld            = csv.Handheld;
  mbr->PortMobile          = csv.PortMobile;
  mbr->PortPacket          = csv.PortPacket;
  mbr->OtherEquip          = csv.OtherEquip;
  mbr->Multilingual        = csv.Multilingual;
  mbr->OtherCapabilities   = csv.OtherCapabilities;
  mbr->Limitations         = csv.Limitations;
  mbr->Comments            = csv.Comments;
  mbr->ShirtSize           = csv.ShirtSize;
  mbr->SkillCertifications = csv.SkillCertifications;
  mbr->EOC_Certifications  = csv.EOC_Certifications;
  mbr->UpdateDate          = csv.UpdateDate;

  mbr->AssgnPrefID         = getAssgnPrefID(csv.AssgnPrefKey, csv.AssgnPrefDsc);

  mbr->LocationPrefID      = getLocationPrefID(csv.LocationPrefKey, csv.LocationPref);
  mbr->IsOfficer           = csv.IsOfficer;
  mbr->StatusID            = getStatusID(csv.StatusAbr, csv.StatusDsc);
  mbr->BadgeOK             = csv.BadgeOK;

  mbrEnt                   = getEntRcd(csv.mbrFirstName, csv.mbrLastName);

  if (mbrEnt) {
    mbrEnt->MiddleInitial  = csv.mbrMiddleInitial;
    mbrEnt->Suffix         = csv.mbrSuffix;
    mbrEnt->AddrIsPO       = csv.mbrAddrIsPO == "1";
    mbrEnt->LocationZip    = csv.mbrLocationZip;
    mbrEnt->eMail          = csv.mbrEmail;
    mbrEnt->Phone1         = csv.mbrPhone;
    mbrEnt->Phone2         = csv.mbrCell;

    mbrAdr                 = getAddrRcd(sanitizeAddr(csv.mbrStreet), sanitizeAddr(csv.mbrAptSuite));

    mbrCty                 = getCityRcd(csv.mbrCity , csv.mbrState, csv.mbrZip);
    }

  emplEnt                  = getEntRcd(csv.emplFirstName, csv.emplLastName);

  if (emplEnt) {
    emplEnt->MiddleInitial = csv.emplMiddleInitial;
    emplEnt->Suffix        = csv.emplSuffix;
    emplEnt->AddrIsPO      = csv.emplAddrIsPO;
    emplEnt->LocationZip   = csv.emplLocationZip;
    emplEnt->eMail         = csv.emplEmail;
    emplEnt->Phone1        = csv.emplPhone;
    emplEnt->Phone2        = csv.emplCell;

    emplAdr                = getAddrRcd(sanitizeAddr(csv.emplStreet), sanitizeAddr(csv.emplAptSuite));

    if (emplAdr) emplCty   = getCityRcd(csv.emplCity, csv.emplState, csv.emplZip);
    }

  iceEnt                   = getEntRcd(csv.iceFirstName, csv.iceLastName);

  if (iceEnt) {
    iceEnt->MiddleInitial  = csv.iceMiddleInitial;
    iceEnt->Suffix         = csv.iceSuffix;
    iceEnt->AddrIsPO       = csv.iceAddrIsPO;
    iceEnt->LocationZip    = csv.iceLocationZip;
    iceEnt->eMail          = csv.iceEmail;
    iceEnt->Phone1         = csv.icePhone;
    iceEnt->Phone2         = csv.iceCell;

    iceAdr                 = getAddrRcd(sanitizeAddr(csv.iceStreet), sanitizeAddr(csv.iceAptSuite));

    if (iceAdr) iceCty     = getCityRcd(csv.iceCity, csv.iceState, csv.iceZip);
    }

  cityTable.updateDatabase();   addressTable.updateDatabase();

  if (mbrEnt) {
    if (mbrAdr) mbrEnt->AddrID   = mbrAdr->AddressID;
    if (mbrCty) mbrEnt->CityStID = mbrCty->CityStateID;
    }

  if (emplEnt) {
    if (emplAdr) emplEnt->AddrID   = emplAdr->AddressID;
    if (emplCty) emplEnt->CityStID = emplCty->CityStateID;
    }

  if (iceEnt) {
    if (iceAdr) iceEnt->AddrID   = iceAdr->AddressID;
    if (iceCty) iceEnt->CityStID = iceCty->CityStateID;
    }

  entityTable.updateDatabase();

  if (mbr) {
    if (mbrEnt)  mbr->MbrEntityID  = mbrEnt->EntityID;
    if (emplEnt) mbr->EmplEntityID = emplEnt->EntityID;
    if (iceEnt)  mbr->ICE_EntityID = iceEnt->EntityID;
    }

  return true;
  }

