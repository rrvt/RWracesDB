// Status Report


#include "pch.h"
#include "StatusRpt.h"
#include "Date.h"
#include "NotePad.h"


int StatusRpt::header(NotePad& np, bool printing) {
Date   dt;
String s;

  if (!printing) return 0;

  dt.getToday();   s = dt.getDate() + _T(" ") + dt.getHHMM();

  np << _T("Status Update") << nRight << s << nCrlf << nCrlf;   return 2;
  }


