// RWracesDB.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "RWracesDB.h"
#include "AboutDlg.h"
#include "Database.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MainFrame.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Resources.h"
#include "RWracesDBDOC.h"
#include "RWracesDBView.h"


RWracesDB theApp;                    // The one and only RWracesDB object
IniFile      iniFile;


BEGIN_MESSAGE_MAP(RWracesDB, CWinAppEx)
  ON_COMMAND(ID_Refresh,          &refresh)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_APP_ABOUT,        &OnAppAbout)
END_MESSAGE_MAP()


BOOL RWracesDB::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.getAppDataPath(m_pszHelpFilePath);

  programName = getMainName(m_pszHelpFilePath);

  SetRegistryKey(appID);

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

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;  ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("RacesDB"));    setTitle(_T("Database Manipulation Program"));

  notePad.clear();   view()->setFont(_T("Arial"), 12.0);

  doc()->initDatabase();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void RWracesDB::refresh() {  }


void RWracesDB::announceFinish() {
  notePad << nFSize(16.0) << nCenter << _T("Upload Completed") << nFont << nCrlf;   invalidate();
  }


void RWracesDB::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void RWracesDB::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

