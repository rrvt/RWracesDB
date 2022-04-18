// Google Earch Report


#include "stdafx.h"
#include "GoogleRpt.h"
#include "Database.h"
#include "MemberList.h"
#include "NotePad.h"



void GoogleRpt::operator() () {
MemberList ml;
MLstIter   iter(ml);
MbrDsc*    dsc;

  header();

  for (dsc = iter(); dsc; dsc = iter++) {

    display(*dsc->rcd, false);
    display(*dsc->rcd, true);
    }
  }


//Name,Call,Status,Type,Disp Priority,Disp Location,Limitations,
//Address,Cell,Phone,SMS Text,Email,Languages,
//Equipment,
//Other,Comments,geLabel

//"Anderson, Craig ",N6YXK,Active," Responder, DSW on file",ARES Only,Anywhere in city,,
//"14656 Bronson Avenue, San Jose CA 95124",408-768-6025,408-371-8904,408-768-6025,acraiga@pacbell.net,,
//"HT:(1-6m(5w), 3-2m(5w), 2-70cm(5w), 1-23cm(1w)) Prtable:(1-2m(50w), 1-70cm(20w), 1-HF(100w)) Pkt:(mobile) Other:(WiFi, APRS, )",
//"APRS-capable, WiFi",Packet Manager; Missing certs.,"Anderson, N6YXK"


void GoogleRpt::header() {

  notePad.clear();

  notePad << _T("Call Sign,");
  notePad << _T("Name,");
  notePad << _T("Status,");
  notePad << _T("Type,");
  notePad << _T("Priority,");
  notePad << _T("Location,");
  notePad << _T("Limitations,");
  notePad << _T("Addr Type,");
  notePad << _T("Address,");
  notePad << _T("Cell,");
  notePad << _T("Phone,");
  notePad << _T("eMail,");
  notePad << _T("SMS Text,");
  notePad << _T("Languages,");
  notePad << _T("Equipment,");
  notePad << _T("Other,");
  notePad << _T("Comment,");
  notePad << _T("Label");
  notePad << nCrlf;
  }


void GoogleRpt::display(MbrRcd& rcd, bool workAddr) {
int     mbrID           = rcd.mbrEntityID;
int     emplID          = rcd.emplEntityID;
int     assgnPrefID     = rcd.assgnPrefID;
int     locPrefID       = rcd.locationPrefID;
int     statusID        = rcd.statusID;
String  responder       = rcd.responder.trim();
String  dsw             = rcd.dSWDate.trim();

EntRcd* mbrRcd          = entTbl.find(mbrID);      if (!mbrRcd) return;
EntRcd* emplRcd         = entTbl.find(emplID);
AdrRcd* addrRcd;

AsnRcd* assgnPrefRcd    = asnTbl.find(assgnPrefID);
LocRcd* locationPrefRcd = locTbl.find(locPrefID);
StsRcd* statusRcd       = stsTbl.find(statusID);
String  s;
String  addrType        = workAddr ? _T("Work") : _T("Home");

EntRcd* r     = workAddr ? emplRcd : mbrRcd;
bool    avail = addrAvail(r, addrRcd);

  if (workAddr && !avail) return;

  quoted.commaOut();

  quoted.stg(rcd.callSign);

  s = mbrRcd->firstName + _T(' ') + mbrRcd->lastName;
  if (!mbrRcd->suffix.isEmpty()) s += mbrRcd->suffix;
  quoted.stg(s);

  if (statusRcd) {
    s = statusRcd->abbreviation == "Act" ? _T("Active") : _T("Inactive");
    quoted.stg(s);
    }
  else notePad << _T(",");

  s =  responder.isEmpty() ? _T("non-Responder") : _T("Responder");
  s += dsw.isEmpty()       ? _T(" - No DSW")     : _T(" - DSW");
  quoted.stg(s);

  if (assgnPrefRcd) {
    s = assgnPrefRcd->aPKey;
    if      (s == _T("P")) s = _T("1st Call");
    else if (s == _T("E")) s = _T("not 1st Call");
    else if (s == _T("G")) s = _T("General");
    else if (s == _T("L")) s = _T("Last Call");
    else if (s == _T("A")) s = _T("ARES Only");
    else                   s = assgnPrefRcd->txt;
    quoted.stg(s);
    }
  else notePad << _T("ARES Only,");

  if (locationPrefRcd) {
    s = locationPrefRcd->key;
    if      (s == _T("A")) s = _T("Anywhere in city");
    else if (s == _T("5")) s = _T("Within 5 miles");
    else if (s == _T("1")) s = _T("Within 1 mile");
    else if (s == _T("N")) s = _T("Within neighborhood");
    else                   s = locationPrefRcd->txt;
    quoted.stg(s);
    }
  else notePad << _T("Anywhere,");

  quoted.stg(rcd.limitations);

  quoted.stg(addrType);

  entityOut(r, addrRcd);
  String textMsgPh1  = rcd.textMsgPh1;
  String formatPhone = formatPhoneNo(textMsgPh1);
  quoted.stg(formatPhone);

  quoted.stg(mbrRcd->eMail);

  quoted.stg(rcd.multilingual);

  s.clear();
  if (!rcd.handHeld.isEmpty())   {                                s += _T("HT: ")    + rcd.handHeld;}
  if (!rcd.portMobile.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Port: ")  + rcd.portMobile;}
  if (!rcd.portPacket.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Pkt: ")   + rcd.portPacket;}
  if (!rcd.otherEquip.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Other: ") + rcd.otherEquip;}
  quoted.stg(s);

  quoted.stg(rcd.otherEquip);

  quoted.stg(rcd.comments);

  quoted.noComma();

  s = mbrRcd->lastName + _T(" - ") + rcd.callSign;  if (workAddr) s += _T(" - Wrk");

  quoted.stg(s);

  notePad << nCrlf;
  }


String GoogleRpt::formatPhoneNo(String& ph) {
int    lng;
String area;
String prefix;
String no;

  if (ph.isEmpty()) return ph;

  lng = ph.length();

  if (lng >= 10) {
    area = ph.substr(0,3); prefix = ph.substr(3,3); no = ph.substr(6);
    String s = area + _T('.') + prefix + _T('.') + no;
    return s;
    }
  if (lng == 7) {
    prefix = ph.substr(0,3); no = ph.substr(3);
    String s = prefix + _T('.') +  no;
    return s;
    }
  return ph;
  }


String  GoogleRpt::formatZip(String& zip) {
int    lng = zip.length();
String s;

  switch (lng) {
    case 5  : return zip;
    case 9  : s = zip.substr(0, 5) + _T("-") + zip.substr(5);  return s;
    default : return zip;
    }
  }



bool GoogleRpt::addrAvail(EntRcd* rcd, AdrRcd*& addrRcd) {

  if (!rcd) return false;

  addrRcd = adrTbl.find(rcd->addrID);

  return addrRcd && (!addrRcd->address1.isEmpty() || rcd->addrIsPO);
  }


void GoogleRpt::entityOut(EntRcd* rcd, AdrRcd*& addrRcd) {
CtyRcd* cityRcd = ctyTbl.find(rcd->cityStID);
String        s;

  if (rcd->addrIsPO) {
    s.clear();
    if (!cityRcd->city.isEmpty())                                     s += cityRcd->city;
    if (!cityRcd->state.isEmpty())   {if (!s.isEmpty()) s += _T(" "); s += cityRcd->state;}
    if (!rcd->locationZip.isEmpty()) {if (!s.isEmpty()) s += _T(" "); s += formatZip(rcd->locationZip);}

    quoted.stg(s);
    }

  else {
    s.clear();
    if (addrRcd) s += addrRcd->address1;

    if (cityRcd) {
      s += cityRcd->city.isEmpty()  ? String(_T(", San Jose")) : _T(", ") + cityRcd->city;
      s += cityRcd->state.isEmpty() ? String(_T(" CA"))        : _T(" ")  + cityRcd->state;
      if (cityRcd->zip)                             s += _T(" ")  + formatZip(cityRcd->zip);
      }
    quoted.stg(s);
    }

  s = formatPhoneNo(rcd->phone2);   quoted.stg(s);
  s = formatPhoneNo(rcd->phone1);   quoted.stg(s);
  }





#if 0
#include "AddressTbl.h"
#include "AssgnPrefTbl.h"
#include "CityStateTbl.h"
#include "EntityTbl.h"
#include "LocationPrefTbl.h"
#include "MemberTbl.h"
#include "StatusTbl.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"
#endif

