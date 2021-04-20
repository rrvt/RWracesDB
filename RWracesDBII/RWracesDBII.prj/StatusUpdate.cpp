// Status Update -- Update Database from MemberStatus downloaded from Google Files


#include "stdafx.h"
#include "StatusUpdate.h"
#include "EntityTbl.h"
#include "GetPathDlg.h"
#include "MemberTbl.h"
#include "RWracesDB.h"
#include "StatusRcds.h"
#include "StatusTbl.h"


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



void StatusUpdate::load(Archive& ar) {statusRcds.load(ar); return;}


void StatusUpdate::store() {
SRcdIter   iter(statusRcds);
CSVstsRcd* rcd;

  noUpdates = 0;

  rcd = iter();  if (rcd->callSign == _T("CallSign")) rcd = iter++;

  for ( ; rcd; rcd = iter++) if (!rcd->callSign.empty()) uploadOneStsCSV(*rcd);

  memberTbl.store();

  notePad << nFSize(16.0) << nCenter;

  if (noUpdates) {notePad << noUpdates << _T(" Update");    if (noUpdates > 1) notePad << _T("s");}
  else            notePad << _T("No Updates");
  notePad << nFont  << nCrlf;
  }


static String fmr = _T("Fmr");


void StatusUpdate::uploadOneStsCSV(CSVstsRcd& csv) {
MemberRcd* rcd        = memberTbl.find(csv.callSign);
String     abbr       = csv.activeStatus;
long       stsID      = statusTbl.find(abbr)->id;
long       fmrID      = statusTbl.find(fmr)->id;
bool       csvBadgeOK = csv.eligibleForBadge == _T("Yes");

  if (!rcd)
    {notePad << _T("Call Sign: ") << csv.callSign << _T(" not found in database") << nCrlf; return;}

  if (rcd->statusID != stsID) {                            //  && rcd->statusID <= noStsRcd

    long orgStsID = rcd->statusID;
    bool fmrMbr   = orgStsID == fmrID;

    if (!fmrMbr) {rcd->statusID = stsID;   rcd->mark();   noUpdates++;}

    dspMemberName(rcd);   notePad << nTab << _T("Status");
                                                                      // statusTbl.findAbbr(orgStsID)
    StatusRcd* stsRcd = statusTbl.find(orgStsID);

    notePad << nTab << stsRcd->abbreviation << nTab << _T("->") << nTab << abbr;

    if (fmrMbr) notePad << nTab << _T("Not Changed");

    notePad << nCrlf;
    }

  if (rcd->badgeOK != csvBadgeOK) {

    bool orig = rcd->badgeOK;

    rcd->badgeOK = csvBadgeOK; rcd->mark(); noUpdates++;

    dspMemberName(rcd);

    notePad << nTab << _T("Badge OK") << nTab << orig << nTab << _T("->") << nTab << rcd->badgeOK;
    notePad << nCrlf;
    }

  if (rcd->textMsgPh1.empty()) {

    dspMemberName(rcd);

    notePad << nTab << _T("Text Message Field") << nTab << nTab << nTab << _T("*** Not Set ***");
    notePad << nCrlf;
    }
  }


void StatusUpdate::dspMemberName(MemberRcd* rcd) {
EntityRcd* entity = entityTbl.find(rcd->mbrEntityID);

  if (entity) dspRcdName(entity);
  else notePad << _T("Unknown");

  setDspTabs(notePad);
  }


void StatusUpdate::setDspTabs(NotePad& np)
        {np << nClrTabs << nSetTab(35) << nSetTab(50) << nSetTab(58) << nSetTab(63) << nSetTab(70);}


void StatusUpdate::dspRcdName(EntityRcd* entity) {

  notePad << entity->firstName << _T(" ");

  if (!entity->middleInitial.empty()) notePad << entity->middleInitial << _T(" ");

  notePad << entity->lastName;
  }




