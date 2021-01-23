// display Member Record


#include "stdafx.h"
#include "MemberRpts.h"
#include "IDitem.h"
#include "MapData.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "qsort.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"


void MemberRpts::info() {
MmbrIter                  iter(memberTable);
MemberRecord*             rcd;
int                       i;
int                       n;
Expandable<MemberInfo, 2> members;

  for (rcd = iter(); rcd; rcd = iter++) {
    MemberInfo memberInfo;
    if (!getMemberInfo(*rcd, memberInfo)) continue;

    memberInfo.sortKey = memberInfo.callSign;   members = memberInfo;
    }

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  for (i = 0, n = members.end(); i < n; i++) {
    MemberInfo& mi = members[i];

    notePad << mi.callSign    << _T(",");
    notePad << mi.firstName   << _T(",");
    notePad << mi.lastName    << _T(",");
    notePad << mi.badgeNumber << nCrlf;
    }
  }



void MemberRpts::idList() {
MmbrIter                iter(memberTable);
MemberRecord*           rcd;
int                     i;
int                     n;
Expandable<IDitem, 128> data;

  for (rcd = iter(); rcd; rcd = iter++) {
    MemberInfo memberInfo;
    if (!getMemberInfo(*rcd, memberInfo)) continue;

    IDitem& item     = data.nextData();
    item.name        = memberInfo.lastName + memberInfo.firstName;
    item.callSign    = memberInfo.callSign;
    item.badgeNumber = memberInfo.badgeNumber;
    }

  n = data.end();   qsort(&data[0], &data[n-1]);

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  notePad << nSetTab(26) << nSetRTab(45) << nSetTab(47);

  notePad << _T("Name")     << nTab << _T("Call Sign") << nTab;
  notePad << _T("Badge") << nTab << _T("Responded") <<  nCrlf;

  for (i = 0; i < n; i++) {
    IDitem& item = data[i];
    notePad <<         item.name        << _T(",");
    notePad << nTab << item.callSign    << _T(",");
    notePad << nTab << item.badgeNumber << _T(":") << nCrlf;
    }
  }



void MemberRpts::badgesCS() {dspBadges(BdgFCCSort);}


void MemberRpts::badgesDT() {dspBadges(BdgDateSort);}


void MemberRpts::dspBadges(BadgeSort badgeSort) {
Expandable<MemberInfo, 2> members;
MmbrIter                  iter(memberTable);
MemberRecord*             rcd;
int                       i;
int                       n;
int                       lng;
int                       maxFn = 0;
int                       maxLn = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    MemberInfo memberInfo;     if (!getMemberInfo(*rcd, memberInfo)) continue;

    if (!memberInfo.badgeOk) continue;

    if (badgeSort == BdgDateSort) memberInfo.sortKey  = getDateKey(memberInfo.badgeExpDate);
    memberInfo.sortKey += memberInfo.callSign;

    lng = memberInfo.firstName.length();  if (lng > maxFn) maxFn = lng;
    lng = memberInfo.lastName.length();   if (lng > maxLn) maxLn = lng;

    members = memberInfo;
    }

  int tab2 = 8    + maxFn + 2;
  int tab3 = tab2 + maxLn + 2;
  int tab4 = tab3 + 4;

  notePad.clear();   view()->setFont(_T("Courier New"), 12.0);

  notePad << nClrTabs << nSetTab(8) << nSetTab(tab2) << nSetTab(tab3) << nSetTab(tab4);

  for (i = 0, n = members.end(); i < n; i++) {

    MemberInfo& mi = members[i];

    String t; t.format(_T("%03s"), mi.badgeNumber.str());

    String expDate = decodeDate(mi.badgeExpDate);

    notePad << mi.callSign    << nTab;
    notePad << mi.firstName   << nTab;
    notePad << mi.lastName    << nTab;
    notePad << t << nTab;
    notePad << expDate;                     //mi.badgeExpDate;
    notePad << nCrlf;
    }
  }



String MemberRpts::getDateKey(String& d) {
String yr;
String mn;
String dy;

  if (d.isEmpty()) return _T("000000");

  mn = d.substr(0, 2);
  dy = d.substr(2, 2);
  yr = d.substr(4, 2);   return yr + mn + dy;
  }


String MemberRpts::decodeDate(String& d) {
String yr;
String mn;
String dy;

  if (d.isEmpty()) return _T("");

  mn = d.substr(0, 2);
  dy = d.substr(2, 2);
  yr = d.substr(4, 2);   return mn + _T("/") + dy + _T("/") + yr;
  }



void MemberRpts::formerNm() {former(FmrNameSort);}


void MemberRpts::formerCS() {former(FmrFCCSort);}



void MemberRpts::former(FmrSort sortKey) {
Expandable<MemberInfo, 2> members;
MmbrIter      iter(memberTable);
MemberRecord* rcd;
int           i;
int           n;
int           lng;
int           maxFn = 0;
int           maxLn = 0;
int           tab1;
int           tab2;


  for (rcd = iter(); rcd; rcd = iter++) {
    MemberInfo memberInfo;

    if (!getFormerMbrInfo(*rcd, memberInfo)) continue;

    if (sortKey == FmrNameSort) memberInfo.sortKey = memberInfo.lastName + memberInfo.firstName;
    else                        memberInfo.sortKey = memberInfo.callSign;

    lng = memberInfo.firstName.length();  if (lng > maxFn) maxFn = lng;
    lng = memberInfo.lastName.length();   if (lng > maxLn) maxLn = lng;

    members = memberInfo;
    }

  if (sortKey == FmrNameSort) {
    tab1 = maxFn + 2;
    tab2 = tab1 + maxLn + 2;
    }
  else {
    tab1 = 8;
    tab2 = tab1 + maxFn + 2;
    }

  notePad.clear();   view()->setFont(_T("Courier New"), 12.0);

  notePad << nClrTabs << nSetTab(tab1) << nSetTab(tab2);

  if (sortKey == FmrNameSort)
       {notePad << _T("First") << nTab << _T("Last") << nTab << _T("FCC") << nCrlf;}
  else {notePad << _T("FCC") << nTab << _T("First") << nTab << _T("Last") << nCrlf;}

  for (i = 0, n = members.end(); i < n; i++) {

    MemberInfo& mi = members[i];
    if (sortKey == FmrNameSort) {
      notePad << mi.firstName   << nTab;
      notePad << mi.lastName    << nTab;
      notePad << mi.callSign;
      }
    else {
      notePad << mi.callSign    << nTab;
      notePad << mi.firstName   << nTab;
      notePad << mi.lastName;
      }
    notePad << nCrlf;
    }
  }


bool MemberRpts::getFormerMbrInfo(MemberRecord& rcd, MemberInfo& memberInfo) {
int           statusID  = rcd.StatusID;
StatusRecord* statusRcd = statusTable.find(statusID);

  if (!statusRcd || statusRcd->Abbreviation != _T("Fmr")) return false;

  EntityRecord* mbrRcd = entityTable.find(rcd.MbrEntityID);   if (!mbrRcd) return false;

  memberInfo.lastName  = mbrRcd->LastName;   memberInfo.lastName.trim();
  memberInfo.firstName = mbrRcd->FirstName;  memberInfo.firstName.trim();
  memberInfo.callSign  = rcd.CallSign;       memberInfo.callSign.trim();

  return true;
  }


bool MemberRpts::getMemberInfo(MemberRecord& rcd, MemberInfo& memberInfo) {
  int           statusID  = rcd.StatusID;
  StatusRecord* statusRcd = statusTable.find(statusID);

  if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) return false;
  EntityRecord* mbrRcd = entityTable.find(rcd.MbrEntityID);   if (!mbrRcd) return false;

  memberInfo.lastName  = mbrRcd->LastName;   memberInfo.lastName.trim();
  memberInfo.firstName = mbrRcd->FirstName;  memberInfo.firstName.trim();

  memberInfo.callSign    = rcd.CallSign;    memberInfo.callSign.trim();
  memberInfo.badgeNumber = rcd.BadgeNumber; memberInfo.badgeNumber.trim();
  memberInfo.badgeOk     = rcd.BadgeOK;     memberInfo.badgeExpDate = rcd.BadgeExpDate;

  return true;
  }



void MemberRpts::excel() {
MmbrIter      iter(memberTable);
MemberRecord* rcd;

  header();

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    display(*rcd);
    }
  }


void MemberRpts::backup() {
MmbrIter      iter(memberTable);
MemberRecord* rcd;

  header();

  for (rcd = iter(); rcd; rcd = iter++) display(*rcd);
  }


void MemberRpts::comparison() {
MmbrIter      iter(memberTable);
MemberRecord* rcd;

  header(true);

  for (rcd = iter(); rcd; rcd = iter++) display(*rcd);
  }


void MemberRpts::header(bool comparison) {

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

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


void MemberRpts::display (MemberRecord& rcd) {
bool                comparison        = dspType == CmpDspType;
int                 mbrID             = rcd.MbrEntityID;
int                 emplID            = rcd.EmplEntityID;
int                 iceID             = rcd.ICE_EntityID;
int                 assgnPrefID       = rcd.AssgnPrefID;
int                 locPrefID         = rcd.LocationPrefID;
int                 statusID          = rcd.StatusID;

EntityRecord*       mbrRcd            = entityTable.find(mbrID);
EntityRecord*       emplRcd           = entityTable.find(emplID);
EntityRecord*       iceRcd            = entityTable.find(iceID);
AssgnPrefRecord*    assgnPrefRcd      = assgnPrefTable.find(assgnPrefID);
LocationPrefRecord* locationPrefRcd   = locationPrefTable.find(locPrefID);
StatusRecord*       statusRcd         = statusTable.find(statusID);

  quoted.commaOut();

  notePad << rcd.BadgeNumber << _T(",");

  if (rcd.TextMsgPh1.isEmpty() && mbrRcd && !mbrRcd->Phone2.isEmpty()) {
    rcd.TextMsgPh1 = mbrRcd->Phone2;
    String s = mbrRcd->FirstName + _T(" ") + mbrRcd->LastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  if (!dspEntity(mbrRcd, &rcd)) notePad << _T(",,,,,,,,,,,,,,,");

  quoted.stg(rcd.TextMsgPh1);
  quoted.stg(rcd.TextMsgPh2);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.CallSign);

  quoted.date(rcd.FCCExpiration);
  quoted.date(rcd.StartDate);
  quoted.date(rcd.DSWDate);
  quoted.date(rcd.BadgeExpDate);
  quoted.date(rcd.Responder);

  if (comparison) notePad << nCrlf;

  if (!dspEntity(emplRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  if (!dspEntity(iceRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.HandHeld);
  quoted.stg(rcd.PortMobile);
  quoted.stg(rcd.PortPacket);
  quoted.stg(rcd.OtherEquip);
  quoted.stg(rcd.Multilingual);
  quoted.stg(rcd.OtherCapabilities);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.Limitations);

  if (comparison) notePad << nCrlf;

  if (assgnPrefRcd) {
    quoted.stg(assgnPrefRcd->APKey);
    quoted.stg(assgnPrefRcd->Txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  if (locationPrefRcd) {
    quoted.stg(locationPrefRcd->Key);
    quoted.stg(locationPrefRcd->Txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.Comments);

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.ShirtSize);
  notePad << rcd.IsOfficer << _T(",");

  if (statusRcd) {
    quoted.stg(statusRcd->Abbreviation);
    quoted.stg(statusRcd->Description);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoted.stg(rcd.SkillCertifications);
  quoted.stg(rcd.EOC_Certifications);
  quoted.stg(rcd.UpdateDate);

  notePad << rcd.BadgeOK;

  if (comparison) notePad << nCrlf << _T("-------------<EndRcd>-------------") << nCrlf;

  notePad << nCrlf;
  }



bool MemberRpts::dspEntity(EntityRecord* ent, MemberRecord* rcd) {
AddressRecord*   addrRcd;
CityStateRecord* cityRcd;

  if (!ent) return false;

  quoted.stg(ent->FirstName);
  quoted.stg(ent->MiddleInitial);
  quoted.stg(ent->LastName);
  quoted.stg(ent->Suffix);

  addrRcd = addressTable.find(ent->AddrID);

  if (addrRcd) {
    quoted.stg(addrRcd->Address1);
    quoted.stg(addrRcd->Address2);
    }
  else notePad << _T(",,");

  cityRcd = cityStateTable.find(ent->CityStID);

  if (cityRcd) {
    quoted.stg(cityRcd->City);
    quoted.stg(cityRcd->State);
    quoted.stg(cityRcd->Zip);
    }
  else notePad << _T(",,,");

  notePad << ent->AddrIsPO << _T(",");
  quoted.stg(ent->LocationZip);
  quoted.stg(ent->eMail);
  if (rcd) quoted.stg(rcd->SecondaryEmail);

  quoted.stg(ent->Phone1);
  quoted.stg(ent->Phone2);
  return true;
  }

