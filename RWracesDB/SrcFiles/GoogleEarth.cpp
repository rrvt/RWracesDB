// Display Google Earth Records


#include "stdafx.h"
#include "RWracesDBDoc.h"
#include "MessageBox.h"
#include "NotePad.h"


//Name,Call,Status,Type,Disp Priority,Disp Location,Limitations,
//Address,Cell,Phone,SMS Text,Email,Languages,
//Equipment,
//Other,Comments,geLabel

//"Anderson, Craig ",N6YXK,Active," Responder, DSW on file",ARES Only,Anywhere in city,,
//"14656 Bronson Avenue, San Jose CA 95124",408-768-6025,408-371-8904,408-768-6025,acraiga@pacbell.net,,
//"HT:(1-6m(5w), 3-2m(5w), 2-70cm(5w), 1-23cm(1w)) Prtable:(1-2m(50w), 1-70cm(20w), 1-HF(100w)) Pkt:(mobile) Other:(WiFi, APRS, )",
//"APRS-capable, WiFi",Packet Manager; Missing certs.,"Anderson, N6YXK"


void RWracesDBDoc::dspGoogleHeader() {

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


void RWracesDBDoc::dspOneGoogleRcd(MemberRecord& rcd, bool workAddr) {
int                 mbrID             = rcd.MbrEntityID;
int                 emplID            = rcd.EmplEntityID;
int                 assgnPrefID       = rcd.AssgnPrefID;
int                 locPrefID         = rcd.LocationPrefID;
int                 statusID          = rcd.StatusID;
String              responder         = rcd.Responder.trim();
String              dsw               = rcd.DSWDate.trim();

EntityRecord*       mbrRcd            = entityTable.find(mbrID);      if (!mbrRcd) return;
EntityRecord*       emplRcd           = entityTable.find(emplID);
AddressRecord*      addrRcd;
//CityStateRecord*    cityRcd           = cityStateTable.find(mbrRcd->CityStID);

AssgnPrefRecord*    assgnPrefRcd      = assgnPrefTable.find(assgnPrefID);
LocationPrefRecord* locationPrefRcd   = locationPrefTable.find(locPrefID);
StatusRecord*       statusRcd         = statusTable.find(statusID);
String              s;
String              addrType          = workAddr ? _T("Work") : _T("Home");

EntityRecord* r     = workAddr ? emplRcd : mbrRcd;
bool          avail = addrAvail(r, addrRcd);

  if (workAddr && !avail) return;

  commaOut();

if (rcd.CallSign == _T("KC6THM")) {
int x = 1;
}

  quoteStrOut(rcd.CallSign);

  s = mbrRcd->FirstName + _T(' ') + mbrRcd->LastName;
  if (!mbrRcd->Suffix.isEmpty()) s += mbrRcd->Suffix;
  quoteStrOut(s);

  if (statusRcd) {
    s = statusRcd->Abbreviation == "Act" ? _T("Active") : _T("Inactive");
    quoteStrOut(s);
    }
  else notePad << _T(",");

  s =  responder.isEmpty() ? _T("non-Responder") : _T("Responder");
  s += dsw.isEmpty()       ? _T(" - No DSW")     : _T(" - DSW");
  quoteStrOut(s);

  if (assgnPrefRcd) {
    s = assgnPrefRcd->APKey;
    if      (s == _T("P")) s = _T("1st Call");
    else if (s == _T("E")) s = _T("not 1st Call");
    else if (s == _T("G")) s = _T("General");
    else if (s == _T("L")) s = _T("Last Call");
    else if (s == _T("A")) s = _T("ARES Only");
    else                   s = assgnPrefRcd->Txt;
    quoteStrOut(s);
    }
  else notePad << _T("ARES Only,");

  if (locationPrefRcd) {
    s = locationPrefRcd->Key;
    if      (s == _T("A")) s = _T("Anywhere in city");
    else if (s == _T("5")) s = _T("Within 5 miles");
    else if (s == _T("1")) s = _T("Within 1 mile");
    else if (s == _T("N")) s = _T("Within neighborhood");
    else                   s = locationPrefRcd->Txt;
    quoteStrOut(s);
    }
  else notePad << _T("Anywhere,");

  quoteStrOut(rcd.Limitations);

  quoteStrOut(addrType);

  entityOut(r, addrRcd);

  quoteStrOut(formatPhoneNo(rcd.TextMsgPh1));

  quoteStrOut(mbrRcd->eMail);

  quoteStrOut(rcd.Multilingual);

  s.clear();
  if (!rcd.HandHeld.isEmpty())   {                                s += _T("HT: ")    + rcd.HandHeld;}
  if (!rcd.PortMobile.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Port: ")  + rcd.PortMobile;}
  if (!rcd.PortPacket.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Pkt: ")   + rcd.PortPacket;}
  if (!rcd.OtherEquip.isEmpty()) {if (!s.isEmpty()) s+= _T("; "); s += _T("Other: ") + rcd.OtherEquip;}
  quoteStrOut(s);

  quoteStrOut(rcd.OtherEquip);

  quoteStrOut(rcd.Comments);

  noComma();

  s = mbrRcd->LastName + _T(" - ") + rcd.CallSign;  if (workAddr) s += _T(" - Wrk");

  quoteStrOut(s);

  notePad << nCrlf;
  }


String RWracesDBDoc::formatPhoneNo(String& ph) {
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


String  RWracesDBDoc::RWracesDBDoc::formatZip(String& zip) {
int    lng = zip.length();
String s;

  switch (lng) {
    case 5  : return zip;
    case 9  : s = zip.substr(0, 5) + _T("-") + zip.substr(5);  return s;
    default : return zip;
    }
  }



bool RWracesDBDoc::addrAvail(EntityRecord* rcd, AddressRecord*& addrRcd) {

  if (!rcd) return false;

  addrRcd = addressTable.find(rcd->AddrID);

  return addrRcd && (!addrRcd->Address1.isEmpty() || rcd->AddrIsPO);
  }


void RWracesDBDoc::entityOut(EntityRecord* rcd, AddressRecord*& addrRcd) {
CityStateRecord* cityRcd = cityStateTable.find(rcd->CityStID);
String           s;

  if (rcd->AddrIsPO) {
    s.clear();
    if (!cityRcd->City.isEmpty())                                     s += cityRcd->City;
    if (!cityRcd->State.isEmpty())   {if (!s.isEmpty()) s += _T(" "); s += cityRcd->State;}
    if (!rcd->LocationZip.isEmpty()) {if (!s.isEmpty()) s += _T(" "); s += formatZip(rcd->LocationZip);}

    quoteStrOut(s);
    }

  else {
    s.clear();
    if (addrRcd) s += addrRcd->Address1;

    if (cityRcd) {
      s += cityRcd->City.isEmpty()  ? _T(", San Jose") : _T(", ") + cityRcd->City;
      s += cityRcd->State.isEmpty() ? _T(" CA")        : _T(" ")  + cityRcd->State;
      if (cityRcd->Zip)                             s += _T(" ")  + formatZip(cityRcd->Zip);
      }
    quoteStrOut(s);
    }

  quoteStrOut(formatPhoneNo(rcd->Phone2));
  quoteStrOut(formatPhoneNo(rcd->Phone1));
  }
