// RWracesDBDOC.h : interface of the RWracesDBDoc class

#pragma once
#include "CDoc.h"

//class  SurveyCommand;


enum DataSource {NotePadSrc, RestoreSrc, StsUpdtSrc};


class RWracesDBDoc : public CDoc {

DataSource  dataSource;

String      title;

String      defaultExtension;
String      filePath;
String      sffx;             // Suffix of db<sffx>.<fileType>
String      fileType;

//SurveyCommand* surveyCmd;

protected: // create from serialization only

  RWracesDBDoc();
  DECLARE_DYNCREATE(RWracesDBDoc)

public:

  virtual ~RWracesDBDoc() {};

          void setDataSrc(DataSource ds) {dataSource = ds;}
    DataSource dataSrc() {return dataSource;}

          void display(DataSource ds);

          void setFileSaveAttr(TCchar* suffix, TCchar* ext) {sffx = suffix; fileType = ext;}

          void getTitle();

  virtual void serialize(Archive& ar);

protected:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:                                // Generated message map functions

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
//  afx_msg void OnUpdateRequest();
//  afx_msg void OnSurveyRequest();
//  afx_msg void OnIDlist();
  afx_msg void OnMemberInfo();
  afx_msg void OnBadgesDT();
  afx_msg void OnBadgesCS();
  afx_msg void OnFormerCS();
  afx_msg void OnFormerNm();
  afx_msg void OnComparison();
  afx_msg void OnFixDeadRcds();
  afx_msg void OnOptions();
  afx_msg void OnFileSave();
  };


