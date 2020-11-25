// Quoated entities


#pragma once


enum DspType {NilDspType, ExcelDspType, BkupDspType, CmpDspType};


class Quoted {

DspType dspType;
bool    addComma;

public:

  Quoted(DspType dt) : dspType(dt), addComma(true) { }
 ~Quoted() { }

  void   noComma()  {addComma = false;}
  void   commaOut() {addComma = true;}

  void   stg(String& s);
  void   date(String& s);

  String remDbl(String& s);

private:

  Quoted() : dspType(NilDspType) { }
  };

