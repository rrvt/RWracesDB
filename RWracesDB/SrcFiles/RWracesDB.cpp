// RWracesDB.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "RWracesDB.h"
#include "About.h"
#include "RWracesDBDOC.h"
#include "RWracesDBView.h"
#include "Copyfile.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MapData.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Resources.h"
#include <filesystem>


RWracesDBApp theApp;                    // The one and only RWracesDBApp object
IniFile iniFile;


BEGIN_MESSAGE_MAP(RWracesDBApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT,        &RWracesDBApp::OnAppAbout)
  ON_COMMAND(ID_OpenDatabase,     &RWracesDBApp::openDatabase)
  ON_COMMAND(ID_Refresh,          &RWracesDBApp::refresh)

  // Standard print setup command
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)

  ON_COMMAND(ID_LoadCSVfile,      &RWracesDBApp::OnLoadCSVfile)
  ON_COMMAND(ID_UploadToDB,       &RWracesDBApp::OnUploadToDB)

  ON_COMMAND(ID_MakeFileCopy,     &RWracesDBApp::OnMakeFileCopy)
END_MESSAGE_MAP()


// RWracesDBApp construction

RWracesDBApp::RWracesDBApp() : doc(0), view(0) {
ResourceData res;
String       appID;

  if (res.getAppID(appID)) SetAppID(appID);
  }




BOOL RWracesDBApp::InitInstance() {

  CWinApp::InitInstance();

  iniFile.getAppDataPath(m_pszHelpFilePath);        //  iniFile.setPath(m_pszHelpFilePath);
  programName = getMainName(m_pszHelpFilePath);


  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(RWracesDBDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(RWracesDBView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  iniFile.readString(FileSection, DBFileKey,      databasePath);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;  ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("RacesDB"));
  setTitle(_T("Database Manipulation Program"));

  notePad.clear();

  maps.initializeMaps(DBFileKey, databasePath);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void RWracesDBApp::openDatabase() {
String title;
String ext;

  notePad.clear();

  if (getPathDlg(_T("Database"), 0, _T("accdb"), _T("*.accdb"), databasePath))
                                            iniFile.writeString(FileSection, DBFileKey, databasePath);

  maps.initializeMaps(DBFileKey, databasePath);   invalidate();
  }


void RWracesDBApp::refresh() {maps.initializeMaps(DBFileKey, databasePath);}



void RWracesDBApp::OnMakeFileCopy() {
String path;
String destinationFile;
String ext;
int    pos;

  if (!getPathDlg(_T("Copy Database"), databasePath, _T("accdb"), _T("*.accdb"), path)) return;

  pos = path.find_last_of(_T('.'));   if (pos < 0) pos = path.size();
  ext = path.substr(pos);
  destinationFile = path.substr(0, pos);   destinationFile += _T(" - Copy");   destinationFile += ext;

  if (!copyFile(path, destinationFile)) return;

  if (ext == ".accdb") {
    iniFile.writeString(FileSection, DBFileKey, destinationFile);

    maps.initializeMaps(DBFileKey, databasePath);
    }
  }


void RWracesDBApp::announceFinish() {
  notePad << nFSize(160) << nCenter << _T("Upload Completed") << nFont << nCrlf;   invalidate();
  }


void RWracesDBApp::invalidate() {if (getView()) view->Invalidate();}


bool RWracesDBApp::getView() {
POSITION   pos;

  if (view) return true;

  if (!getDocument()) return false;

  pos  = doc->GetFirstViewPosition();        if (!pos)  return false;
  view = (RWracesDBView*) doc->GetNextView(pos);

  return view != 0;
  }



bool RWracesDBApp::getDocument() {

  if (doc) return true;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return false;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return false;

  pos = t->GetFirstDocPosition();                    if (!pos) return false;
  doc = (RWracesDBDoc*) t->GetNextDoc(pos);              if (!doc) return false;

  return true;
  }


void RWracesDBApp::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}
