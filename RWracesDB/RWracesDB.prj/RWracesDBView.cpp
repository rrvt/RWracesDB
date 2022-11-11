// RWracesDBView.cpp : implementation of the RWracesDBView class
//

#include "pch.h"
#include "RWracesDBView.h"
#include "Options.h"
#include "RWracesDB.h"
#include "RWracesDBDoc.h"
//#include "StatusUpdate.h"


// RWracesDBView

IMPLEMENT_DYNCREATE(RWracesDBView, CScrView)

BEGIN_MESSAGE_MAP(RWracesDBView, CScrView)
END_MESSAGE_MAP()



void RWracesDBView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RWracesDBView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc :
      case RestoreSrc : prtNote.print(*this);   break;
      case StsUpdtSrc : prtStatus.print(*this); break;
      }

  else
    switch(ds) {
      case NotePadSrc :
      case RestoreSrc : dspNote.display(*this);   break;
      case StsUpdtSrc : dspStatus.display(*this); break;
      }

  CScrView::onPrepareOutput(printing);
  }



void RWracesDBView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void RWracesDBView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : prtNote.footer(dev, pageNo);  break;
    }
  }



void RWracesDBView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


void RWracesDBView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


#ifdef _DEBUG

void RWracesDBView::AssertValid() const {CScrollView::AssertValid();}

void RWracesDBView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

RWracesDBDoc* RWracesDBView::GetDocument() const
        {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RWracesDBDoc)));  return (RWracesDBDoc*)m_pDocument;}

#endif //_DEBUG
