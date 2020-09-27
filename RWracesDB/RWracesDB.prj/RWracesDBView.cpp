// RWracesDBView.cpp : implementation of the RWracesDBView class
//

#include "stdafx.h"
#include "RWracesDBView.h"
#include "RWracesDBDoc.h"


// RWracesDBView

IMPLEMENT_DYNCREATE(RWracesDBView, CScrView)

BEGIN_MESSAGE_MAP(RWracesDBView, CScrView)
END_MESSAGE_MAP()


#ifdef _DEBUG

void RWracesDBView::AssertValid() const {CScrollView::AssertValid();}

void RWracesDBView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

RWracesDBDoc* RWracesDBView::GetDocument() const
        {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RWracesDBDoc)));  return (RWracesDBDoc*)m_pDocument;}

#endif //_DEBUG

