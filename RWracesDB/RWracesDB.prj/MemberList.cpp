// List of Members suitable for sorting


#include "pch.h"
#include "MemberList.h"
#if 1
#include "Database.h"
#else
#include "AssgnPrefTbl.h"
#include "EntityTbl.h"
#include "MemberTbl.h"
#include "StatusTbl.h"
#endif
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



#if 0
// Sort conditionals with two different algorithms based on the sortForGEP boolean

bool Member::operator== (Member& m) {
  if (sortForGEP) {
    return folderOrder == m.folderOrder && lastName == m.lastName && firstName == m.firstName;
    }
  return lastName == m.lastName && firstName == m.firstName;
  }


bool Member::operator>  (Member& m) {
  if (sortForGEP) {
    return folderOrder > m.folderOrder || (folderOrder == m.folderOrder && lastName >  m.lastName ||
                                                  (lastName == m.lastName && firstName > m.firstName));
    }
  return lastName >  m.lastName || (lastName == m.lastName && firstName > m.firstName);
  }


bool Member::operator<= (Member& m) {
  if (sortForGEP) {
    return folderOrder < m.folderOrder || (folderOrder == m.folderOrder && lastName < m.lastName ||
                                                 (lastName == m.lastName && firstName <= m.firstName));
    }
  return lastName < m.lastName || (lastName == m.lastName && firstName <= m.firstName);
  }
#endif
#if 0
    int     statusID  = rcd->statusID;
    StsRcd* statusRcd = stsTbl.find(statusID);

    if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) continue;
#endif
#if 1
#else
MbrIter iter(mbrTbl);
#endif
//int     i;

