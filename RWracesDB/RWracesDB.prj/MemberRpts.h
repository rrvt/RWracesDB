// display Member Record


#pragma once
#include "Quoted.h"

class MbrRcd;
class EntRcd;


class MemberRpts {

DspType       dspType;
Quoted        quoted;

public:

  MemberRpts(DspType dt) : dspType(dt), quoted(dt) { }
 ~MemberRpts() { }

  void excel();
  void backup();
  void comparison();

  void covidList();

private:

  void   header(bool comparison = false);
  void   display(MbrRcd& rcd);
  bool   dspEntity(EntRcd* ent, MbrRcd* rcd = 0);

  MemberRpts() : dspType(NilDspType), quoted(NilDspType) { }
  };




