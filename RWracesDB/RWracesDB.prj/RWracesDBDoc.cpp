// RWracesDBDoc.cpp : implementation of the RWracesDBDoc class
//

#include "pch.h"
#include "RWracesDBDOC.h"
#include "CntResponders.h"
#include "Copyfile.h"
#include "Database.h"
#include "DeadRcds.h"
#include "Everbridge.h"
#include "FileName.h"
#include "FCClist.h"
#include "GetPathDlg.h"
#include "GoogleRpt.h"
#include "MbrInfo.h"
#include "MbrSortList.h"
#include "MemberRpts.h"
#include "Resource.h"
#include "Resources.h"
#include "RWracesDB.h"
#include "RWracesDBView.h"
#include "StatusUpdate.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};
enum ShowFeeType {NilShowFee, StableStable, StableTack, StableBedding, StableOther, OtherFees};

static TCchar* FileSection = _T("FileSection");
static TCchar* DBFileKey   = _T("DBfile");


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

  ON_COMMAND(ID_CovidList,      &OnCovidList)

  ON_COMMAND(ID_FILE_SAVE,      &OnFileSave)

  ON_COMMAND(ID_MakeFileCopy,   &OnMakeFileCopy)
  ON_COMMAND(ID_Backup,         &OnBackup)
  ON_COMMAND(ID_Restore,        &OnRestoreNew)
  ON_COMMAND(ID_Comparison,     &OnComparison)

  ON_COMMAND(ID_FixDeadRcds,    &OnFixDeadRcds)
END_MESSAGE_MAP()


RWracesDBDoc::RWracesDBDoc() : dataSource(NotePadSrc), dbLoaded(false) {getTitle();}


void RWracesDBDoc::getTitle() {CString  ttl;   ttl.LoadString(AFX_IDS_APP_TITLE); title = ttl;}


void RWracesDBDoc::initDatabase() {

  if (!iniFile.readString(FileSection, DBFileKey, path)) return;

  loadDatabase();
  }


void RWracesDBDoc::openDatabase() {
PathDlgDsc dsc(_T("Database"), 0, _T("accdb"), _T("*.accdb"));

  notePad.clear();

  if (!setOpenPath(dsc)) return;

  iniFile.writeString(FileSection, DBFileKey, path);   loadDatabase();
  }


void RWracesDBDoc::loadDatabase() {

  dbLoaded = database.load(path);

  notePad << _T("Database at ") << path << (dbLoaded ? _T(" Loaded") : _T(" Not Loaded"));
  notePad << nCrlf;

  if (dbLoaded) {dbPath = path; mbrSortList.create();}

  display(NotePadSrc);
  }


void RWracesDBDoc::OnExcelReport() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Excel"), _T("csv"));   memberRpts.excel();      display(NotePadSrc);
  }


void RWracesDBDoc::OnCovidList() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CovidList"), _T("csv"));   memberRpts.covidList();      display(NotePadSrc);
  }


void RWracesDBDoc::OnComparison() {
MemberRpts memberRpts(CmpDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Comparison"), _T("csv"));   memberRpts.comparison();     display(NotePadSrc);
  }


void RWracesDBDoc::OnMakeFileCopy() {
PathDlgDsc dsc(_T("Copy Database"), path, _T("accdb"), _T("*.accdb"));
String newPath;
String destinationFile;
String ext;
int    pos;

  if (!getOpenDlg(dsc, newPath)) return;

  pos = newPath.find_last_of(_T('.'));   if (pos < 0) pos = newPath.size();
  ext = newPath.substr(pos);
  destinationFile = newPath.substr(0, pos);   destinationFile += _T(" - Copy");   destinationFile += ext;

  if (!copyFile(newPath, destinationFile)) return;

  if (ext == ".accdb") {
    iniFile.writeString(FileSection, DBFileKey, destinationFile);

//    maps.initializeMaps(DBFileKey, path);
    }
  }


void RWracesDBDoc::OnBackup() {
MemberRpts dspMbrRcd(BkupDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Backup"), _T("csv"));   dspMbrRcd.backup();      display(NotePadSrc);
  }


void RWracesDBDoc::OnRestoreNew() {
#if 1
#else
DB db(BkupDspType);   dataSource = RestoreSrc;

  if (!getPathDlg(_T("Restore Database from csv File"), 0, _T("csv"), _T("*.csv"), path) ||
                                                                           !OnOpenDocument(path)) return;
  db.restore();   theApp.announceFinish();   display(NotePadSrc);
#endif
  display(NotePadSrc);
  }


void RWracesDBDoc::OnGoogleEarth() {
GoogleRpt rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Google Report"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RWracesDBDoc::OnEverbridge() {
Everbridge rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Everbridge"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RWracesDBDoc::OnCountResponders() {
CntResponders rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("ResponderCounts"), _T("txt"));   rpt();    display(NotePadSrc);
  }


void RWracesDBDoc::OnFCCcallSigns() {
FCClist fccList;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CallSigns"), _T("txt"));    fccList();      display(NotePadSrc);
  }



void RWracesDBDoc::OnMemberInfo() {
InfoRpts rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("MemberInfo"), _T("txt"));   rpt.info();  display(NotePadSrc);
  }


void RWracesDBDoc::OnBadgesCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByCallSign"), _T("txt"));   rpt.dspBadges(BdgFCCSort);;  display(NotePadSrc);
  }


void RWracesDBDoc::OnBadgesDT() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByDate"), _T("txt"));   rpt.dspBadges(BdgDateSort);  display(NotePadSrc);
  }


void RWracesDBDoc::OnFormerNm() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByName"), _T("txt"));   rpt.former(FmrNameSort);  display(NotePadSrc);
  }


void RWracesDBDoc::OnFormerCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByCallSign"), _T("txt"));   rpt.former(FmrFCCSort);  display(NotePadSrc);
  }



void RWracesDBDoc::OnLoadCSVfile() {
PathDlgDsc   dsc(_T("Status Update csv File"), 0, _T("csv"), _T("*.csv"));
String       path;
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;

  if (!setOpenPath(dsc)) return;

  OnOpenDocument(path);

  stsUpdt.isLoaded();   display(NotePadSrc);
  }


void RWracesDBDoc::OnUploadToDB() {
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;   stsUpdt.store(path);   theApp.announceFinish();

  setFileSaveAttr(_T("StatusUpdate"), _T("txt"));   display(NotePadSrc);
  }


void RWracesDBDoc::OnFixDeadRcds() {
DeadRcds deadRcds;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("DeadFields"), _T("txt"));     deadRcds.fix(path); invalidate();
  }


void RWracesDBDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void RWracesDBDoc::OnFileSave() {
String     name    = getMainName(dbPath) + sffx;
String     pattern = _T("*.") + fileType;
PathDlgDsc dsc(_T("Output File"), name, fileType, pattern);

  if (setSaveAsPath(dsc)) OnSaveDocument(path);
  }


// RWracesDBDoc serialization

void RWracesDBDoc::serialize(Archive& ar) {

  if (ar.isStoring()) notePad.archive(ar);

  else
    switch(dataSource) {
#if 1
#else
    case RestoreSrc : {DB db(BkupDspType);  db.load(ar); return;}
#endif
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



//#include "DB.h"
//#include "DBtables.h"




#if 1
#else
String     fileName = path;
int        pos      = fileName.find_last_of('\\');
  fileName = fileName.substr(pos+1);   pos = fileName.find_first_of(_T('.'));
  fileName = fileName.substr(0, pos);
#endif
//String     title;
//String     ext;

