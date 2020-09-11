// Address Table Extension Template


#include "stdafx.h"
#include "AddressTbl.h"
#include "Utilities.h"


AddressRecord* AddressTbl::get(String& address1, String& address2) {
AddressRecord* r = find(address1, address2);   if (r) return r;
AddressRecord  rcd;

  rcd.Address1 = address1;    rcd.Address2 = address2;    rcd.mark();  AddressTable::add(rcd);

  toDatabase();   return find(address1, address2);
  }


AddressRecord* AddressTbl::find(String& address1, String& address2) {
AddsIter       iter(*this);
AddressRecord* rcd;

  if (isEmpty(&address1, &address2, 0)) return 0;

  for (rcd = iter(); rcd; rcd = iter++)
                                  if (rcd->Address1 == address1 && rcd->Address2 == address2) return rcd;

  return 0;
  }

