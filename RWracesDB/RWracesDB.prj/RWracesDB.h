// RWracesDB.h : main header file for the RWracesDB application


#pragma once
#include "CApp.h"
#include "IniFile.h"


extern TCchar* GenFilePathKey;

class RWracesDBDoc;
class RWracesDBView;



class RWracesDB : public CApp {

String programName;

public:

//String databasePath;

  RWracesDB() : CApp(this) { }

  virtual BOOL InitInstance();

  void announceFinish();

  RWracesDBDoc*  doc()  {return (RWracesDBDoc*)  CApp::getDoc();}
  RWracesDBView* view() {return (RWracesDBView*) CApp::getView();}

  DECLARE_MESSAGE_MAP()

  afx_msg void refresh();
  afx_msg void OnAppAbout();

  afx_msg void OnHelp();

  friend  RWracesDBDoc* doc();
  };


extern RWracesDB theApp;

inline void           invalidate() {theApp.invalidate();}
inline RWracesDBDoc*  doc()        {return theApp.doc();}
inline RWracesDBView* view()       {return theApp.view();}

