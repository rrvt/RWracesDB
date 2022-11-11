// Quoated entities


#include "pch.h"
#include "Quoted.h"
#include "NotePad.h"


static String zeros = _T("000000");


void Quoted::date(String& s) {
int    n;
String t;
String mon;
String day;
String yr;
String d;

  if (dspType == ExcelDspType) {
    n = s.size();
    if (n > 0) {
      t = zeros.substr(0, 6-n) + s;
      mon = t.substr(0,2);
      day = t.substr(2,2);
      yr  = t.substr(4,2);
      d = mon + _T("/") + day + _T("/20") + yr;
      }
    stg(d);
    }
  else stg(s);
  }


void Quoted::stg(String& s) {
int    i;
int    lng = s.size();
Tchar  ch;
String t;

  if (!lng) notePad << _T("\" \"");

  else {
    for (i = 0; i < lng; i++) {
      ch = s[i];

      if      (ch == _T('"')) t += _T('"');

      switch (dspType) {
        case CmpDspType   :
        case ExcelDspType : if (ch == _T('\r')) continue;
                            if (ch == _T('\n')) {t += _T("; "); continue;}
                            break;
        case BkupDspType  : if (ch == _T('\r')) continue;
                            if (ch == _T('\n')) {t += _T("\\\\M"); continue;}
                            break;
        }

      t += ch;
      }

    notePad << _T('"') << t << _T('"');
    }

  if (addComma) notePad << _T(",");
  }


String Quoted::remDbl(String& s) {
int    i;
int    lng = s.size();
Tchar  ch;
Tchar  ch1;
String t;

  for (i = 0; i < lng; i++) {
    ch = s[i]; ch1 = i+1 < lng ? s[i+1] : 0;

    if (ch == _T('"') && ch1 == _T('"')) {t += _T('"'); i++; continue;}

    if (dspType == BkupDspType && ch == _T('\\') && ch1 == _T('M')) {t += _T("\r\n"); i++; continue;}

    t += ch;
    }

  return t;
  }

