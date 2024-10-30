// RacesDBView.h : interface of the RacesDBView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#include "StatusRpt.h"


class RacesDBDOC;


class RacesDBView : public CScrView {

StatusRpt  dspStatus;
StatusRpt  prtStatus;

protected: // create from serialization only

  RacesDBView() : CScrView(), dspStatus(dMgr.getNotePad()), prtStatus(pMgr.getNotePad()) { }

  DECLARE_DYNCREATE(RacesDBView)

// Attributes

public:

  virtual      ~RacesDBView() { }

  virtual void  initRptOrietn();
  virtual void  saveRptOrietn();

  virtual void  onPreparePrinting(CPrintInfo* info);
  virtual void  onBeginPrinting();
  virtual void  onDisplayOutput();

  virtual void  printFooter(DevBase& dev, int pageNo);
  virtual void  OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  RacesDBDOC* GetDocument() const;


#ifdef _DEBUG

  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;

#endif
protected:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in RacesDBView.cpp
inline RacesDBDOC* RacesDBView::GetDocument() const
                                            {return reinterpret_cast<RacesDBDOC*>(m_pDocument);}
#endif

