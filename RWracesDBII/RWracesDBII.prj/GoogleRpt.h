// Google Earch Report


#pragma once
#include "Quoted.h"

class AddressRcd;
class EntityRcd;
class MemberRcd;

class GoogleRpt {

Quoted        quoted;

public:

  GoogleRpt(DspType dt) : quoted(dt) { }
 ~GoogleRpt() { }

  void   header();
  void   operator() ();
  void   display(MemberRcd& rcd, bool workAddr);
  String formatPhoneNo(String& ph);
  String formatZip(String& zip);
  bool   addrAvail(EntityRcd* rcd, AddressRcd*& addrRcd);
  void   entityOut(EntityRcd* rcd, AddressRcd*& addrRcd);

private:

  GoogleRpt() : quoted(NilDspType) { }
  };

