// Status Report


#pragma once
#include "NotePadRpt.h"


class StatusRpt : public NotePadRpt {

public:

  StatusRpt(NotePad& notePad) : NotePadRpt(notePad) { }
 ~StatusRpt() { }

  int  header(NotePad& np, bool printing);

private:

  StatusRpt() : NotePadRpt(*(NotePad*)0) { }
  };

