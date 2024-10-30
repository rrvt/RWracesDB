// Status Update -- Update Database from MemberStatus downloaded from Google Files


#include "pch.h"
#include "StatusUpdate.h"
#include "Database.h"
#include "GetPathDlg.h"
#include "RacesDB.h"
#include "StatusRcds.h"


bool StatusUpdate::isLoaded() {
int noRcds = noRecords();

  notePad << nCrlf << _T("Number of Status CSV Records: ") << noRcds << nCrlf << nCrlf;

  return noRcds > 0;
  }


int StatusUpdate::noRecords() {
SRcdIter   iter(statusRcds);
CSVstsRcd* rcd;
int        i;

  for (i = 0, rcd = iter(); rcd; i++, rcd = iter++) if (rcd->callSign.isEmpty()) break;

  return i;
  }



void StatusUpdate::load(Archive& ar) {
String line;
int    pos;

  while (ar.read(line)) {
    pos = line.find(_T(','));
    if (pos > 0 && line.substr(0,pos) == _T("<Start of Data>")) break;
    }

  statusRcds.load(ar); return;
  }


void StatusUpdate::store(TCchar* path) {
SRcdIter   iter(statusRcds);
CSVstsRcd* rcd;
int        pos;

  noUpdates = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    String& callSign = rcd->callSign;

    pos = callSign.find(_T(' '));   if (pos > 0 && callSign.substr(0, pos) == _T("Active")) break;

    if (!rcd->callSign.empty()) uploadOneStsCSV(*rcd);
    }

  mbrTbl.store(path);

  notePad << nFSize(16.0) << nCenter;

  if (noUpdates) {notePad << noUpdates << _T(" Update");    if (noUpdates > 1) notePad << _T("s");}
  else            notePad << _T("No Updates");
  notePad << nFont  << nCrlf;
  }


static String Act = _T("Act");
static String InA = _T("InA");
static String fmr = _T("Fmr");


void StatusUpdate::uploadOneStsCSV(CSVstsRcd& csv) {
MbrRcd* rcd   = mbrTbl.find(csv.callSign);
uint    x;
int     cnt   = csv.activityCnt.stoi(x);
String  abbr  = x > 0 && cnt > 0 ? Act : InA;
long    stsID = stsTbl.find(abbr)->getId();
long    fmrID = stsTbl.find(fmr)->getId();

  if (!rcd)
    {notePad << _T("Call Sign: ") << csv.callSign << _T(" not found in database") << nCrlf; return;}

  if (rcd->statusID != stsID) {

    long orgStsID = rcd->statusID;
    bool fmrMbr   = orgStsID == fmrID;

    if (!fmrMbr) {rcd->statusID = stsID;   rcd->setDirty();   noUpdates++;}

    dspMemberName(rcd);   notePad << nTab << _T("Status");

    StsRcd* stsRcd = stsTbl.find(orgStsID);

    notePad << nTab << stsRcd->abbreviation << nTab << _T("->") << nTab << abbr;

    if (fmrMbr) notePad << nTab << _T("Not Changed");

    notePad << nCrlf;
    }

  if (rcd->textMsgPh1.empty()) {

    dspMemberName(rcd);

    notePad << nTab << _T("Text Message Field") << nTab << nTab << nTab << _T("*** Not Set ***");
    notePad << nCrlf;
    }
  }


void StatusUpdate::dspMemberName(MbrRcd* rcd) {
EntRcd* entity = entTbl.find(rcd->mbrEntityID);

  if (entity) dspRcdName(entity);
  else notePad << _T("Unknown");

  setDspTabs(notePad);
  }


void StatusUpdate::setDspTabs(NotePad& np)
      {np << nClrTabs << nSetTab(35) << nSetTab(50) << nSetTab(58) << nSetTab(63) << nSetTab(70);}


void StatusUpdate::dspRcdName(EntRcd* entity) {

  notePad << entity->firstName << _T(" ");

  if (!entity->middleInitial.empty()) notePad << entity->middleInitial << _T(" ");

  notePad << entity->lastName;
  }



