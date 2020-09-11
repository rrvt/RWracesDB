// RWracesDBDoc.cpp : implementation of the RWracesDBDoc class
//

#include "stdafx.h"
#include "RWracesDBDOC.h"
#include "Currency.h"
#include "GetPathDlg.h"
#include "RWracesDBView.h"
#include "RWracesDB.h"
#include "MapTable.h"
#include "MapData.h"
#include "MemberList.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "qsort.h"
#include "Records.h"
#include "StatusRcds.h"
#include "Survey.h"
#include "TextPosition.h"
#include "Resources.h"
#include "Utilities.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};
enum ShowFeeType {NilShowFee, StableStable, StableTack, StableBedding, StableOther, OtherFees};


// Local Functions

static long sanitizeBadgeNo(String& bn);

static void dspRcdName(EntityRecord* entity);
static void setDspTabs();


// RWracesDBDoc

IMPLEMENT_DYNCREATE(RWracesDBDoc, CDocument)

BEGIN_MESSAGE_MAP(RWracesDBDoc, CDocument)

  ON_COMMAND(ID_FILE_SAVE,      &RWracesDBDoc::OnFileSave)

  ON_COMMAND(ID_Backup,         &RWracesDBDoc::OnBackup)
  ON_COMMAND(ID_Restore,        &RWracesDBDoc::OnRestoreNew)
  ON_COMMAND(ID_ExcelReport,    &RWracesDBDoc::OnExcelReport)
  ON_COMMAND(ID_GoogleEarth,    &RWracesDBDoc::OnGoogleEarth)
  ON_COMMAND(ID_Everbridge,     &RWracesDBDoc::OnEverbridge)
  ON_COMMAND(ID_CntResponders,  &RWracesDBDoc::OnCountResponders)
  ON_COMMAND(ID_FCC,            &RWracesDBDoc::OnFCCcallSigns)
  ON_COMMAND(ID_UpdateReq,      &RWracesDBDoc::OnUpdateRequest)
  ON_COMMAND(ID_SurveyReq,      &RWracesDBDoc::OnSurveyRequest)
  ON_COMMAND(ID_IDlist,         &RWracesDBDoc::OnIDlist)
  ON_COMMAND(ID_MemberInto,     &RWracesDBDoc::OnMemberInfo)
  ON_COMMAND(ID_Comparison,     &RWracesDBDoc::OnComparison)
  ON_COMMAND(ID_FIX_DEADRCDS,   &RWracesDBDoc::OnFixDeadRcds)
END_MESSAGE_MAP()


// RWracesDBDoc construction/destruction

RWracesDBDoc::RWracesDBDoc() : docType(NilDocType), dspType(NilDspType),
                                       delDSWdates(false), noUpdates(0), addComma(true), surveyCmd(0) {
  notePad.clear(); defaultExtension = _T("Save Files|*.csv|All Files|*.*||");

  getTitle();
  }


void RWracesDBDoc::getTitle() {
CString  ttl;

  ttl.LoadString(AFX_IDS_APP_TITLE); title = ttl;
  }


void RWracesDBDoc::setTitle(TCchar* s) {
CWnd*        wnd = AfxGetMainWnd();   if (!wnd) return;
ResourceData res;
String       t;
String       pn;
String       cn;
String       ds;
String       ver;

  if (s && _tcslen(s)) {t = s; t += _T(":");}

  if (res.getProductName(pn)) {
    if (!t.empty()) t += _T(" / ") + pn;
    else            t = pn;
    }

  if (res.getCompanyName(cn))     t += _T(" / ") + cn;
  if (res.getFileDescription(ds)) t += _T(" / ") + ds;
  if (res.getVersion(ver))        t += _T(" / ") + ver;

  wnd->SetWindowText(t);
  }


void RWracesDBDoc::OnExcelReport() {
MmbrIter      iter(memberTable);
MemberRecord* rcd;

  setFileSaveAttr(_T("Excel"), _T("csv"));

  dspRecordHeader();

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    dspOneRecord(*rcd, ExcelDspType);
    }

  invalidate();
  }


void RWracesDBDoc::OnGoogleEarth() {
MemberList    ml(GoogleEarth);
MbrIter       iter(ml);
MemberRecord* rcd;

  setFileSaveAttr(_T("GoogleEarth"), _T("csv"));   dspType = ExcelDspType;

  dspGoogleHeader();

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    dspOneGoogleRcd(*rcd, false);
    dspOneGoogleRcd(*rcd, true);
    }

  invalidate();
  }



void RWracesDBDoc::OnEverbridge() {
MemberList    ml(Everbridge);
MbrIter       iter(ml);
MemberRecord* rcd;

  setFileSaveAttr(_T("Everbridge"), _T("csv"));   dspType = ExcelDspType;

  ebHeader();

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    dspOneEverbridgeRcd(*rcd);
    }

  invalidate();
  }


static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };



void RWracesDBDoc::OnCountResponders() {
MmbrIter         iter(memberTable);
MemberRecord*    rcd;
int              assgnPrefID;
AssgnPrefRecord* assgnPrefRcd;
String           key;
String           dsc;
int              i;
int              counts[6];
int              total;

  setFileSaveAttr(_T("ResponderCounts"), _T("txt"));   dspType = ExcelDspType;

  notePad.clear();

  for (i = 0; i < noElements(counts); i++) counts[i] = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    assgnPrefID  = rcd->AssgnPrefID;
    assgnPrefRcd = assgnPrefTable.find(assgnPrefID);
    if (!assgnPrefRcd) {counts[5]++; continue;}

    key = assgnPrefRcd->APKey;

    for (i = 0; i < noElements(counts); i++) {
      if (i >= noElements(keys) || key == keys[i]) {counts[i]++; break;}
      }
    }

  notePad << nSetRTab(72);   total = 0;

  for (i = 0; i < noElements(counts); i++) {
    String k     = i < noElements(keys) ? keys[i] : _T("Nuts");
    assgnPrefRcd = assgnPrefTable.find(assgnPrefTable.findID(k));
    dsc          = assgnPrefRcd ? assgnPrefRcd->Txt : _T("Other");

    notePad << dsc << nTab << counts[i] << nCrlf;    total += counts[i];
    }

  notePad << nTab << _T("------") << nCrlf;
  notePad << _T("   Total") << nTab << total << nCrlf;

  invalidate();
  }


void RWracesDBDoc::OnFCCcallSigns() {
MmbrIter                iter(memberTable);
MemberRecord*           rcd;
int                     i;
int                     nCallSigns;
Expandable<String, 128> callSigns;

  setFileSaveAttr(_T("CallSigns"), _T("txt"));

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    callSigns += rcd->CallSign;        //[callSigns.end()]
    }
  nCallSigns = callSigns.end();

  qsort(&callSigns[0], &callSigns[nCallSigns-1]);

  notePad.clear();

  for (i = 0; i < nCallSigns; i++) notePad << callSigns[i] << nCrlf;

  invalidate();
  }



void RWracesDBDoc::OnUpdateRequest() {
MemberList    ml(Everbridge);
MbrIter       iter(ml);
MemberRecord* rcd;

  setFileSaveAttr(_T("Updates"), _T("txt"));   dspType = ExcelDspType;

  notePad.clear();

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);
    String        responder = rcd->Responder.trim();

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;
    if (responder.isEmpty()) continue;
    if (rcd->IsOfficer) continue;

    UpdateRequest(*rcd);
    }

  invalidate();
  }


void RWracesDBDoc::OnSurveyRequest() {
  surveyCmd = new SurveyCommand(*this);

  surveyCmd->doIt();

  delete surveyCmd; surveyCmd = 0;

  invalidate();
  }


void RWracesDBDoc::OnMemberInfo() {
MmbrIter                      iter(memberTable);
MemberRecord*                 rcd;
int                           i;
int                           n;
Expandable<MemberInfo, 2> members;

  setFileSaveAttr(_T("MemberInfo"), _T("txt"));

  for (rcd = iter(), i = 0; rcd; rcd = iter++) {
    MemberInfo memberInfo;
    if (!getMemberInfo(*rcd, memberInfo)) continue;
    members[i] = memberInfo;  i++;
    }

  n = members.end();   qsort(&members[0], &members[n-1]);   notePad.clear();
  notePad.clear();

  for (i = 0; i < n; i++) {
    MemberInfo& mi = members[i];

    notePad << mi.callSign    << _T(",");
    notePad << mi.firstName   << _T(",");
    notePad << mi.lastName    << _T(",");
    notePad << mi.badgeNumber << nCrlf;
    }
  invalidate();
  }



void RWracesDBDoc::OnIDlist() {
MmbrIter                iter(memberTable);
MemberRecord*           rcd;
int                     i;
int                     n;
Expandable<IDitem, 128> idList;

  setFileSaveAttr(_T("IDlist"), _T("txt"));

  for (rcd = iter(); rcd; rcd = iter++) {
    MemberInfo memberInfo;
    if (!getMemberInfo(*rcd, memberInfo)) continue;

    IDitem& item     = idList.nextData();
    item.name        = memberInfo.lastName + memberInfo.firstName;
    item.callSign    = memberInfo.callSign;
    item.badgeNumber = memberInfo.badgeNumber;
    }

  n = idList.end();   qsort(&idList[0], &idList[n-1]);   notePad.clear();

  notePad << nSetTab(26) << nSetRTab(45) << nSetTab(47);

  notePad << _T("Name")     << nTab << _T("Call Sign") << nTab;
  notePad << _T("Badge") << nTab << _T("Responded") <<  nCrlf;

  for (i = 0; i < n; i++) {
    IDitem& item = idList[i];
    notePad <<         item.name        << _T(",");
    notePad << nTab << item.callSign    << _T(",");
    notePad << nTab << item.badgeNumber << _T(":") << nCrlf;
    }

  invalidate();
  }


bool RWracesDBDoc::getMemberInfo(MemberRecord& rcd, MemberInfo& memberInfo) {
  int           statusID  = rcd.StatusID;
  StatusRecord* statusRcd = statusTable.find(statusID);

  if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) return false;
  EntityRecord* mbrRcd = entityTable.find(rcd.MbrEntityID);   if (!mbrRcd) return false;

  memberInfo.lastName  = mbrRcd->LastName;   memberInfo.lastName.trim();
  memberInfo.firstName = mbrRcd->FirstName;  memberInfo.firstName.trim();

  memberInfo.callSign    = rcd.CallSign;    memberInfo.callSign.trim();
  memberInfo.badgeNumber = rcd.BadgeNumber; memberInfo.badgeNumber.trim();

  return true;
  }



void RWracesDBDoc::OnComparison() {
MmbrIter      iter(memberTable);
MemberRecord* rcd;
bool          saveFile = false;

  setFileSaveAttr(_T("Comparison"), _T("csv"));

  dspRecordHeader(true);

  for (rcd = iter(); rcd; rcd = iter++) {dspOneRecord(*rcd, CmpDspType); saveFile = true;}

  invalidate();

  if (saveFile) OnFileSave();
  }






void RWracesDBDoc::OnFileSave() {
String fileName = theApp.databasePath;
int    pos      = fileName.find_last_of('\\');
String ext      = _T("*.") + fileType;

  fileName = fileName.substr(pos+1);
  pos = fileName.find_first_of(_T('.'));   fileName = fileName.substr(0, pos);   fileName += sffx;

  if (getSaveAsPathDlg(_T("Output File"), fileName, fileType, ext, filePath)) OnSaveDocument(filePath);
  }


// RWracesDBDoc serialization

void RWracesDBDoc::serialize(Archive& ar) {

  if (ar.isStoring()) notePad.archive(ar);

  else if (docType == RestoreDocType) {loadBackupData(ar);}

  else if (docType == StatusDocType) {statusRcds.load(ar);
    }

  else if (docType == FilterDocType) {
    int    i;
    String line;

    if (!surveyCmd) return;

    for (i = 0; ar.read(line); i++) if (i) surveyCmd->getItem(line);
    }
  }


// Set flag so that updating db will delete DSW dates.

void RWracesDBDoc::FixDSWdates() {
  delDSWdates = MessageBox(0, _T("Delete DSW Dates in all records?"), _T("Delete DSW"),
                                      MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING|MB_ICONEXCLAMATION) == IDYES;
  }



void RWracesDBDoc::deleteDSWdates() {
long          fmrID       = statusTable.findID(String(_T("Fmr")));
MmbrIter      iter(memberTable);
MemberRecord* rcd;
String        oldDSW;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->StatusID == fmrID) continue;

    oldDSW = rcd->DSWDate;

    rcd->DSWDate.clear();

    if (rcd->DSWDate != oldDSW) {
      rcd->mark(); noUpdates++;

      dspMemberName(rcd);   notePad << nTab << _T("DSW Date") << nTab << _T("Cleared") << nCrlf;
      }
    }
  }


void RWracesDBDoc::dspMemberName(MemberRecord* rcd) {
EntityRecord* entity = entityTable.find(rcd->MbrEntityID);
  if (entity) dspRcdName(entity);
  else notePad << _T("Unknown");

  setDspTabs();
  }



void dspRcdName(EntityRecord* entity) {
  notePad << entity->FirstName << _T(" ");
  if (!entity->MiddleInitial.empty()) notePad << entity->MiddleInitial << _T(" ");
  notePad << entity->LastName;
  }


void setDspTabs()
        {notePad << nClrTabs << nSetTab(35) << nSetTab(50) << nSetTab(58) << nSetTab(63) << nSetTab(70);}







long find(EntityRecord& r) {
EntyIter      iter(entityTable);
EntityRecord* rcd;

  if (isEmpty(&r.FirstName, &r.LastName, &r.LocationZip, &r.eMail, 0)) return 0;

  r.LocationZip = sanitizeZip(r.LocationZip);

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->FirstName == r.FirstName &&
        rcd->LastName  == r.LastName  &&
        rcd->AddrID    == r.AddrID    &&
        rcd->Phone1    == r.Phone1    &&
        rcd->eMail     == r.eMail)
      return rcd->EntityID;
    }
  r.mark();

  return 0;
//  return entityTable.addRecord(r);   // Study Later
  }



void RWracesDBDoc::quoteStrOut(String& s) {
int    i;
int    lng = s.size();
Tchar  ch;
String t;

  if (!lng) notePad << _T("\" \"");

  else {
    for (i = 0; i < lng; i++) {
      ch = s[i];

      if      (ch == _T('"')) t += _T('"');

      switch (dspType) {
        case CmpDspType   :
        case ExcelDspType : if (ch == _T('\r')) continue;
                            if (ch == _T('\n')) {t += _T("; "); continue;}
                            break;
        case BkupDspType  : if (ch == _T('\r')) continue;
                            if (ch == _T('\n')) {t += _T("\\\\M"); continue;}
                            break;
        }

      t += ch;
      }

    notePad << _T('"') << t << _T('"');
    }

  if (addComma) notePad << _T(",");
  }


String RWracesDBDoc::quoteStrIn(String& s) {
int    i;
int    lng = s.size();
Tchar  ch;
Tchar  ch1;
String t;

  for (i = 0; i < lng; i++) {
    ch = s[i]; ch1 = i+1 < lng ? s[i+1] : 0;

    if (ch == _T('"') && ch1 == _T('"')) {t += _T('"'); i++; continue;}

    if (dspType == BkupDspType && ch == _T('\\') && ch1 == _T('M')) {t += _T("\r\n"); i++; continue;}

    t += ch;
    }

  return t;
  }



static String zeros = _T("000000");

void RWracesDBDoc::dateOut(String& s) {
int    n;
String t;
String mon;
String day;
String yr;
String d;

  if (dspType == ExcelDspType) {
    n = s.size();
    if (n > 0) {
      t = zeros.substr(0, 6-n) + s;
      mon = t.substr(0,2);
      day = t.substr(2,2);
      yr  = t.substr(4,2);
      d = mon + _T("/") + day + _T("/20") + yr;
      }
    quoteStrOut(d);
    }
  else quoteStrOut(s);
  }


// RWracesDBDoc diagnostics

#ifdef _DEBUG

void RWracesDBDoc::AssertValid() const {CDocument::AssertValid();}


void RWracesDBDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}

#endif //_DEBUG




#if 0
    Csv<512> csv(ar);
    String   nullStg = _T("");
    Token*   tok;
    Token*   tok1;
    bool     keyWord = true;

    csv.set_print_flag(false);

    while (csv.get_token() != EolToken) {
      if (keyWord) {
        keyWord = false;
        if (csv.token->name != _T("CallSign"))
                                      {messageBox(_T("Not an Update File, please try again."));  return;}
        }
      csv.accept_token();
      }

    csv.accept_token(); statusCSV.initialize();

    while (csv.get_token() != EOFToken) {
      tok = csv.token;   tok1 = csv.token1;

      if (tok->code != CommaToken) {
        statusCSV.storeField(tok->code, String(tok->name));
        if (     tok1->code == EolToken) statusCSV.storeField(tok1->code, nullStg);
        else if (tok1->code != CommaToken) {csv.accept_token(); continue;}
        csv.accept_two_tokens(); continue;
        }

      else {
        if (tok1->code != CommaToken)
          {statusCSV.storeField(StringToken, nullStg); csv.accept_token(); continue;}

        if (tok1->code == CommaToken) {

          csv.accept_token(); csv.get_token();

          if (csv.token1->code == EolToken) break;
          }
        }
      }
#endif

