// Google Earch Report


#pragma once
#include "Quoted.h"

struct AddressRecord;
struct EntityRecord;
struct MemberRecord;

class GoogleRpt {

Quoted        quoted;

public:

  GoogleRpt(DspType dt) : quoted(dt) { }
 ~GoogleRpt() { }

  void   header();
  void   operator() ();
  void   display(MemberRecord& rcd, bool workAddr);
  String formatPhoneNo(String& ph);
  String formatZip(String& zip);
  bool   addrAvail(EntityRecord* rcd, AddressRecord*& addrRcd);
  void   entityOut(EntityRecord* rcd, AddressRecord*& addrRcd);

private:

  GoogleRpt() : quoted(NilDspType) { }
  };

