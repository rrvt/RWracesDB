// MainFrm.cpp : implementation of the MainFrame class
//

#include "pch.h"
#include "MainFrame.h"
#include "Resource.h"


IMPLEMENT_DYNCREATE(MainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWndEx)
  ON_WM_CREATE()
  ON_WM_MOVE()
  ON_WM_SIZE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)              // MainFrame::
END_MESSAGE_MAP()


static UINT indicators[] = {
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
  };


// MainFrame construction/destruction

MainFrame::MainFrame() : isInitialized(false) { }


MainFrame::~MainFrame() {winPos.~WinPos();}


BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs) {

  cs.style &= ~FWS_ADDTOTITLE;  cs.lpszName = _T("AddProj");    // Sets the default title left part

  return CFrameWndEx::PreCreateWindow(cs) ? TRUE : FALSE;
  }


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
CRect winRect;

  if (CFrameWndEx::OnCreate(lpCreateStruct) == -1) return -1;

  if (!m_wndMenuBar.Create(this)) {TRACE0("Failed to create menubar\n"); return -1;}

  CMFCPopupMenu::SetForceMenuFocus(FALSE);

  if (!toolBar.CreateEx(this, TBSTYLE_FLAT,
                                        WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
      !toolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, TRUE)) {TRACE0("Failed to create toolbar\n"); return -1;}

  if (!m_wndStatusBar.Create(this)) {TRACE0("Failed to create status bar\n"); return -1;}

  m_wndStatusBar.SetIndicators(indicators, noElements(indicators));

  GetWindowRect(&winRect);   winPos.initialPos(this, winRect);

  DockPane(&m_wndMenuBar);   DockPane(&toolBar);

  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
                                                                   // Affects look of toolbar, etc.
  isInitialized = true;   return 0;
  }


void MainFrame::OnMove(int x, int y)
    {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CFrameWndEx::OnMove(x, y);}


void MainFrame::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CFrameWndEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);
  }


afx_msg LRESULT MainFrame::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar(); return 0;}


void MainFrame::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.set(winRect);

  toolBar.addMenu(ID_Badges, IDR_BadgeOpts,    _T("Badged"));
  toolBar.addMenu(ID_Former, IDR_FormerOpts,   _T("Former"));
  toolBar.addMenu(ID_Status, IDR_MemberStatus, _T("Mbr Status"));
  }



// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const          {CFrameWndEx::AssertValid();}
void MainFrame::Dump(CDumpContext& dc) const {CFrameWndEx::Dump(dc);}
#endif //_DEBUG

