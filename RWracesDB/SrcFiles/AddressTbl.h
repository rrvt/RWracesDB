// Address Table Extension Template


#pragma once
#include "AddressMap.h"


class AddressTbl : public AddressTable {

public:

  AddressTbl() : AddressTable() {}

  AddressRecord* get(String& address1, String& address2);

  AddressRecord* find(const long key) {AddsIter iter(*this); return iter.find(key);}

private:

  AddressRecord* find(String& address1, String& address2);
  };
