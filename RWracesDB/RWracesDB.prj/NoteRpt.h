// NotePad Report -- Logic to output the NotePad content to the display and/or printer


#pragma once
#include "NoteRptB.h"




class NoteRpt : public NoteRptB {

public:

  NoteRpt(NotePad& notePad) : NoteRptB(notePad) { }
 ~NoteRpt() { }

protected:

  int  header( NotePad& np, bool printing);
  void setTabs(NotePad& np) override;

private:
  NoteRpt() : NoteRptB(*(NotePad*)0)  { }
  };

