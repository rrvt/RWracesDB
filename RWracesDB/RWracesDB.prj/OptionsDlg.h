// Options Dialog Box


#pragma once
#include "Resource.h"


extern TCchar* PortraitKey;
extern TCchar* LandscapeKey;


// OptionsDlg dialog

class OptionsDlg : public CDialogEx {

  DECLARE_DYNAMIC(OptionsDlg)

public:
CComboBox orientCtrl;
CString   orient;

CString topMargin;
CString leftMargin;
CString rightMargin;
CString botMargin;
CEdit   topCtrl;
CEdit   leftCtrl;
CEdit   rightCtrl;
CEdit   botCtrl;

  OptionsDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~OptionsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Options };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void floatingOnly(CEdit& ctrl);

public:
  afx_msg void OnChangeTop();
  afx_msg void OnChangeLeft();
  afx_msg void OnChangeRight();
  afx_msg void OnChangeBot();
  virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
  virtual BOOL OnInitDialog();
};
