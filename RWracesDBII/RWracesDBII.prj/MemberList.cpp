// List of Members suitable for sorting


#include "stdafx.h"
#include "MemberList.h"
#include "AssgnPrefTbl.h"
#include "EntityTbl.h"
#include "MemberTbl.h"
#include "qsort.h"
#include "StatusTbl.h"


static bool sortForGEP = false;

static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };



MemberList::MemberList(SortCriteria sortCriteria) {
MbrIter    iter(memberTbl);
MemberRcd* rcd;
int        i;

  sortForGEP = sortCriteria == GoogleEarthSrt;

  for (rcd = iter(); rcd; rcd = iter++) {
    int        statusID  = rcd->statusID;
    StatusRcd* statusRcd = statusTbl.find(statusID);

    if (!statusRcd || statusRcd->abbreviation == _T("Fmr")) continue;

    int        mbrID  = rcd->mbrEntityID;
    EntityRcd* mbrRcd = entityTbl.find(mbrID);      if (!mbrRcd) continue;

    Member& m = list.nextData();

    m.p = rcd; m.firstName = mbrRcd->firstName; m.lastName = mbrRcd->lastName;

    if (sortForGEP) {
      int           assgnPrefID   = rcd->assgnPrefID;
      AssgnPrefRcd* assgnPrefRcd  = assgnPrefTbl.find(assgnPrefID);

      if (assgnPrefRcd) {
        String s = assgnPrefRcd->apkey;
        for (i = 0; i < noElements(keys); i++) {
          if (s == keys[i]) {m.folderOrder = i; break;}
          }
        if (i >= noElements(keys)) m.folderOrder = i;
        }
      else m.folderOrder = noElements(keys);
      }
    }

  nList = list.end();

  qsort(&list[0], &list[nList-1]);
  }


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

