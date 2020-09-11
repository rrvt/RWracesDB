// MainFrm.h : interface of the MainFrame class
//


#pragma once

class MainFrame : public CFrameWnd {

protected: // create from serialization only
  MainFrame();
  DECLARE_DYNCREATE(MainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  void setAppName(TCchar* name) {m_strTitle = name;}
  void setTitle(  TCchar* leftPart);

  virtual void OnMove(int x, int y);
  virtual void OnSize(UINT nType, int cx, int cy);

// Implementation
public:
  virtual ~MainFrame();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
  CToolBar    m_wndToolBar;

// Generated message map functions
protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  DECLARE_MESSAGE_MAP()
  };


