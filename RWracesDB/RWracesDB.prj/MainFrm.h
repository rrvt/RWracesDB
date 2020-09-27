// MainFrm.h : interface of the MainFrame class


#pragma once
#include "CMainFrm.h"
#include "ToolBar.h"


class MainFrame : public CMainFrm {

CMFCMenuBar   m_wndMenuBar;
ToolBar       toolBar;
CMFCStatusBar m_wndStatusBar;
CMenu         menu;

protected: // create from serialization only

  MainFrame();

  DECLARE_DYNCREATE(MainFrame)

public:

  virtual ~MainFrame();

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  void setAppName(TCchar* name) {m_strTitle = name;}
  void setTitle(  TCchar* leftPart);

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


