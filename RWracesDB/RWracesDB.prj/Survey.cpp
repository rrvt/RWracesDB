// Survey

// for all members produce the body of an eMail that requests an update contact information.


#include "stdafx.h"
#include "Survey.h"
#include "Archive.h"
#include "GetPathDlg.h"
#include "MemberList.h"
#include "RWracesDB.h"
#include "RWracesDBDOC.h"
#include "RWracesDBView.h"



#if 0
<name>:

When an event occurs the Chief Radio Officer (CRO) may need to assign
tasks to members of the San Jose Radio Amateur Civil Emergency Service
(SJ RACES) quickly.  The contents of the database give the CRO
the current location and contact information for each member.  To ensure
that the database contains the correct information we ask that you return
this eMail promptly with or without corrections.

Corrections may be made by replacing an underline segment with a correction
in a reply to sender.

* Do you wish to continue as a member of San Jose Radio Amateur Civil
Emergency Service     (Y/N) ______

* Availability: <data> ____________
The choices for Availability are:

   P - RACES is first call, ready to be dispatched immediately
   E - RACES is second call, ready to be dispatched immediately
   G - Will probably respond, may take some time to assemble equipment
   A - ARES only
   L - Last resort resource

* Locality: <data>  ____________
The choices for Locality are:

   A - Available to be dispatched anywhere needed
   5 - Available to be dispatched within 5 miles of location
   1 - Available to be dispatched within 1 mile of location
   N - Available to accept assignments in neighborhood
   O - Not available for RACES dispatch.

* Primary Cell Phone: <data> ______________    Text Msg OK (Y/N) ___
* Secondary Cell Phone: <data> _____________   Text Msg OK (Y/N) ___
* Primary Land Line Phone: <data> ____________
* Secondary Land Line Phone: <data> ___________
* Primary eMail Address: <data>  __________________________________________________
* Secondary eMail Address: <data> __________________________________________________
* Home Address: <data> _____________________________________________________________
* Work (daytime) Address: <data> _________________________________________________________
* Current Equipment/Capabilities: <data> ________________________________________________________



Thanks,

Bob Van Tuyl
Membership

#endif

static int LineWidth     = 100;
static int PrefixWidth   = 32;
static String Blanks     = _T("                                                                       ");
static String UnderScore = _T("_______________________________________________________________________");


static String keys[5] = {_T("P"),
                         _T("E"),
                         _T("G"),
                         _T("A"),
                         _T("L")
                         };

static String locPref[5] = {_T("A"),
                            _T("5"),
                            _T("1"),
                            _T("N"),
                            _T("O")
                            };





void SurveyCommand::operator() () {
MemberList    ml(EverbridgeSrt);
MbrIter       iter(ml);
MemberRecord* rcd;
int           i;
int           n;

  notePad.clear();  view()->setFont(_T("Arial"), 120);

  for (i = 0, n = 0; i < idList.end(); i++) if (!idList[i].check) n++;

  notePad << _T("No of Survey Requests: ") << n << nCrlf << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    if (surveyDone(rcd->CallSign)) continue;

    Survey survey(rcd);    survey.request();
    }
  }


void SurveyCommand::load(Archive& ar) {
int    i;
String line;

  for (i = 0; ar.read(line); i++) if (i) getItem(line);

  return;
  }


void SurveyCommand::getItem(String& line) {
IDitem  item;
int     x;
int     y;
String  s;

  y = line.find(_T(','));   if (y < 0) return;
  s = line.substr(0, y);    s.trim();   item.name = s;

  x = y + 1; y = line.find(_T(','), x);   if (y < 0) return;
  s = line.substr(x, y-x);    s.trim();   item.callSign = s;

  x = y + 1; y = line.find(_T(':'), x);   if (y < 0) return;
  s = line.substr(x, y-x);    s.trim();   item.badgeNumber = s;

  x = y + 1; s = line.substr(x);  s.trim();  item.check = !s.isEmpty();

  idList += item;
  }


bool SurveyCommand::surveyDone(String& callSign) {
int i;
int n = idList.end();

  for (i = 0; i < n; i++) {
    IDitem& item = idList[i];

    if (item.callSign == callSign) return item.check;
    }

  return false;
  }




class SrvyLine {
int prfxWidth;
int stgWidth;

public:

int pos;

  SrvyLine() : pos(0), prfxWidth(PrefixWidth), stgWidth(0) { }
 ~SrvyLine() { }

  void setPrefixWidth(int w) {prfxWidth = w;}
  void prefix(TCchar* pf);
  void stg(String& s);
  void tchar(TCchar* tc);
  void underscore(int w = 0);
  void crlf() {notePad << nCrlf; pos = 0;}
  };




void Survey::request() {
int                 mbrID             = rcd.MbrEntityID;
int                 emplID            = rcd.EmplEntityID;
int                 assgnPrefID       = rcd.AssgnPrefID;
int                 locPrefID         = rcd.LocationPrefID;
int                 statusID          = rcd.StatusID;
String              responder         = rcd.Responder.trim();
String              dsw               = rcd.DSWDate.trim();

EntityRecord*       mbrRcd            = entityTable.find(mbrID);      if (!mbrRcd) return;
EntityRecord*       emplRcd           = entityTable.find(emplID);
AssgnPrefRecord*    assgnPrefRcd      = assgnPrefTable.find(assgnPrefID);
LocationPrefRecord* locationPrefRcd   = locationPrefTable.find(locPrefID);
String              s;

//if (mbrRcd->LastName != _T("Buder")) return;

  dspeMail(mbrRcd, mbrRcd->eMail);
  dspeMail(mbrRcd, rcd.SecondaryEmail);
  if (emplRcd) dspeMail(mbrRcd, emplRcd->eMail);

  notePad << _T("SJ RACES Biennial Membership Attribute Survey, 2020 Version") << nCrlf << nCrlf;

  notePad << mbrRcd->FirstName << _T(":") << nCrlf << nCrlf;

  notePad << _T("When an event occurs the Chief Radio Officer (CRO) may need to assign ");
  notePad << _T("tasks to members of the San Jose Radio Amateur Civil Emergency Service ");
  notePad << _T("(SJ RACES) quickly.  The contents of the database give the CRO ");
  notePad << _T("the current location and contact information for each member.  To ensure ");
  notePad << _T("that the database contains the correct information we ask that you return ");
  notePad << _T("this eMail promptly with or without corrections. ");
  notePad << nCrlf << nCrlf;
  notePad << _T("Corrections may be made by replacing an underline segment with a correction ");
  notePad << _T("in a reply to sender. ");
  notePad << nCrlf << nCrlf;
  notePad << _T("* Do you wish to continue as a member of San Jose Radio Amateur Civil ");
  notePad << _T("Emergency Service? (Y/N) _____");
  notePad << nCrlf << nCrlf;

  s = assgnPrefRcd ? assgnPrefRcd->APKey + _T(" - ") + assgnPrefRcd->Txt : _T("U - Not Specified");

  SrvyLine avLn;  avLn.setPrefixWidth(15);
  avLn.prefix(_T("Availability:")); avLn.stg(s); avLn.underscore(); avLn.crlf();

  notePad << _T("The choices for Availability are:") << nCrlf;
  notePad << _T("   P - RACES is first call, ready to be dispatched immediately") << nCrlf;
  notePad << _T("   E - RACES is second call, ready to be dispatched immediately") << nCrlf;
  notePad << _T("   G - Will probably respond, may take some time to assemble equipment") << nCrlf;
  notePad << _T("   A - ARES only") << nCrlf;
  notePad << _T("   L - Last resort resource") << nCrlf;
  notePad << nCrlf;

  s = locationPrefRcd ? locationPrefRcd->Key + _T(" - ") + locationPrefRcd->Txt : _T("U - Not Specified");

  avLn.prefix(_T("Locality:")); avLn.stg(s); avLn.underscore(); avLn.crlf();
  notePad << _T("The choices for Locality are:") << nCrlf;
  notePad << _T("   A - Available to be dispatched anywhere needed") << nCrlf;
  notePad << _T("   5 - Available to be dispatched within 5 miles of location") << nCrlf;
  notePad << _T("   1 - Available to be dispatched within 1 mile of location") << nCrlf;
  notePad << _T("   N - Available to accept assignments in neighborhood") << nCrlf;
  notePad << _T("   O - Not available for RACES dispatch.") << nCrlf;
  notePad << nCrlf;

  SrvyLine phLn;

  phone(_T("* Primary Cell Phone:"),        mbrRcd,  true,  phLn);
  phone(_T("* Secondary Cell Phone:"),      emplRcd, true,  phLn);
  phone(_T("* Primary Land Line Phone:"),   mbrRcd,  false, phLn);
  phone(_T("* Secondary Land Line Phone:"), emplRcd, false, phLn);

  SrvyLine emLn;
  int mLng = mbrRcd  ? mbrRcd->eMail.length()  : 0;
  int eLng = emplRcd ? emplRcd->eMail.length() : 0;
  int maxLng = mLng > eLng ? mLng : eLng;   if (!maxLng) maxLng = 25;

  eMail(_T("* Primary eMail Address:  "),   mbrRcd,  maxLng, emLn);
  eMail(_T("* Secondary eMail Address:  "), emplRcd, maxLng, emLn);


  SrvyLine adLn;
  addr(_T("* Home Address:  "),            mbrRcd,  adLn);
  addr(_T("* Work (daytime) Address:  "),  emplRcd, adLn);
  notePad << nCrlf;

  notePad << _T("Equipment/Other Capabilities") << nCrlf;
  equip(_T("Hand Held:           "), HandHeldData);
  equip(_T("Port/Mobile:         "), PortMobileData);
  equip(_T("Port Packet:         "), PortPacketData);
  equip(_T("Other Equip:         "), OtherEquipData);
  equip(_T("Other Capabilities:  "), OtherCapData);
  notePad << nCrlf;

  notePad << _T("Thanks,") << nCrlf;
  notePad << nCrlf;
  notePad << _T("Bob Van Tuyl") << nCrlf;
  notePad << _T("Membership Officer, K6RWY") << nCrlf;
  notePad << _T("--------------------------") << nCrlf << nCrlf;
  }


void Survey::dspeMail(EntityRecord* mbrRcd, String& eMail) {
String s = eMail;  s.trim();

  if (s.isEmpty()) return;

  notePad << mbrRcd->FirstName << _T(" ") << mbrRcd->LastName;
  notePad << _T(" <") << s << _T("> ") << nCrlf;
  }


//TextMsgPh1

void Survey::phone(TCchar* prefix, EntityRecord* eRcd, bool cellPh, SrvyLine& sl) {
String s;
int    lng;
String t;

  if (eRcd) {

    s = cellPh ? eRcd->Phone2 : eRcd->Phone1;   s.trim();

    lng = s.length();

    if      (lng ==  7) t = s.substr(0, 3) + _T(".") + s.substr(3);
    else if (lng == 10) t = s.substr(0, 3) + _T(".") + s.substr(3, 3) + _T(".") + s.substr(6);
    else                t = _T("            ");

//    srvyPrefix(prefix);   notePad << t;   srvyUnderscore(20);
    sl.prefix(prefix); sl.stg(t); sl.underscore(20);

    if (cellPh) {
      bool txtOK = false;
      if (!eRcd->Phone2.isEmpty()) {
        if (eRcd->Phone2 == rcd.TextMsgPh1) txtOK = true;
        if (eRcd->Phone2 == rcd.TextMsgPh2) txtOK = true;
        }

      sl.tchar(_T("   Text Msg OK (Y/N)"));
      if (txtOK) sl.tchar(_T("   __Y__"));
      else       sl.underscore(5);
      }

    sl.crlf();
    }
  }


void Survey::eMail(TCchar* prefix, EntityRecord* eRcd, int  width, SrvyLine& sl) {
String s   = eRcd ? eRcd->eMail : _T("");;
int    lng = s.length();

  s += Blanks.substr(0, width-lng);

  sl.prefix(prefix);   sl.stg(s);   sl.underscore();  sl.crlf();
  }


void Survey::addr(TCchar* prefix, EntityRecord* eRcd, SrvyLine& sl) {
int              id;
AddressRecord*   addrRcd;
CityStateRecord* cityStRcd;
String           s;
String           zip;

  sl.prefix(prefix);

  if (eRcd) {
    id = eRcd->AddrID;    addrRcd   = addressTable.find(id);
    id = eRcd->CityStID;  cityStRcd = cityStateTable.find(id);

    if (eRcd->AddrIsPO) zip = eRcd->LocationZip;

    if (addrRcd) {
      s = addrRcd->Address1;   s.trim();

      if (cityStRcd) {

        if (!s.isEmpty())                s += _T(", ");
        if (!cityStRcd->City.isEmpty())  s += cityStRcd->City + _T(", ");
        if (!cityStRcd->State.isEmpty()) s += cityStRcd->State + _T(" ");

        if (!eRcd->AddrIsPO) zip = cityStRcd->Zip;
        }

      zip.trim();
      if (zip.length() > 5) zip = zip.substr(0, 5) + _T("-") + zip.substr(5);
      if (!zip.isEmpty()) s += zip;
      }
    }

  sl.stg(s);   sl.underscore();   sl.crlf();
  }


void Survey::equip(TCchar* prefix, EquipData equipData) {
String      s;
SrvyLine dl;

  switch (equipData) {
    case HandHeldData   : s = rcd.HandHeld;          break;
    case PortMobileData : s = rcd.PortMobile;        break;
    case PortPacketData : s = rcd.PortPacket;        break;
    case OtherEquipData : s = rcd.OtherEquip;        break;
    case OtherCapData   : s = rcd.OtherCapabilities; break;
    }

  s.trim();

  dl.prefix(prefix);   if (s.length()) dl.stg(s);   dl.underscore(LineWidth-PrefixWidth);   dl.crlf();
  }


void SrvyLine::prefix(TCchar* pf) {
String s   = pf;
int    lng = s.length();

  pos = prfxWidth;

  s += Blanks.substr(0, prfxWidth-lng);  notePad << s;
  }


void SrvyLine::stg(String& s) {
String t = s;
String u;
int    lng;
int    i;
int    j;
int    k;
int    spaceX;
int    commaX;

  while ((j = t.find(_T('\n'))) >= 0)
                          {u = t.substr(j+1);   t = t.substr(0, j);   t = t.trim() + _T(' ') + u.trim();}

  if (prfxWidth + t.length() >= LineWidth) {
    for (i = 0; prfxWidth + t.length() >= LineWidth; i++) {
      spaceX = 0;    commaX = 0;

      for (j = 0, k = t.find(_T(' ')); k >= 0 && prfxWidth + k < LineWidth;
                                                              j = k, k = t.find(_T(' '), k+1)) continue;
      spaceX = j;

      for (j = 0, k = t.find(_T(',')); k >= 0 && prfxWidth + k + 1 < LineWidth;
                                                              j = k, k = t.find(_T(','), k+1)) continue;
      commaX = j + 1;

      if (spaceX > commaX + 20) {u = t.substr(0, spaceX); t = t.substr(spaceX);}
      else if (commaX)          {u = t.substr(0, commaX); t = t.substr(commaX);}
      else if (spaceX)          {u = t.substr(0, spaceX); t = t.substr(spaceX);}
      else {j = LineWidth - pos; u = t.substr(0, j);      t = t.substr(j);}

      if (i) {crlf();  notePad << Blanks.substr(0, prfxWidth);   pos = prfxWidth;}

      notePad << u;   t.trim();   pos += u.length();
      }

    lng = t.length();

    if (lng) {
      if (i) {crlf();  notePad << Blanks.substr(0, prfxWidth);   pos = prfxWidth;}

      notePad << t;  stgWidth = lng;   pos += stgWidth;    if (pos + 40 >= LineWidth) pos = LineWidth;
      }
    }

  else {
    lng = t.length();

    if (lng > stgWidth) stgWidth = lng;

    if (lng < stgWidth) t += Blanks.substr(0, stgWidth-lng);

    notePad << t;   pos += stgWidth;
    }
  }


void SrvyLine::tchar(TCchar* tc) {int lng = _tcslen(tc);   pos += lng;   notePad << tc;}



void SrvyLine::underscore(int w) {
int n = w ? w : LineWidth - pos - 3;
String s;

  if (!pos) prefix(_T(""));

  if (pos + w + 3 > LineWidth) n = LineWidth - pos - 3;

  if ((w > 0 && w <= LineWidth - pos - 3) || n >= 5) {s = UnderScore.substr(0, n); notePad << _T("   ");}
  else {crlf(); s = Blanks.substr(0, PrefixWidth) + UnderScore.substr(0, LineWidth-PrefixWidth);}

  notePad << s;
  }

