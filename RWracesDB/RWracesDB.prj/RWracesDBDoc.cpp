// RWracesDBDoc.cpp : implementation of the RWracesDBDoc class
//

#include "stdafx.h"
#include "RWracesDBDOC.h"
#include "CntResponders.h"
#include "DataBase.h"
#include "DeadRcds.h"
#include "Everbridge.h"
#include "FCClist.h"
#include "GetPathDlg.h"
#include "GoogleRpt.h"
#include "MemberRpts.h"
#include "MapData.h"
#include "Options.h"
#include "resource.h"
#include "Resources.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"
#include "StatusUpdate.h"
//#include "Survey.h"
//#include "UpdateRequest.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};
enum ShowFeeType {NilShowFee, StableStable, StableTack, StableBedding, StableOther, OtherFees};


IMPLEMENT_DYNCREATE(RWracesDBDoc, CDocument)

BEGIN_MESSAGE_MAP(RWracesDBDoc, CDocument)

  ON_COMMAND(ID_OpenDatabase,   &openDatabase)

  ON_COMMAND(ID_Status,         &OnLoadCSVfile)
  ON_COMMAND(ID_LoadCSVfile,    &OnLoadCSVfile)
  ON_COMMAND(ID_UploadToDB,     &OnUploadToDB)

  ON_COMMAND(ID_ExcelReport,    &OnExcelReport)
  ON_COMMAND(ID_GoogleEarth,    &OnGoogleEarth)
  ON_COMMAND(ID_Everbridge,     &OnEverbridge)
  ON_COMMAND(ID_CntResponders,  &OnCountResponders)
  ON_COMMAND(ID_FCC,            &OnFCCcallSigns)
  ON_COMMAND(ID_MemberIDs,      &OnMemberInfo)

  ON_COMMAND(ID_Badges,         &OnBadgesCS)
  ON_COMMAND(ID_BadgesCS,       &OnBadgesCS)
  ON_COMMAND(ID_BadgesDate,     &OnBadgesDT)

  ON_COMMAND(ID_FormerNm,       &OnFormerNm)
  ON_COMMAND(ID_Former,         &OnFormerNm)
  ON_COMMAND(ID_FormerCS,       &OnFormerCS)

  ON_COMMAND(ID_FILE_SAVE,      &OnFileSave)

  ON_COMMAND(ID_Backup,         &OnBackup)
  ON_COMMAND(ID_Restore,        &OnRestoreNew)
  ON_COMMAND(ID_Comparison,     &OnComparison)

  ON_COMMAND(ID_Options,        &OnOptions)

  ON_COMMAND(ID_FixDeadRcds,    &OnFixDeadRcds)
END_MESSAGE_MAP()


RWracesDBDoc::RWracesDBDoc() : dataSource(NotePadSrc)               //, surveyCmd(0)
                              {defaultExtension = _T("Save Files|*.csv|All Files|*.*||");   getTitle();}


void RWracesDBDoc::getTitle() {CString  ttl;   ttl.LoadString(AFX_IDS_APP_TITLE); title = ttl;}


void RWracesDBDoc::openDatabase() {
String title;
String ext;

  notePad.clear();

  if (getPathDlg(_T("Database"), 0, _T("accdb"), _T("*.accdb"), theApp.databasePath))
                                       iniFile.writeString(FileSection, DBFileKey, theApp.databasePath);

  maps.initializeMaps(DBFileKey, theApp.databasePath);   display(NotePadSrc);
  }


void RWracesDBDoc::OnExcelReport() {
MemberRpts memberRpts(ExcelDspType);

  setFileSaveAttr(_T("Excel"), _T("csv"));   memberRpts.excel();   invalidate();
  }


void RWracesDBDoc::OnComparison() {
MemberRpts memberRpts(CmpDspType);

  setFileSaveAttr(_T("Comparison"), _T("csv"));   memberRpts.comparison();  invalidate();
  }


void RWracesDBDoc::OnBackup() {
MemberRpts dspMbrRcd(BkupDspType);

  setFileSaveAttr(_T("Backup"), _T("csv"));   dspMbrRcd.backup();   invalidate();
  }


void RWracesDBDoc::OnRestoreNew() {
DataBase db(BkupDspType);   dataSource = RestoreSrc;

  if (!getPathDlg(_T("Restore Database from csv File"), 0, _T("csv"), _T("*.csv"), path) ||
                                                                           !OnOpenDocument(path)) return;
  db.restore();   theApp.announceFinish();
  }


void RWracesDBDoc::OnGoogleEarth() {
GoogleRpt rpt(ExcelDspType);

  setFileSaveAttr(_T("Google Report"), _T("csv"));   rpt();   invalidate();
  }


void RWracesDBDoc::OnEverbridge() {
Everbridge rpt(ExcelDspType);

  setFileSaveAttr(_T("Everbridge"), _T("csv"));   rpt();   invalidate();
  }


void RWracesDBDoc::OnCountResponders()
        {CntResponders rpt;  setFileSaveAttr(_T("ResponderCounts"), _T("txt"));   rpt();   invalidate();}


void RWracesDBDoc::OnFCCcallSigns()
          {FCClist fccList;   setFileSaveAttr(_T("CallSigns"), _T("txt"));    fccList();   invalidate();}


#if 0
void RWracesDBDoc::OnUpdateRequest()
              {UpdateRequest rpt;   setFileSaveAttr(_T("Updates"), _T("txt"));   rpt();   invalidate();}


void RWracesDBDoc::OnSurveyRequest() {
String path;

  surveyCmd = new SurveyCommand;

  setFileSaveAttr(_T("Survey"), _T("txt"));

  if (getPathDlg(_T("Load Filter"), 0, _T("txt"), _T("*.txt"), path))
                                            {setDataSrc(FilterSrc);   if (!OnOpenDocument(path)) return;}

  (*surveyCmd)();  delete surveyCmd; surveyCmd = 0; invalidate();
  }
#endif

void RWracesDBDoc::OnMemberInfo() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("MemberInfo"), _T("txt"));   rpt.info();  invalidate();
  }


void RWracesDBDoc::OnBadgesCS() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("BadgesByCallSign"), _T("txt"));   rpt.badgesCS();  invalidate();
  }


void RWracesDBDoc::OnBadgesDT() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("BadgesByDate"), _T("txt"));   rpt.badgesDT();  invalidate();
  }


void RWracesDBDoc::OnFormerNm() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("FormerByName"), _T("txt"));   rpt.formerNm();  invalidate();
  }


void RWracesDBDoc::OnFormerCS() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("FormerByCallSign"), _T("txt"));   rpt.formerCS();  invalidate();
  }



void RWracesDBDoc::OnLoadCSVfile() {
String       path;
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;

  if (getPathDlg(_T("Status Update csv File"), 0, _T("csv"), _T("*.csv"), path)) {OnOpenDocument(path);}

  stsUpdt.isLoaded();   invalidate();
  }


void RWracesDBDoc::OnUploadToDB() {
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;   stsUpdt.toDatabase();   theApp.announceFinish();

  setFileSaveAttr(_T("StatusUpdate"), _T("txt"));   invalidate();
  }


void RWracesDBDoc::OnFixDeadRcds()
  {DeadRcds deadRcds;setFileSaveAttr(_T("DeadFields"), _T("txt"));     deadRcds.fix(); invalidate();}


void RWracesDBDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void RWracesDBDoc::OnOptions() {
  options(view());
  view()->setOrientation(options.orient);
  }


void RWracesDBDoc::OnFileSave() {
String fileName = theApp.databasePath;
int    pos      = fileName.find_last_of('\\');
String ext      = _T("*.") + fileType;

  fileName = fileName.substr(pos+1);   pos = fileName.find_first_of(_T('.'));
  fileName = fileName.substr(0, pos);   fileName += sffx;

  if (getSaveAsPathDlg(_T("Output File"), fileName, fileType, ext, filePath)) OnSaveDocument(filePath);
  }


// RWracesDBDoc serialization

void RWracesDBDoc::serialize(Archive& ar) {

  if (ar.isStoring()) notePad.archive(ar);

  else
    switch(dataSource) {
    case RestoreSrc : {DataBase db(BkupDspType);  db.load(ar); return;}
    case StsUpdtSrc : {StatusUpdate stsUpdt; stsUpdt.load(ar);  return;}
    }
  }




// RWracesDBDoc diagnostics

#ifdef _DEBUG

void RWracesDBDoc::AssertValid() const {CDocument::AssertValid();}


void RWracesDBDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}

#endif //_DEBUG



#if 0
void RWracesDBDoc::OnIDlist() {
MemberRpts rpt(ExcelDspType);

  setFileSaveAttr(_T("IDlist"), _T("txt"));   rpt.idList();  invalidate();
  }
#endif

