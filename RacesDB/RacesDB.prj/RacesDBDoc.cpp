// RacesDBDOC.cpp : implementation of the RacesDBDOC class
//

#include "pch.h"
#include "RacesDBDOC.h"
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
#include "RacesDB.h"
#include "RacesDBView.h"
#include "StatusUpdate.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};
enum ShowFeeType {NilShowFee, StableStable, StableTack, StableBedding, StableOther, OtherFees};

static TCchar* FileSection = _T("FileSection");
static TCchar* DBFileKey   = _T("DBfile");


IMPLEMENT_DYNCREATE(RacesDBDOC, CDocument)

BEGIN_MESSAGE_MAP(RacesDBDOC, CDocument)

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

  ON_COMMAND(ID_FILE_SAVE,      &onFileSave)

  ON_COMMAND(ID_MakeFileCopy,   &OnMakeFileCopy)
  ON_COMMAND(ID_Backup,         &OnBackup)
  ON_COMMAND(ID_Restore,        &OnRestoreNew)
  ON_COMMAND(ID_Comparison,     &OnComparison)

  ON_COMMAND(ID_FixDeadRcds,    &OnFixDeadRcds)
END_MESSAGE_MAP()


RacesDBDOC::RacesDBDOC() : dataSource(NotePadSrc), dbLoaded(false) {getTitle();}


void RacesDBDOC::getTitle() {CString  ttl;   ttl.LoadString(AFX_IDS_APP_TITLE); title = ttl;}


void RacesDBDOC::initDatabase() {

  if (!iniFile.readString(FileSection, DBFileKey, path)) return;

  loadDatabase();
  }


void RacesDBDOC::openDatabase() {
PathDlgDsc dsc(_T("Database"), 0, _T("accdb"), _T("*.accdb"));

  notePad.clear();

  if (!setOpenPath(dsc)) return;

  iniFile.writeString(FileSection, DBFileKey, path);   loadDatabase();
  }


void RacesDBDOC::loadDatabase() {

  dbLoaded = database.load(path);

  notePad << _T("Database at ") << path << (dbLoaded ? _T(" Loaded") : _T(" Not Loaded"));
  notePad << nCrlf;

  if (dbLoaded) {dbPath = path; mbrSortList.create();}

  display(NotePadSrc);
  }


void RacesDBDOC::OnExcelReport() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Excel"), _T("csv"));   memberRpts.excel();      display(NotePadSrc);
  }


void RacesDBDOC::OnCovidList() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CovidList"), _T("csv"));   memberRpts.covidList();      display(NotePadSrc);
  }


void RacesDBDOC::OnComparison() {
MemberRpts memberRpts(CmpDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Comparison"), _T("csv"));   memberRpts.comparison();     display(NotePadSrc);
  }


void RacesDBDOC::OnMakeFileCopy() {
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
    }
  }


void RacesDBDOC::OnBackup() {
MemberRpts dspMbrRcd(BkupDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Backup"), _T("csv"));   dspMbrRcd.backup();      display(NotePadSrc);
  }


void RacesDBDOC::OnRestoreNew() {display(NotePadSrc);}


void RacesDBDOC::OnGoogleEarth() {
GoogleRpt rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Google Report"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RacesDBDOC::OnEverbridge() {
Everbridge rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Everbridge"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RacesDBDOC::OnCountResponders() {
CntResponders rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("ResponderCounts"), _T("txt"));   rpt();    display(NotePadSrc);
  }


void RacesDBDOC::OnFCCcallSigns() {
FCClist fccList;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CallSigns"), _T("txt"));    fccList();      display(NotePadSrc);
  }



void RacesDBDOC::OnMemberInfo() {
InfoRpts rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("MemberInfo"), _T("txt"));   rpt.info();  display(NotePadSrc);
  }


void RacesDBDOC::OnBadgesCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByCallSign"), _T("txt"));   rpt.dspBadges(BdgFCCSort);;

  display(NotePadSrc);
  }


void RacesDBDOC::OnBadgesDT() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByDate"), _T("txt"));   rpt.dspBadges(BdgDateSort);

  display(NotePadSrc);
  }


void RacesDBDOC::OnFormerNm() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByName"), _T("txt"));   rpt.former(FmrNameSort);  display(NotePadSrc);
  }


void RacesDBDOC::OnFormerCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByCallSign"), _T("txt"));   rpt.former(FmrFCCSort);

  display(NotePadSrc);
  }



void RacesDBDOC::OnLoadCSVfile() {
PathDlgDsc   dsc(_T("Status Update csv File"), 0, _T("csv"), _T("*.csv"));
String       path;
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;

  if (!setOpenPath(dsc)) return;

  OnOpenDocument(path);

  stsUpdt.isLoaded();   display(NotePadSrc);
  }


void RacesDBDOC::OnUploadToDB() {
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;   stsUpdt.store(path);   theApp.announceFinish();

  setFileSaveAttr(_T("StatusUpdate"), _T("txt"));   display(NotePadSrc);
  }


void RacesDBDOC::OnFixDeadRcds() {
DeadRcds deadRcds;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("DeadFields"), _T("txt"));     deadRcds.fix(path); invalidate();
  }


void RacesDBDOC::display(DataSource ds) {dataSource = ds; invalidate();}


void RacesDBDOC::onFileSave() {
String     name    = getMainName(dbPath) + sffx;
String     pattern = _T("*.") + fileType;
PathDlgDsc dsc(_T("Output File"), name, fileType, pattern);

  if (setSaveAsPath(dsc)) OnSaveDocument(path);
  }


// RacesDBDOC serialization

void RacesDBDOC::serialize(Archive& ar) {

  if (ar.isStoring()) notePad.archive(ar);

  else
    switch(dataSource) {
      case StsUpdtSrc : {StatusUpdate stsUpdt; stsUpdt.load(ar);  return;}
      }
  }




// RacesDBDOC diagnostics

#ifdef _DEBUG
void RacesDBDOC::AssertValid() const          {CDocument::AssertValid();}
void RacesDBDOC::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG



