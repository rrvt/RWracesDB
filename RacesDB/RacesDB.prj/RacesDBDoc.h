// RacesDBDOC.h : interface of the RacesDBDOC class

#pragma once
#include "CDoc.h"

//class  SurveyCommand;


enum DataSource {NotePadSrc, RestoreSrc, StsUpdtSrc};


class RacesDBDOC : public CDoc {

DataSource  dataSource;

String      title;

bool        dbLoaded;
String      dbPath;
String      sffx;             // Suffix of <dbName><sffx>.<fileType>
String      fileType;

protected: // create from serialization only

  RacesDBDOC();
  DECLARE_DYNCREATE(RacesDBDOC)

public:

  virtual ~RacesDBDOC() {};

          void setDataSrc(DataSource ds) {dataSource = ds;}
    DataSource dataSrc() {return dataSource;}

          void initDatabase();

          void display(DataSource ds);

          void setFileSaveAttr(TCchar* suffix, TCchar* ext) {sffx = suffix; fileType = ext;}

          void getTitle();

  virtual void serialize(Archive& ar);

private:

  void loadDatabase();

protected:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void openDatabase();
  afx_msg void OnBackup();
  afx_msg void OnLoadCSVfile();
  afx_msg void OnUploadToDB();
  afx_msg void OnRestoreNew();
  afx_msg void OnExcelReport();
  afx_msg void OnGoogleEarth();
  afx_msg void OnEverbridge();
  afx_msg void OnCountResponders();
  afx_msg void OnFCCcallSigns();
  afx_msg void OnMemberInfo();
  afx_msg void OnBadgesDT();
  afx_msg void OnBadgesCS();
  afx_msg void OnFormerCS();
  afx_msg void OnFormerNm();
  afx_msg void OnComparison();
  afx_msg void OnFixDeadRcds();
  afx_msg void onFileSave();
  afx_msg void OnCovidList();
  afx_msg void OnMakeFileCopy();
  };


