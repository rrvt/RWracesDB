// My CSV Records


#include "stdafx.h"
#include "CSVLex.h"
#include "CSVOut.h"
#include "CSVRcdXB.h"

// load csv data from file

bool CSVRcdXB::load(CSVLex& lex){
static TCchar* NullStg = _T("");

  clear();

  while (lex.get_token() != EolToken) {
    CSVtok& tok  = lex.token;
    CSVtok& tok1 = lex.token1;

    if (tok.code  == CommaToken) {put(NullStg);         putI++; lex.accept_token();      continue;}
    if (tok1.code == CommaToken) {put(tok.name.trim()); putI++; lex.accept_two_tokens(); continue;}
    if (tok.code  == EOFToken) return putI > 0;

    put(tok.name.trim()); putI++; lex.accept_token();
    }

  lex.accept_token();   return true;
  }


void CSVRcdXB::store(Archive& ar) {
CSVOut  co(ar);
String* s;
String  line;

  for (getI = 0, s = get(); s; getI++, s = get()) {
    if (getI > 0) co << _T(',');

    co << *s;
    }

  co << vCrlf;
  }


void CSVRcdXB::display() {
String* s;

  for (getI = 0, s = get(); s; getI++, s = get()) {if (getI > 0) notePad << _T(',');   notePad << *s;}

  notePad << nCrlf;
  }

