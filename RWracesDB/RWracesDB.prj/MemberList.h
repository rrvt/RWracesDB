// List of Members suitable for sorting

#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class MbrRcd;
class AsnRcd;


class MbrDsc {
public:
String  key;
MbrRcd* rcd;

  MbrDsc() : rcd(0) {}
 ~MbrDsc() { }


  // Needed for Insertion Sort of Primary Key
  bool operator== (MbrDsc& r) {return key == r.key;}
  bool operator>= (MbrDsc& r) {return key >= r.key;}
  };


typedef DatumPtrT<MbrDsc, String> MbrDscP;


class MemberList;
typedef IterT<MemberList, MbrDsc> MLstIter;


class MemberList {

ExpandableP<MbrDsc, String, MbrDscP, 2> data;

public:

  MemberList();
 ~MemberList() {}

private:

  int getPriority(AsnRcd* asnRcd);

  // returns either a pointer to data (or datum) at index i in array or zero

  MbrDsc* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MLstIter;
  };

