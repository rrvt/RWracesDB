// List of Members suitable for sorting


#include "stdafx.h"
#include "MemberList.h"
#include "qsort.h"


static bool sortForGEP = false;


  #if 0
  if (assgnPrefRcd) {
    s = assgnPrefRcd->APKey;
    if      (s == _T("P")) s = _T("1st Call");
    else if (s == _T("E")) s = _T("not 1st Call");
    else if (s == _T("G")) s = _T("General");
    else if (s == _T("L")) s = _T("Last Call");
    else if (s == _T("A")) s = _T("ARES Only");
    else                   s = assgnPrefRcd->Txt;
    quoteStrOut(s);
    }
  else notePad << _T("ARES Only,");
#endif



static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };



MemberList::MemberList(SortCriteria sortCriteria) {
MmbrIter      iter(memberTable);
MemberRecord* rcd;
int           i;

  sortForGEP = sortCriteria == GoogleEarth;

  for (rcd = iter(); rcd; rcd = iter++) {
    int           statusID  = rcd->StatusID;
    StatusRecord* statusRcd = statusTable.find(statusID);

    if (!statusRcd || statusRcd->Abbreviation == _T("Fmr")) continue;

    int           mbrID  = rcd->MbrEntityID;
    EntityRecord* mbrRcd = entityTable.find(mbrID);      if (!mbrRcd) continue;

    Member& m = list.nextData();

    m.p = rcd; m.firstName = mbrRcd->FirstName; m.lastName = mbrRcd->LastName;

    if (sortForGEP) {
      int              assgnPrefID   = rcd->AssgnPrefID;
      AssgnPrefRecord* assgnPrefRcd  = assgnPrefTable.find(assgnPrefID);

      if (assgnPrefRcd) {
        String s = assgnPrefRcd->APKey;
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

