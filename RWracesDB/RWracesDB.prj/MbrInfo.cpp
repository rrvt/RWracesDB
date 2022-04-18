// Member Info -- Used in reports


#include "stdafx.h"
#include "MbrInfo.h"
#include "Database.h"
#include "mbrSortList.h"
#include "NotePad.h"


void InfoRpts::info() {
MbrLstIter iter(mbrSortList);
MbrItem*   item;

int     i;
int     n;

  data.clear();

  for (item = iter(); item; item = iter++) {

    if (!item->curMbr) continue;

    MbrInfo memberInfo;
    if (!memberInfo.get(*item->rcd)) continue;

    memberInfo.sortKey = memberInfo.callSign;   data = memberInfo;
    }

  notePad.clear();

  for (i = 0, n = data.end(); i < n; i++) {
    MbrInfo& mi = *data[i].p;

    notePad << mi.callSign    << _T(",");
    notePad << mi.firstName   << _T(",");
    notePad << mi.lastName    << _T(",");
    notePad << mi.badgeNumber << nCrlf;
    }
  }


void InfoRpts::dspBadges(BadgeSort badgeSort) {
MbrLstIter iter(mbrSortList);
MbrItem*   item;
int        i;
int        n;
int        lng;
int        maxFn = 0;
int        maxLn = 0;

  data.clear();

  for (item = iter(); item ; item = iter++) {
    if (!item->curMbr) continue;

    MbrInfo memberInfo;     if (!memberInfo.get(*item->rcd)) continue;

    if (!memberInfo.badgeOk) continue;

    if (badgeSort == BdgDateSort) memberInfo.sortKey  = getDateKey(memberInfo.badgeExpDate);
    memberInfo.sortKey += memberInfo.callSign;

    lng = memberInfo.firstName.length();  if (lng > maxFn) maxFn = lng;
    lng = memberInfo.lastName.length();   if (lng > maxLn) maxLn = lng;

    data = memberInfo;
    }

  int tab2 = 8    + maxFn + 2;
  int tab3 = tab2 + maxLn + 2;
  int tab4 = tab3 + 4;

  notePad.clear();

  notePad << nClrTabs << nSetTab(8) << nSetTab(tab2) << nSetTab(tab3) << nSetTab(tab4);

  for (i = 0, n = data.end(); i < n; i++) {

    MbrInfo& mi = *data[i].p;

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

String InfoRpts::getDateKey(String& d) {
String yr;
String mn;
String dy;

  if (d.isEmpty()) return _T("000000");

  mn = d.substr(0, 2);
  dy = d.substr(2, 2);
  yr = d.substr(4, 2);   return yr + mn + dy;
  }


String InfoRpts::decodeDate(String& d) {
String yr;
String mn;
String dy;

  if (d.isEmpty()) return _T("");

  mn = d.substr(0, 2);
  dy = d.substr(2, 2);
  yr = d.substr(4, 2);   return mn + _T("/") + dy + _T("/") + yr;
  }



void InfoRpts::former(FmrSort sortKey) {
MbrLstIter iter(mbrSortList);
MbrItem*   item;
int        i;
int        n;
int        lng;
int        maxFn = 0;
int        maxLn = 0;
int        tab1;
int        tab2;

  data.clear();

  for (item = iter(); item; item = iter++) {

    if (item->curMbr) continue;

    MbrInfo memberInfo;

    if (!memberInfo.get(*item->rcd)) continue;

    if (sortKey == FmrNameSort) memberInfo.sortKey = memberInfo.lastName + memberInfo.firstName;
    else                        memberInfo.sortKey = memberInfo.callSign;

    lng = memberInfo.firstName.length();  if (lng > maxFn) maxFn = lng;
    lng = memberInfo.lastName.length();   if (lng > maxLn) maxLn = lng;

    data = memberInfo;
    }

  if (sortKey == FmrNameSort) {
    tab1 = maxFn + 2;
    tab2 = tab1 + maxLn + 2;
    }
  else {
    tab1 = 8;
    tab2 = tab1 + maxFn + 2;
    }

  notePad.clear();

  notePad << nClrTabs << nSetTab(tab1) << nSetTab(tab2);

  if (sortKey == FmrNameSort)
       {notePad << _T("First") << nTab << _T("Last") << nTab << _T("FCC") << nCrlf;}
  else {notePad << _T("FCC") << nTab << _T("First") << nTab << _T("Last") << nCrlf;}

  for (i = 0, n = data.end(); i < n; i++) {

    MbrInfo& mi = *data[i].p;
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


bool MbrInfo::get(MbrRcd& rcd) {
EntRcd* mbrEnt;

  mbrEnt       = entTbl.find(rcd.mbrEntityID);   if (!mbrEnt) return false;

  lastName     = mbrEnt->lastName;    lastName.trim();
  firstName    = mbrEnt->firstName;   firstName.trim();

  callSign     = rcd.callSign;        callSign.trim();
  badgeNumber  = rcd.badgeNumber;     badgeNumber.trim();
  badgeOk      = rcd.badgeOK;
  badgeExpDate = rcd.badgeExpDate;

  return true;
  }


#if 0
bool MbrInfo::getFormer(MbrRcd& rcd) {

  EntRcd* mbrRcd = entTbl.find(rcd.mbrEntityID);   if (!mbrRcd) return false;

  lastName  = mbrRcd->lastName;   lastName.trim();
  firstName = mbrRcd->firstName;  firstName.trim();
  callSign  = rcd.callSign;       callSign.trim();

  return true;
  }
#endif
//MbrRcd*    rcd;

