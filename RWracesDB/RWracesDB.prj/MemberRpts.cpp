// display Member Record


#include "pch.h"
#include "MemberRpts.h"
#include "Database.h"
#include "MbrSortList.h"
#include "MessageBox.h"
#include "NotePad.h"


void MemberRpts::excel() {
MbrLstIter iter(mbrSortList);
MbrItem*   item;

  header();

  for (item = iter(); item; item = iter++) if (item->curMbr) display(*item->rcd);
  }


void MemberRpts::covidList() {
MbrLstIter iter(mbrSortList);
MbrItem*   item;
MbrRcd*    rcd;
AsnRcd*    assgnPrefRcd;
bool       isResponder;
bool       isPrimary;
bool       isSecondary;
bool       isOfficer;

  header();

  for (item = iter(); item; item = iter++) {

    if (!item->curMbr) continue;

    rcd = item->rcd;   assgnPrefRcd = asnTbl.find(rcd->assgnPrefID);   if (!assgnPrefRcd) continue;

    isResponder = !rcd->responder.isEmpty();
    isPrimary   = assgnPrefRcd->aPKey == _T('P');
    isSecondary = assgnPrefRcd->aPKey == _T('E');
    isOfficer   = rcd->isOfficer;

    if ((isResponder && isPrimary) || (isResponder && isSecondary) || isOfficer) display(*rcd);
    }
  }


void MemberRpts::backup() {
MbrIter iter(mbrTbl);
MbrRcd* rcd;

  header();

  for (rcd = iter(); rcd; rcd = iter++) display(*rcd);
  }


void MemberRpts::comparison() {
MbrIter iter(mbrTbl);
MbrRcd* rcd;

  header(true);

  for (rcd = iter(); rcd; rcd = iter++) display(*rcd);
  }


void MemberRpts::header(bool comparison) {

  notePad.clear();

  notePad << _T("BadgeNumber,");
  notePad << _T("mbrFirstName,");
  notePad << _T("mbrMiddleInitial,");
  notePad << _T("mbrLastName,");
  notePad << _T("mbrSuffix,");
  notePad << _T("mbrStreet,");
  notePad << _T("mbrAptSuite,");
  notePad << _T("mbrCity,");
  notePad << _T("mbrState,");
  notePad << _T("mbrZip,");
  notePad << _T("mbrAddrIsPO,");
  notePad << _T("mbrLocationZip,");
  notePad << _T("mbrPrimaryEmail,");
  notePad << _T("mbrSecondaryEmail,");

  notePad << _T("mbrPhone,");
  notePad << _T("mbrCell,");
  notePad << _T("txtDevPrim,");
  notePad << _T("txtDevSec,");

  if (comparison) notePad << nCrlf;

  notePad << _T("CallSign,");
  notePad << _T("FCCExpiration,");
  notePad << _T("StartDate,");
  notePad << _T("DSWDate,");
  notePad << _T("BadgeExpDate,");
  notePad << _T("Responder,");

  if (comparison) notePad << nCrlf;

  notePad << _T("emplFirstName,");
  notePad << _T("emplMiddleInitial,");
  notePad << _T("emplLastName,");
  notePad << _T("emplSuffix,");
  notePad << _T("emplStreet,");
  notePad << _T("emplAptSuite,");
  notePad << _T("emplCity,");
  notePad << _T("emplState,");
  notePad << _T("emplZip,");
  notePad << _T("emplAddrIsPO,");
  notePad << _T("emplLocationZip,");
  notePad << _T("emplEmail,");
  notePad << _T("emplPhone,");
  notePad << _T("emplCell,");

  if (comparison) notePad << nCrlf;

  notePad << _T("iceFirstName,");
  notePad << _T("iceMiddleInitial,");
  notePad << _T("iceLastName,");
  notePad << _T("iceSuffix,");
  notePad << _T("iceStreet,");
  notePad << _T("iceAptSuite,");
  notePad << _T("iceCity,");
  notePad << _T("iceState,");
  notePad << _T("iceZip,");
  notePad << _T("iceAddrIsPO,");
  notePad << _T("iceLocationZip,");
  notePad << _T("iceEmail,");
  notePad << _T("icePhone,");
  notePad << _T("iceCell,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Handheld,");
  notePad << _T("PortMobile,");
  notePad << _T("PortPacket,");
  notePad << _T("OtherEquip,");
  notePad << _T("Multilingual,");
  notePad << _T("OtherCapabilities,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Limitations,");

  if (comparison) notePad << nCrlf;

  notePad << _T("AssgnPrefKey,");
  notePad << _T("AssgnPrefDsc,");

  if (comparison) notePad << nCrlf;

  notePad << _T("LocationPrefKey,");
  notePad << _T("LocationPref,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Comments,");

  if (comparison) notePad << nCrlf;

  notePad << _T("ShirtSize,");
  notePad << _T("IsOfficer,");
  notePad << _T("StatusAbr,");
  notePad << _T("StatusDsc,");

  if (comparison) notePad << nCrlf;

  notePad << _T("SkillCertifications,");
  notePad << _T("EOC_Certifications,");
  notePad << _T("UpdateDate,");
  notePad << _T("BadgeOK");

  if (comparison) notePad << nCrlf << _T("-------------<EndRcd>-------------") << nCrlf;

  notePad << nCrlf;
  }


void MemberRpts::display (MbrRcd& rcd) {
bool    comparison      = dspType == CmpDspType;

EntRcd* mbrRcd          = entTbl.find(rcd.mbrEntityID);
EntRcd* emplRcd         = entTbl.find(rcd.emplEntityID);
EntRcd* iceRcd          = entTbl.find(rcd.iCE_EntityID);
AsnRcd* assgnPrefRcd    = asnTbl.find(rcd.assgnPrefID);
LocRcd* locationPrefRcd = locTbl.find(rcd.locationPrefID);
StsRcd* statusRcd       = stsTbl.find(rcd.statusID);

  quoted.commaOut();

  notePad << rcd.badgeNumber << _T(",");

  if (rcd.textMsgPh1.isEmpty() && mbrRcd && !mbrRcd->phone2.isEmpty()) {
    rcd.textMsgPh1 = mbrRcd->phone2;
    String s = mbrRcd->firstName + _T(" ") + mbrRcd->lastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  if (!dspEntity(mbrRcd, &rcd)) notePad << _T(",,,,,,,,,,,,,,,");

  quoted.stg(rcd.textMsgPh1);
  quoted.stg(rcd.textMsgPh2);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.callSign);

  quoted.date(rcd.fCCExpiration);
  quoted.date(rcd.startDate);
  quoted.date(rcd.dSWDate);
  quoted.date(rcd.badgeExpDate);
  quoted.date(rcd.responder);

  if (comparison) notePad << nCrlf;

  if (!dspEntity(emplRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  if (!dspEntity(iceRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.handHeld);
  quoted.stg(rcd.portMobile);
  quoted.stg(rcd.portPacket);
  quoted.stg(rcd.otherEquip);
  quoted.stg(rcd.multilingual);
  quoted.stg(rcd.otherCapabilities);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.limitations);

  if (comparison) notePad << nCrlf;

  if (assgnPrefRcd) {
    quoted.stg(assgnPrefRcd->aPKey);
    quoted.stg(assgnPrefRcd->txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  if (locationPrefRcd) {
    quoted.stg(locationPrefRcd->key);
    quoted.stg(locationPrefRcd->txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.comments);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.shirtSize);
  notePad << rcd.isOfficer << _T(",");

  if (statusRcd) {
    quoted.stg(statusRcd->abbreviation);
    quoted.stg(statusRcd->description);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.skillCertifications);
  quoted.stg(rcd.eOC_Certifications);
  quoted.stg(rcd.updateDate);

  notePad << rcd.badgeOK;

  if (comparison) notePad << nCrlf << _T("-------------<EndRcd>-------------") << nCrlf;

  notePad << nCrlf;
  }


bool MemberRpts::dspEntity(EntRcd* ent, MbrRcd* rcd) {
AdrRcd*   addrRcd;
CtyRcd* cityRcd;

  if (!ent) return false;

  quoted.stg(ent->firstName);
  quoted.stg(ent->middleInitial);
  quoted.stg(ent->lastName);
  quoted.stg(ent->suffix);

  addrRcd = adrTbl.find(ent->addrID);

  if (addrRcd) {
    quoted.stg(addrRcd->address1);
    quoted.stg(addrRcd->address2);
    }
  else notePad << _T(",,");

  cityRcd = ctyTbl.find(ent->cityStID);

  if (cityRcd) {
    quoted.stg(cityRcd->city);
    quoted.stg(cityRcd->state);
    quoted.stg(cityRcd->zip);
    }
  else notePad << _T(",,,");

  notePad << ent->addrIsPO << _T(",");
  quoted.stg(ent->locationZip);
  quoted.stg(ent->eMail);
  if (rcd) quoted.stg(rcd->secondaryEmail);

  quoted.stg(ent->phone1);
  quoted.stg(ent->phone2);
  return true;
  }







