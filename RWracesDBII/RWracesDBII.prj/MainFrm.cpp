// MainFrm.cpp : implementation of the MainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "resource.h"
#include "WindowData.h"


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

MainFrame::MainFrame() { }


MainFrame::~MainFrame() {}


BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs) {
int        xSize = ::GetSystemMetrics(SM_CXSCREEN);
int        ySize = ::GetSystemMetrics(SM_CYSCREEN);
WindowData winData(iniFile);
RECT       rect;

  cs.cx = xSize * 45 / 100;  cs.cy = ySize * 7 / 10;

  winData.getSize(rect);

  cs.x = rect.left; cs.y = rect.top;

  if (rect.right  > cs.cx) cs.cx = rect.right;
  if (rect.bottom > cs.cy) cs.cy = rect.bottom;

  return CFrameWndEx::PreCreateWindow(cs) ? TRUE : FALSE;
  }


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CFrameWndEx::OnCreate(lpCreateStruct) == -1) return -1;

  if (!m_wndMenuBar.Create(this)) {TRACE0("Failed to create menubar\n"); return -1;}
  CMFCPopupMenu::SetForceMenuFocus(FALSE);

  if (!toolBar.CreateEx(this, TBSTYLE_FLAT,
                                        WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
      !toolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, TRUE)) {TRACE0("Failed to create toolbar\n"); return -1;}

  if (!m_wndStatusBar.Create(this)) {TRACE0("Failed to create status bar\n"); return -1;}

  m_wndStatusBar.SetIndicators(indicators, noElements(indicators));  //sizeof(indicators)/sizeof(UINT)

  DockPane(&m_wndMenuBar);
  DockPane(&toolBar);

  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
                                                                      // Affects look of toolbar, etc.
  return 0;
  }


afx_msg LRESULT MainFrame::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar(); return 0;}


void MainFrame::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.initialize(winRect);

  toolBar.installMenu(ID_Badges, IDR_BadgeOpts,    _T("Badged"));
  toolBar.installMenu(ID_Former, IDR_FormerOpts,   _T("Former"));
  toolBar.installMenu(ID_Status, IDR_MemberStatus, _T("Mbr Status"));
  }


void MainFrame::OnMove(int x, int y) {
WindowData winData(iniFile);
RECT       rect;

  GetWindowRect(&rect); winData.savePos(rect.left, rect.top);

  CFrameWndEx::OnMove(x, y);
  }



void MainFrame::OnSize(UINT nType, int cx, int cy) {
WindowData winData(iniFile);
RECT       rect;

  GetWindowRect(&rect);

  if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
                                      winData.saveSize(rect.right - rect.left, rect.bottom - rect.top);
  CFrameWndEx::OnSize(nType, cx, cy);
  }


// MainFrame diagnostics

#ifdef _DEBUG

void MainFrame::AssertValid() const {CFrameWndEx::AssertValid();}

void MainFrame::Dump(CDumpContext& dc) const {CFrameWndEx::Dump(dc);}

#endif //_DEBUG


