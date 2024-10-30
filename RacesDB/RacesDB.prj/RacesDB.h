// RacesDB.h : main header file for the RacesDB application


#pragma once
#include "CApp.h"
#include "IniFile.h"


extern TCchar* GenFilePathKey;

class RacesDBDOC;
class RacesDBView;



class RacesDB : public CApp {

String programName;

public:

//String databasePath;

  RacesDB() : CApp(this) { }

  virtual BOOL InitInstance();

  void announceFinish();

  RacesDBDOC*  doc()  {return (RacesDBDOC*)  CApp::getDoc();}
  RacesDBView* view() {return (RacesDBView*) CApp::getView();}

  DECLARE_MESSAGE_MAP()

  afx_msg void refresh();
  afx_msg void OnAppAbout();

  afx_msg void OnHelp();

  friend  RacesDBDOC* doc();
  };


extern RacesDB theApp;

inline void           invalidate() {theApp.invalidate();}
inline RacesDBDOC*  doc()        {return theApp.doc();}
inline RacesDBView* view()       {return theApp.view();}

