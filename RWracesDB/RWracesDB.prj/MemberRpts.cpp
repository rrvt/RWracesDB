// display Member Record


#include "stdafx.h"
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







#if 0
#include "AddressTbl.h"
#include "AssgnPrefTbl.h"
#include "CityStateTbl.h"
#include "EntityTbl.h"
#include "MemberTbl.h"
#include "StatusTbl.h"
//#include "LocationPrefTbl.h"
#endif
#if 0
void MemberRpts::info() {
MbrIter                   iter(mbrTbl);
MbrRcd*                   rcd;
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
#endif


#if 0
void MemberRpts::idList() {
MbrIter                 iter(mbrTbl);
MbrRcd*                 rcd;
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
#endif


#if 0
//void MemberRpts::badgesCS() {dspBadges(BdgFCCSort);}


//void MemberRpts::badgesDT() {dspBadges(BdgDateSort);}


void MemberRpts::dspBadges(BadgeSort badgeSort) {
Expandable<MemberInfo, 2> members;
MbrIter                   iter(mbrTbl);
MbrRcd*                   rcd;
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
#endif


#if 0
void MemberRpts::formerNm() {former(FmrNameSort);}


void MemberRpts::formerCS() {former(FmrFCCSort);}



void MemberRpts::former(FmrSort sortKey) {
Expandable<MemberInfo, 2> members;
MbrIter                   iter(mbrTbl);
MbrRcd*                   rcd;
int                       i;
int                       n;
int                       lng;
int                       maxFn = 0;
int                       maxLn = 0;
int                       tab1;
int                       tab2;


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


bool MemberRpts::getFormerMbrInfo(MbrRcd& rcd, MemberInfo& memberInfo) {
int        statusID  = rcd.statusID;
StsRcd* statusRcd = stsTbl.find(statusID);

  if (!statusRcd || statusRcd->abbreviation != _T("Fmr")) return false;

  EntRcd* mbrRcd = entTbl.find(rcd.mbrEntityID);   if (!mbrRcd) return false;

  memberInfo.lastName  = mbrRcd->lastName;   memberInfo.lastName.trim();
  memberInfo.firstName = mbrRcd->firstName;  memberInfo.firstName.trim();
  memberInfo.callSign  = rcd.callSign;       memberInfo.callSign.trim();

  return true;
  }


bool MemberRpts::getMemberInfo(MbrRcd& rcd, MemberInfo& memberInfo) {
int     statusID  = rcd.statusID;
StsRcd* statusRcd = stsTbl.find(statusID);

  if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) return false;

  EntRcd* mbrRcd = entTbl.find(rcd.mbrEntityID);   if (!mbrRcd) return false;

  memberInfo.lastName  = mbrRcd->lastName;   memberInfo.lastName.trim();
  memberInfo.firstName = mbrRcd->firstName;  memberInfo.firstName.trim();

  memberInfo.callSign    = rcd.callSign;    memberInfo.callSign.trim();
  memberInfo.badgeNumber = rcd.badgeNumber; memberInfo.badgeNumber.trim();
  memberInfo.badgeOk     = rcd.badgeOK;     memberInfo.badgeExpDate = rcd.badgeExpDate;

  return true;
  }
#endif

//    if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) continue;
//#include "IDitem.h"
//#include "qsort.h"
//#include "RWracesDB.h"
//#include "RWracesDBView.h"






