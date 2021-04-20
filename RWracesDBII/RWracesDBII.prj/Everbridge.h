// Everbridge Report


#pragma once
#include "Quoted.h"

class MemberRcd;
class EntityRcd;


class Everbridge {

Quoted        quoted;

public:

  Everbridge(DspType dt) : quoted(dt) { }
 ~Everbridge() { }

  void operator() ();

private:


  void header();
  void display(MemberRcd& rcd);
  void location(TCchar* title, EntityRcd* rcd);
  void eMail(TCchar* em);
  void phone(TCchar* ph);
  void out(TCchar* p);
  void emptyFields(int n);

  Everbridge() : quoted(NilDspType) { }
  };


