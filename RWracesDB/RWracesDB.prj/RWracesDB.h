// RWracesDB.h : main header file for the RWracesDB application


#pragma once
#include "CApp.h"
#include "IniFile.h"


extern TCchar* GenFilePathKey;

class RWracesDBDoc;
class RWracesDBView;



class RWracesDBApp : public CApp {

String        programName;

public:

String         databasePath;

  RWracesDBApp() { }

  void openDatabase();
  void refresh();

  void announceFinish();

  RWracesDBDoc*  doc()  {return (RWracesDBDoc*)  CApp::getDoc();}
  RWracesDBView* view() {return (RWracesDBView*) CApp::getView();}

  virtual BOOL InitInstance();

  afx_msg void OnAppAbout();
  afx_msg void OnMakeFileCopy();
  afx_msg void OnLoadCSVfile();
  afx_msg void OnUploadToDB();

  DECLARE_MESSAGE_MAP()

  friend  RWracesDBDoc* doc();
  afx_msg void OnFilePrintSetup();
  };


extern RWracesDBApp theApp;

inline void           invalidate() {theApp.invalidate();}
inline RWracesDBDoc*  doc()  {return theApp.doc();}
inline RWracesDBView* view() {return theApp.view();}

