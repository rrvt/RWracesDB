// Utility Functions


#include "pch.h"
#include "RDbUtilities.h"


// Local Variables

static long    defaultBadgeNo = -1;


void initDefaultBadgeNo() {defaultBadgeNo = -1;}


long sanitizeBadgeNo(String& bn) {
Tchar* endPtr;
long   n = _tcstol(bn, &endPtr, 10);

  if (n <= 0) n = defaultBadgeNo--;

  return n;
  }


String sanitizeDate(String& date) {
static String t;
String        s;
Tchar         ch;
int           i;

  t.clear();

  for (i = 0; i < int(date.size()); i++) {
    ch = date[i];
    if (ch == _T(':')) {if (t.length() == 2) t.clear();   break;}
    if (_T('0') <= ch && ch <= _T('9')) t += ch;
    }

  if (t.length() == 5) t = _T('0') + t;
  if (t.length() == 7) t = _T('0') + t;

  if (t.length() == 8) {
    s = t.substr(0,4);
    s += t.substr(6);
    t = s;
    }

  if (t.length() == 4) {
    s = t; t.clear();
    t =  "0" + s.substr(0,1);
    t += "0" + s.substr(1);
    }

  return t;
  }


String sanitizeAddr(String& addr) {
static String t;
Tchar         ch;
int           i;

  t.clear();

  for (i = 0; i < int(addr.size()); i++) {ch = addr[i];  if (ch != _T(' ')) break;}
  for (     ; i < int(addr.size()); i++)  t += addr[i];

  return t;
  }


String sanitizeZip(String& zip) {
static String t;
Tchar         ch;
int           i;

  t.clear();

  for (i = 0; i < int(zip.size()); i++)
                                      {ch = zip[i];  if (_T('0') <= ch && ch <= _T('9')) t += ch;}
  return t;
  }


bool isEmpty(String* s, ...) {
va_list args;
String* p;

  if (s->size() != 0) return false;

  for (va_start(args, s); (p = va_arg(args, String*)) && p != 0; )
                                                                  if (p->size() != 0) return false;
  return true;
  }



static TCchar quote = _T('"');


String& quotes(TCchar* p) {
static String s;
bool          addQuotes = false;

  if (!p) {s.clear(); return s;}

  s = p;

  if (s.find(quote) >= 0) {
    String t;
    int    n = s.length();
    int    i;

    for (i = 0; i < n; i++) {Tchar ch = s[i];   if (ch == quote) t += quote;   t += ch;}

    s = t; addQuotes = true;
    }

  if (s.find(_T(',')) >= 0) addQuotes = true;

  if (addQuotes) s = quote + s + quote;

  return s;
  }

