// List comprised of Member Table sorted


#include "pch.h"
#include "MbrSortList.h"
#include "MbrTbl.h"
#include "EntTbl.h"
#include "StsTbl.h"


MbrSortList mbrSortList;


void MbrSortList::create() {
MbrIter iter(mbrTbl);
MbrRcd* mbr;
EntRcd* ent;
StsRcd* sts;

  data.clear();

  for (mbr = iter(); mbr; mbr = iter++) {
    ent = entTbl.find(mbr->mbrEntityID);   if (!ent) continue;
    sts = stsTbl.find(mbr->statusID);

    MbrItem* item = data.allocate();

    item->key    = ent->lastName + ent->firstName + ent->middleInitial + mbr->callSign;
    item->rcd    = mbr;
    item->curMbr = sts && sts->abbreviation != _T("Fmr") ? true : false;

    data = item;
    }
  }

