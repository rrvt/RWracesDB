// RacesDBView.cpp : implementation of the RacesDBView class
//

#include "pch.h"
#include "RacesDBView.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "RacesDB.h"
#include "RacesDBDOC.h"
#include "RptOrientDlgTwo.h"


static TCchar* StsOrietnKey = _T("Status");


// RacesDBView

IMPLEMENT_DYNCREATE(RacesDBView, CScrView)

BEGIN_MESSAGE_MAP(RacesDBView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


void RacesDBView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void RacesDBView::onRptOrietn() {
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


void RacesDBView::initRptOrietn()
    {prtStatus.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StsOrietnKey, PortOrient);}


void RacesDBView::saveRptOrietn()
     {saveNoteOrietn();   iniFile.write(RptOrietnSect, StsOrietnKey,  (int) prtStatus.prtrOrietn);}


void RacesDBView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);   break;
    case StsUpdtSrc : prtStatus.onPreparePrinting(info); break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RacesDBView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : prtNote.onBeginPrinting(*this);   break;
    case StsUpdtSrc : prtStatus.onBeginPrinting(*this); break;
    }
  }


void RacesDBView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : dspNote.display(*this);   break;
    case StsUpdtSrc : dspStatus.display(*this); break;
    }
  }



// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void RacesDBView::printFooter(DevBase& dev, int pageNo) {prtNote.prtFooter(dev, pageNo);}



void RacesDBView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


void RacesDBView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


#ifdef _DEBUG
void RacesDBView::AssertValid() const          {CScrollView::AssertValid();}
void RacesDBView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

RacesDBDOC* RacesDBView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RacesDBDOC)));  return (RacesDBDOC*)m_pDocument;}
#endif //_DEBUG
