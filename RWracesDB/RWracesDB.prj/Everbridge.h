// Everbridge Report


#pragma once
#include "Quoted.h"

class MbrRcd;
class EntRcd;


class Everbridge {

Quoted        quoted;

public:

  Everbridge(DspType dt) : quoted(dt) { }
 ~Everbridge() { }

  void operator() ();

private:

  void header();
  void display(MbrRcd& rcd);
  void location(TCchar* title, EntRcd* rcd);
  void eMail(TCchar* em);
  void phone(TCchar* ph);
  void out(TCchar* p);
  void emptyFields(int n);

  Everbridge() : quoted(NilDspType) { }
  };


