// Update Database from Status file


#include "stdafx.h"
#include "RWracesDB.h"
#include "GetPathDlg.h"
#include "Utilities.h"
#include "StatusRcds.h"


void RWracesDBApp::OnLoadCSVfile() {
String path;

  if (getPathDlg(_T("Status Update csv File"), 0, _T("csv"), _T("*.csv"), path) && getDocument())
                                    {doc->setDocType(StatusDocType); doc->OnOpenDocument(path);}

  notePad << _T("Number of Status CSV Records: ") << doc->noStatusCSV() << nCrlf;
  invalidate();
  }


void RWracesDBApp::OnUploadToDB() {
  if (getDocument()) doc->uploadStsCSV();

  announceFinish();
  }




void RWracesDBDoc::uploadStsCSV() {
StsIter    iter(statusRcds);
StatusRcd* rcd;

  noUpdates = 0;

  rcd = iter();  if (rcd->callSign == _T("CallSign")) rcd = iter++;

  for ( ; rcd; rcd = iter++) if (!rcd->callSign.empty()) uploadOneStsCSV(*rcd);

  memberTable.toDatabase();

  notePad << nFSize(160) << nCenter;

  if (noUpdates) {notePad << noUpdates << _T(" Update");    if (noUpdates > 1) notePad << _T("s");}
  else            notePad << _T("No Updates");
  notePad << nFont  << nCrlf;
  }


String fmr = _T("Fmr");


void RWracesDBDoc::uploadOneStsCSV(StatusRcd& csv) {
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
    notePad << nTab << statusTable.findAbbr(orgStsID) << nTab << _T("->") << nTab << abbr;

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

