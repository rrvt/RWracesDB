// List comprised of Member Table sorted


#pragma once
#include "ExpandableP.h"
#include "IterT.h"


class MbrRcd;


struct MbrItem {
String  key;
MbrRcd* rcd;
bool    curMbr;

  MbrItem() : rcd(0), curMbr(false) { }

  // Needed for Insertion Sort of Primary Key
  bool operator== (MbrItem& r) {return key == r.key;}
  bool operator>= (MbrItem& r) {return key >= r.key;}
  };


// Record Pointer Declaration, see ExpandableP.h for details
typedef DatumPtrT<MbrItem, String>  MbrItemP;

class MbrSortList;
typedef IterT<MbrSortList, MbrItem> MbrLstIter;



class MbrSortList {

ExpandableP<MbrItem, String, MbrItemP, 2> data;

public:

  MbrSortList() { }
 ~MbrSortList() { }

  void create();

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  MbrItem* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int    nData()      {return data.end();}                 // returns number of data items in array

  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MbrLstIter;
  };


extern MbrSortList mbrSortList;
