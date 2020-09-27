// RWracesDBView.h : interface of the RWracesDBView class
//


#pragma once
#include "CScrView.h"


class RWracesDBDoc;


class RWracesDBView : public CScrView {

protected: // create from serialization only

  RWracesDBView() { }
  DECLARE_DYNCREATE(RWracesDBView)

// Attributes

public:

  virtual ~RWracesDBView() { }

  RWracesDBDoc* GetDocument() const;


#ifdef _DEBUG

  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;

#endif
protected:

  DECLARE_MESSAGE_MAP()
  };


#ifndef _DEBUG  // debug version in RWracesDBView.cpp
inline RWracesDBDoc* RWracesDBView::GetDocument() const {return reinterpret_cast<RWracesDBDoc*>(m_pDocument);}
#endif

