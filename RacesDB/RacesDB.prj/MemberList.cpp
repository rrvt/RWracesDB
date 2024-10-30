// List of Members suitable for sorting


#include "pch.h"
#include "MemberList.h"
#include "Database.h"
#include "MbrSortList.h"
#include "qsort.h"



MemberList::MemberList() {
MbrLstIter iter(mbrSortList);
MbrItem*   item;
MbrRcd*    rcd;

  for (item = iter(); item; item = iter++) {

    if (!item->curMbr) continue;

    rcd = item->rcd;
    int     mbrID  = rcd->mbrEntityID;
    EntRcd* entRcd = entTbl.find(mbrID);      if (!entRcd) continue;

    MbrDsc* mbrDsc = data.allocate();

    mbrDsc->rcd = rcd;

    int priority = getPriority(asnTbl.find(rcd->assgnPrefID));

    mbrDsc->key = priority;   mbrDsc->key += entRcd->lastName + entRcd->firstName;

    data = mbrDsc;
    }
  }


static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };


int MemberList::getPriority(AsnRcd* asnRcd) {
int i;
int n = noElements(keys);

  if (!asnRcd) return n;

  for (i = 0; i < n; i++) if (asnRcd->aPKey == keys[i]) break;

  return i;
  }



