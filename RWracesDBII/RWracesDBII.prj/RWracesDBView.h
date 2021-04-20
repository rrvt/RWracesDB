// RWracesDBView.h : interface of the RWracesDBView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#include "StatusRpt.h"


class RWracesDBDoc;


class RWracesDBView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;
StatusRpt  dspStatus;
StatusRpt  prtStatus;

protected: // create from serialization only

  RWracesDBView() : dspNote(  dMgr.getNotePad()), prtNote(  pMgr.getNotePad()),
                    dspStatus(dMgr.getNotePad()), prtStatus(pMgr.getNotePad()) { }
  DECLARE_DYNCREATE(RWracesDBView)

// Attributes

public:

  virtual ~RWracesDBView() { }

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  RWracesDBDoc* GetDocument() const;


#ifdef _DEBUG

  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;

#endif
protected:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in RWracesDBView.cpp
inline RWracesDBDoc* RWracesDBView::GetDocument() const {return reinterpret_cast<RWracesDBDoc*>(m_pDocument);}
#endif

