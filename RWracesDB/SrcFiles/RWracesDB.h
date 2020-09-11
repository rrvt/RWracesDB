// RWracesDB.h : main header file for the RWracesDB application
//
#pragma once

#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "IniFile.h"
#include "RWracesDBDOC.h"
#include "MainFrm.h"
#include "MapTable.h"


extern TCchar* GenFilePathKey;


class RWracesDBView;



class RWracesDBApp : public CWinApp {

RWracesDBDoc* doc;
String        programName;

public:

RWracesDBView* view;
String         databasePath;

  RWracesDBApp();

  void openDatabase();
  void refresh();

  void announceFinish();

  bool getDocument();
  void invalidate();
  bool getView();

  virtual BOOL InitInstance();

  void setAppName(TCchar* appName) {getMainFrame()->setAppName(appName);}   // Title left part
  void setTitle(TCchar* rightPart) {getMainFrame()->setTitle(rightPart);}    // title right part

  afx_msg void OnAppAbout();
  afx_msg void OnMakeFileCopy();
  afx_msg void OnLoadCSVfile();
  afx_msg void OnUploadToDB();

  DECLARE_MESSAGE_MAP()

  friend  RWracesDBDoc* doc();
  afx_msg void OnFilePrintSetup();

private:

  MainFrame* getMainFrame() {return (MainFrame*) m_pMainWnd;}
  };


extern RWracesDBApp theApp;


inline void          invalidate() {theApp.invalidate();}
inline RWracesDBDoc* doc() {return theApp.getDocument() ? theApp.doc : 0;}
