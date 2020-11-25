// NotePad Report -- Logic to output the NotePad content to the display and/or printer


#include "stdafx.h"
#include "NoteRpt.h"
#include "RWracesDB.h"
#include "RWracesDBDoc.h"
#include "RWracesDBView.h"
#include "StatusUpdate.h"


int NoteRpt::header(NotePad& np, bool printing) {
  switch(doc()->dataSrc()) {
    case StsUpdtSrc : {StatusUpdate stsUpdt; return stsUpdt.header(np, printing);}
    default         : return NoteRptB::header(np, printing);
    }
  }


void NoteRpt::setTabs(NotePad& np) {
  switch(doc()->dataSrc()) {
    case StsUpdtSrc : {StatusUpdate stsUpdt; stsUpdt.setDspTabs(np); break;}
    default         : NoteRptB::setTabs(np);                         break;
    }
  }


