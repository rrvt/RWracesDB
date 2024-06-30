// RWracesDBView.cpp : implementation of the RWracesDBView class
//

#include "pch.h"
#include "RWracesDBView.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "RWracesDB.h"
#include "RWracesDBDoc.h"
#include "RptOrientDlgTwo.h"


static TCchar* StsOrietnKey = _T("Status");


// RWracesDBView

IMPLEMENT_DYNCREATE(RWracesDBView, CScrView)

BEGIN_MESSAGE_MAP(RWracesDBView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


void RWracesDBView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void RWracesDBView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
  dlg.rpt1 = printer.toStg(prtStatus.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
    prtStatus.prtrOrietn = printer.toOrient(dlg.rpt1);
    saveRptOrietn();
    }
  }


void RWracesDBView::initRptOrietn()
    {prtStatus.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StsOrietnKey, PortOrient);}


void RWracesDBView::saveRptOrietn()
     {saveNoteOrietn();   iniFile.write(RptOrietnSect, StsOrietnKey,  (int) prtStatus.prtrOrietn);}


void RWracesDBView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);   break;
    case StsUpdtSrc : prtStatus.onPreparePrinting(info); break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RWracesDBView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : prtNote.onBeginPrinting(*this);   break;
    case StsUpdtSrc : prtStatus.onBeginPrinting(*this); break;
    }
  }


void RWracesDBView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : dspNote.display(*this);   break;
    case StsUpdtSrc : dspStatus.display(*this); break;
    }
  }



// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void RWracesDBView::printFooter(DevBase& dev, int pageNo) {prtNote.prtFooter(dev, pageNo);}



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
void RWracesDBView::AssertValid() const          {CScrollView::AssertValid();}
void RWracesDBView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

RWracesDBDoc* RWracesDBView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RWracesDBDoc)));  return (RWracesDBDoc*)m_pDocument;}
#endif //_DEBUG
