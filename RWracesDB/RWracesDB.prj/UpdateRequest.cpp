// Update Request

// for all members that have reached responder status produce the body of an eMail that request an
// update of their Availability (Assignment Pref) and Prefered Locality (Location Pref.


#include "stdafx.h"
#include "UpdateRequest.h"
#include "MapData.h"
#include "MemberList.h"
#include "NotePad.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"


void UpdateRequest::operator() () {
MemberList    ml(EverbridgeSrt);
MbrIter       iter(ml);
MemberRecord* rcd;

  notePad.clear();   view()->setFont(_T("Arial"), 120);

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;
    if (responder.isEmpty()) continue;
    if (rcd->IsOfficer) continue;

    display(*rcd);
    }
  }



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



void UpdateRequest::display(MemberRecord& rcd) {
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
StatusRecord*       statusRcd         = statusTable.find(statusID);
String              key;
String              s;
int                 i;

  notePad << _T("SJ RACES Availability and Locality of Service") << nCrlf << nCrlf;

  notePad << mbrRcd->FirstName << _T(":") << nCrlf << nCrlf;
  notePad << _T("It has come to my attention that I have been remiss in asking each new ");
  notePad << _T("responder their preferences for Availability and Locality during an emergency.  ");
  notePad << _T("Please review the following data which is now in the database and respond by eMail ");
  notePad << _T("with changes.  No response will be interpreted as there being no changes.  ");
  notePad << _T("The options are list below.") << nCrlf << nCrlf;

  notePad << mbrRcd->FirstName << _T(" ") << mbrRcd->LastName << nCrlf;

  s = assgnPrefRcd ? assgnPrefRcd->APKey + _T(" - ") + assgnPrefRcd->Txt : _T("U - Not Specified");

  notePad << _T("Availability: ") << s << nCrlf;

  s = locationPrefRcd ? locationPrefRcd->Key + _T(" - ") + locationPrefRcd->Txt : _T("U - Not Specified");

  notePad << _T("Locality:      ") << s << nCrlf << nCrlf;

  notePad << _T("The choices for Availability are:") << nCrlf << nCrlf;

  for (i = 0; i < noElements(keys); i++) {
    AssgnPrefRecord* r = findAvail(keys[i]);
    if (!r) continue;
    notePad << _T("   ") << r->APKey << _T(" - ") << r->Txt << nCrlf;
    }
  notePad << nCrlf;

  notePad << _T("The choices for Locality are:") << nCrlf << nCrlf;

  for (i = 0; i < noElements(locPref); i++) {
    LocationPrefRecord* r = findLoc(locPref[i]);
    if (!r) continue;
    notePad << _T("   ") << r->Key << _T(" - ") << r->Txt << nCrlf;
    }

  notePad << nCrlf;

  notePad << _T("Thank you,") << nCrlf << nCrlf;

  notePad << _T("Bob Van Tuyl") << nCrlf;
  notePad << _T("Membership Officer, K6RWY") << nCrlf;
  notePad << _T("--------------------------") << nCrlf << nCrlf;
  }


AssgnPrefRecord* UpdateRequest::findAvail(TCchar* key) {
AgPfIter         iter(assgnPrefTable);
AssgnPrefRecord* r;

  for (r = iter(); r; r = iter++) if (r->APKey == key) return r;

  return 0;
  }



LocationPrefRecord* UpdateRequest::findLoc(TCchar* key) {
LcPfIter            iter(locationPrefTable);
LocationPrefRecord* r;

  for (r = iter(); r; r = iter++) if (r->Key == key) return r;

  return 0;
  }


