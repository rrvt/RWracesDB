// MainFrame.h : interface of the MainFrame class


#pragma once
#include "CMainFrm.h"
#include "MyToolBar.h"
#include "WinPos.h"


class MainFrame : public CMainFrm {

CMFCMenuBar   m_wndMenuBar;
MyToolBar     toolBar;
CMFCStatusBar m_wndStatusBar;
CMenu         bdgMenu;
CMenu         fmrMenu;
CMenu         stsMenu;

bool          isInitialized;

protected: // create from serialization only

  MainFrame();

  DECLARE_DYNCREATE(MainFrame)

public:

  virtual ~MainFrame();

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnMove(int x, int y);
  virtual void OnSize(UINT nType, int cx, int cy);

  void setupToolBar();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:

  DECLARE_MESSAGE_MAP()

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  };


