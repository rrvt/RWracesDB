// RWracesDBDOC.h : interface of the RWracesDBDoc class

#pragma once
#include "CDoc.h"
#include "MapData.h"
#include "MapTable.h"


class  Note;
class  DisplayLine;
class  SurveyCommand;
class  StatusRcd;
class  BackupRcd;


enum DocType {NilDocType, RestoreDocType, StatusDocType, FilterDocType};
enum DspType {NilDspType, ExcelDspType,   BkupDspType, CmpDspType};


struct MemberInfo {
String firstName;
String lastName;
String badgeNumber;
String callSign;

  MemberInfo() { }
  MemberInfo(MemberInfo& mi) {copy(mi);}

  //  *p == *q
  //  *p >  *q
  //  *p <= *q
  //  *s = *p

  MemberInfo& operator=  (MemberInfo& mi) {copy(mi); return *this;}
  bool        operator>  (MemberInfo& mi) {return callSign >  mi.callSign;}
  bool        operator<= (MemberInfo& mi) {return callSign <= mi.callSign;}
  bool        operator== (MemberInfo& mi) {return callSign == mi.callSign;}

private:

  void copy(MemberInfo& mi) {
    firstName   = mi.firstName;   lastName = mi.lastName;
    badgeNumber = mi.badgeNumber; callSign = mi.callSign;
    }
  };



class RWracesDBDoc : public CDoc {
String    dbPath;
String    title;

String    defaultExtension;
String    filePath;
String    sffx;             // Suffix of db<sffx>.<fileType>
String    fileType;

DocType   docType;

DspType   dspType;
bool      delDSWdates;

int       noUpdates;

bool      addComma;

SurveyCommand* surveyCmd;

protected: // create from serialization only
  RWracesDBDoc();
  DECLARE_DYNCREATE(RWracesDBDoc)

// Attributes
public:

          void setDocType(DocType t) {docType = t;}
          void setDspType(DspType t) {dspType = t;}

          void setFileSaveAttr(TCchar* suffix, TCchar* ext) {sffx = suffix; fileType = ext;}
          void OnFileSave();

          void getTitle();
          void setTitle(TCchar* s);

  virtual void serialize(Archive& ar);
          bool lex(CArchive& ar);

// Implementation
public:
  virtual ~RWracesDBDoc() {};

  void   dspRecordHeader(bool comparison = false);

  void   dspOneRecord(MemberRecord& rcd, DspType dspType);



  void   quoteStrOut(String& s);
  void   noComma()  {addComma = false;}
  void   commaOut() {addComma = true;}

  String quoteStrIn(String& s);

  void   dateOut(String& s);

  int    noStatusCSV() {return 0;}
  void   uploadStsCSV();
  void   uploadOneStsCSV(StatusRcd& csv);
  void   deleteDSWdates();
  void   restoreBackupCSV();
  bool   restoreOneBackupRcd(BackupRcd& csv);

protected:

  void                dspGoogleHeader();
  void                dspOneGoogleRcd(MemberRecord& rcd, bool workAddr);
  void                dspOneEverbridgeRcd(MemberRecord& rcd);
  void                UpdateRequest(MemberRecord& rcd);
  AssgnPrefRecord*    findAvail(TCchar* key);
  LocationPrefRecord* findLoc(TCchar* key);

  String              formatPhoneNo(String& ph);
  String              formatZip(String& zip);
  bool                addrAvail(EntityRecord* rcd, AddressRecord*& addrRcd);
  void                entityOut(EntityRecord* rcd, AddressRecord*& addrRcd);

  bool                dspEntity(EntityRecord* ent, MemberRecord* rcd = 0)          ;
  int                 removeDeadEntityRcds();
  bool                entityRcdNeeded(long id);
  int                 removeDeadAddrRcds();
  bool                addrRcdNeeded(long id);
  int                 removeDeadCityRcds();
  bool                cityRcdNeeded(long id);
  void                dspMemberName(MemberRecord* rcd);
  bool                getMemberInfo(MemberRecord& rcd, MemberInfo& memberInfo);


  void                ebHeader();
  void                ebLocation(TCchar* title, EntityRecord* rcd);
  void                ebPhone(TCchar* ph);
  void                ebEmail(TCchar* em);
  void                ebOut(  TCchar* p);
  void                emptyFields(int n);

  void                loadBackupData(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:                                // Generated message map functions

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnBackup();
  afx_msg void OnRestoreNew();
  afx_msg void OnExcelReport();
  afx_msg void OnGoogleEarth();
  afx_msg void OnEverbridge();
  afx_msg void OnCountResponders();
  afx_msg void OnFCCcallSigns();
  afx_msg void OnUpdateRequest();
  afx_msg void OnSurveyRequest();
  afx_msg void OnIDlist();
  afx_msg void OnMemberInfo();
  afx_msg void OnComparison();
  afx_msg void OnFixDeadRcds();
  afx_msg void FixDSWdates();
  };


