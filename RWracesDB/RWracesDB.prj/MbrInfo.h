// Member Info -- Used in reports


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class MbrRcd;
enum BadgeSort {BdgDateSort, BdgFCCSort};
enum FmrSort   {FmrNameSort, FmrFCCSort};


struct MbrInfo {
String sortKey;
String firstName;
String lastName;
String badgeNumber;
String callSign;
bool   badgeOk;
String badgeExpDate;

  MbrInfo() : badgeOk(false) { }
  MbrInfo(MbrInfo& mi) {copy(mi);}

  MbrInfo& operator=  (MbrInfo& mi) {copy(mi); return *this;}

  bool get(MbrRcd& rcd);

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (MbrInfo& mi) {return sortKey >= mi.sortKey;}
  bool     operator== (MbrInfo& mi) {return sortKey == mi.sortKey;}

  // Required for qsort, ==, >, <= and assignment (=)
  bool     operator>  (MbrInfo& mi) {return sortKey >  mi.sortKey;}
  bool     operator<= (MbrInfo& mi) {return sortKey <= mi.sortKey;}

private:

  void copy(MbrInfo& mi) {
    sortKey     = mi.sortKey;
    firstName   = mi.firstName;   lastName     = mi.lastName;
    badgeNumber = mi.badgeNumber; callSign     = mi.callSign;
    badgeOk     = mi.badgeOk;     badgeExpDate = mi.badgeExpDate;
    }
  };


typedef DatumPtrT<MbrInfo> MbrInfoP;                      // Usually defined just before iterator
class InfoRpts;
typedef IterT<InfoRpts, MbrInfo> InfoIter;


class InfoRpts {

ExpandableP<MbrInfo, MbrInfoP, 2> data;

public:

  InfoRpts() { }
 ~InfoRpts() { }

  void info();
  void dspBadges(BadgeSort badgeSort);
  void former(FmrSort sortKey);

private:

  String getDateKey(String& d);
  String decodeDate(String& d);

  // returns either a pointer to data (or datum) at index i in array or zero

  MbrInfo* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename InfoIter;
  };




//  bool getFormer(MbrRcd& rcd);

