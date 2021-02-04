// Status Update -- Update Database from MemberStatus downloaded from Google Files


#include "stdafx.h"
#include "StatusUpdate.h"
#include "GetPathDlg.h"
#include "MapData.h"
#include "RWracesDB.h"
#include "StatusRcds.h"


bool StatusUpdate::isLoaded() {
int    noRcds = noRecords();

  notePad << nCrlf << _T("Number of Status CSV Records: ") << noRcds << nCrlf << nCrlf;

  return noRcds > 0;
  }


int StatusUpdate::noRecords() {
StsIter    iter(statusRcds);
StatusRcd* rcd;
int        i;

  for (i = 0, rcd = iter(); rcd; i++, rcd = iter++) if (rcd->callSign.isEmpty()) break;

  return i;
  }



void StatusUpdate::load(Archive& ar) {statusRcds.load(ar); return;}


void StatusUpdate::toDatabase() {
StsIter    iter(statusRcds);
StatusRcd* rcd;

  noUpdates = 0;

  rcd = iter();  if (rcd->callSign == _T("CallSign")) rcd = iter++;

  for ( ; rcd; rcd = iter++) if (!rcd->callSign.empty()) uploadOneStsCSV(*rcd);

  memberTable.toDatabase();

  notePad << nFSize(16.0) << nCenter;

  if (noUpdates) {notePad << noUpdates << _T(" Update");    if (noUpdates > 1) notePad << _T("s");}
  else            notePad << _T("No Updates");
  notePad << nFont  << nCrlf;
  }


static String fmr = _T("Fmr");


void StatusUpdate::uploadOneStsCSV(StatusRcd& csv) {
MemberRecord* rcd        = memberTable.get(csv.callSign);
String        abbr       = csv.activeStatus;
long          stsID      = statusTable.findID(abbr);
long          fmrID      = statusTable.findID(fmr);
long          orgStsID;
bool          csvBadgeOK = csv.eligibleForBadge == _T("Yes");
bool          fmrMbr;

  if (!rcd)
    {notePad << _T("Call Sign: ") << csv.callSign << _T(" not found in database") << nCrlf; return;}

  if (rcd->StatusID != stsID) {                            //  && rcd->StatusID <= noStsRcd

    orgStsID = rcd->StatusID;   fmrMbr = orgStsID == fmrID;
    if (!fmrMbr) {rcd->StatusID = stsID;   rcd->mark();   noUpdates++;}

    dspMemberName(rcd);   notePad << nTab << _T("Status");
                                                                      // statusTable.findAbbr(orgStsID)
    StatusRecord* stsRcd = statusTable.find(orgStsID);

    notePad << nTab << stsRcd->Abbreviation << nTab << _T("->") << nTab << abbr;

    if (fmrMbr) notePad << nTab << _T("Not Changed");

    notePad << nCrlf;
    }

  if (rcd->BadgeOK != csvBadgeOK) {
    bool orig = rcd->BadgeOK;
    rcd->BadgeOK = csvBadgeOK; rcd->mark(); noUpdates++;

    dspMemberName(rcd);
    notePad << nTab << _T("Badge OK") << nTab << orig << nTab << _T("->") << nTab << rcd->BadgeOK;
    notePad << nCrlf;
    }

  if (rcd->TextMsgPh1.empty()) {
    dspMemberName(rcd);
    notePad << nTab << _T("Text Message Field") << nTab << nTab << nTab << _T("*** Not Set ***");
    notePad << nCrlf;
    }
  }


void StatusUpdate::dspMemberName(MemberRecord* rcd) {
EntityRecord* entity = entityTable.find(rcd->MbrEntityID);
  if (entity) dspRcdName(entity);
  else notePad << _T("Unknown");

  setDspTabs(notePad);
  }


void StatusUpdate::setDspTabs(NotePad& np)
        {np << nClrTabs << nSetTab(35) << nSetTab(50) << nSetTab(58) << nSetTab(63) << nSetTab(70);}


void StatusUpdate::dspRcdName(EntityRecord* entity) {
  notePad << entity->FirstName << _T(" ");
  if (!entity->MiddleInitial.empty()) notePad << entity->MiddleInitial << _T(" ");
  notePad << entity->LastName;
  }




