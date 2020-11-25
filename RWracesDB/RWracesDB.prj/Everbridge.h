// Everbridge Report


#pragma once
#include "Quoted.h"

struct MemberRecord;
struct EntityRecord;


class Everbridge {

Quoted        quoted;

public:

  Everbridge(DspType dt) : quoted(dt) { }
 ~Everbridge() { }

  void operator() ();

private:


  void header();
  void display(MemberRecord& rcd);
  void location(TCchar* title, EntityRecord* rcd);
  void eMail(TCchar* em);
  void phone(TCchar* ph);
  void out(TCchar* p);
  void emptyFields(int n);

  Everbridge() : quoted(NilDspType) { }
  };


