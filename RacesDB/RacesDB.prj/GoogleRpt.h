// Google Earch Report


#pragma once
#include "Quoted.h"

class AdrRcd;
class EntRcd;
class MbrRcd;


class GoogleRpt {

Quoted        quoted;

public:

  GoogleRpt(DspType dt) : quoted(dt) { }
 ~GoogleRpt() { }

  void   header();
  void   operator() ();
  void   display(MbrRcd& rcd, bool workAddr);
  String formatPhoneNo(String& ph);
  String formatZip(String& zip);
  bool   addrAvail(EntRcd* rcd, AdrRcd*& addrRcd);
  void   entityOut(EntRcd* rcd, AdrRcd*& addrRcd);

private:

  GoogleRpt() : quoted(NilDspType) { }
  };

