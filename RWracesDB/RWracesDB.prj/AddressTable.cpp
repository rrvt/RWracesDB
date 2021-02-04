// Address Table Extension Template


#include "stdafx.h"
#include "AddressTable.h"
#include "Utilities.h"


AddressRecord* AddressTable::get(String& address1, String& address2) {
AddressRecord* r = find(address1, address2);   if (r) return r;
AddressRecord  rcd;

  rcd.Address1 = address1; rcd.Address2 = address2;  rcd.mark();  AddressMap::add(rcd);

  toDatabase();   return find(address1, address2);
  }


long AddressTable::add(TCchar* address1, TCchar* address2) {
String arg0 = address1;
String arg1 = address2;
long   id;

  if (arg0.isEmpty() && arg1.isEmpty()) return 0;

  id = findID(arg0, arg1);   if (id) return id;

  AddressRecord r;  r.Address1 = arg0;  r.Address2 = arg1;
  r.mark();   AddressMap::add(r);

  toDatabase();   return findID(arg0, arg1);
  }


long AddressTable::findID(String& key) {
AddsIter       iter(*this);
AddressRecord* rcd;

  if (key.isEmpty()) return 0;

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->Address1 == key) return rcd->AddressID;

  return 0;
  }

long AddressTable::findID(String& address1, String& address2) {
AddressRecord* rcd = find(address1, address2);
  return rcd ? rcd->AddressID : 0;
  }


AddressRecord* AddressTable::find(String& address1, String& address2) {
AddsIter       iter(*this);
AddressRecord* rcd;

  if (isEmpty(&address1, &address2, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
    if (rcd->Address1 == address1 && rcd->Address2 == address2) return rcd;

  return 0;
  }

