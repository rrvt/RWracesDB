// RWracesDBView.h : interface of the RWracesDBView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#include "StatusRpt.h"


class RWracesDBDoc;


class RWracesDBView : public CScrView {

StatusRpt  dspStatus;
StatusRpt  prtStatus;

protected: // create from serialization only

  RWracesDBView() : CScrView(), dspStatus(dMgr.getNotePad()), prtStatus(pMgr.getNotePad()) { }

  DECLARE_DYNCREATE(RWracesDBView)

// Attributes

public:

  virtual      ~RWracesDBView() { }

  virtual void  initRptOrietn();
  virtual void  saveRptOrietn();

  virtual void  onPreparePrinting(CPrintInfo* info);
  virtual void  onBeginPrinting();
  virtual void  onDisplayOutput();

  virtual void  printFooter(DevBase& dev, int pageNo);
  virtual void  OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  RWracesDBDoc* GetDocument() const;


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


#ifndef _DEBUG  // debug version in RWracesDBView.cpp
inline RWracesDBDoc* RWracesDBView::GetDocument() const
                                            {return reinterpret_cast<RWracesDBDoc*>(m_pDocument);}
#endif

