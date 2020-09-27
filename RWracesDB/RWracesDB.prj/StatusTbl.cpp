// Status Table Extension Template


#include "stdafx.h"
#include "StatusTbl.h"
#include "Utilities.h"


StatusRecord* StatusTbl::get(String& abbreviation, String& description) {
StatusRecord* r = find(abbreviation, description);   if (r) return r;
StatusRecord  rcd;

  rcd.Abbreviation = abbreviation;   rcd.Description = description;   rcd.mark();  StatusTable::add(rcd);

  toDatabase();   return find(abbreviation, description);
  }


StatusRecord* StatusTbl::find(String& abbreviation, String& description) {
SttsIter      iter(*this);
StatusRecord* rcd;

  if (isEmpty(&abbreviation, &description, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
                    if (rcd->Abbreviation == abbreviation && rcd->Description == description) return rcd;
  return 0;
  }



StatusRecord* StatusTbl::find(String& abbr) {
SttsIter      iter(*this);
StatusRecord* rcd;

  if (!abbr.length()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->Abbreviation == abbr) return rcd;
  return 0;
  }


struct Status {
TCchar* key;
TCchar* desc;
};


Status statusList[3] = {{_T("Act"), _T("Member is Active")},
                        {_T("InA"), _T("Member is deemed inactive but still a member")},
                        {_T("Fmr"), _T("Member is a former member and not active")}
                        };




void StatusTbl::FixedInit() {
int i;

  for (i = 0; i < noElements(statusList); i++) {
    Status& itm = statusList[i];
    String  key = itm.key;
    String  dsc = itm.desc;      add(key, dsc);
    }
  }



long StatusTbl::add(String& key, String& dsc) {
long id;

  if (key.isEmpty()) return 0;

  id = findID(key);   if (id) return id;

  StatusRecord r; r.Abbreviation = key; r.Description = dsc;  r.mark(); StatusTable::add(r);

  toDatabase();   return findID(key);
  }


static const String unk = _T("Unk");


const String& StatusTbl::findAbbr(const long key)
                                 {StatusRecord* rcd = find(key); return rcd ? rcd->Abbreviation : unk;}

