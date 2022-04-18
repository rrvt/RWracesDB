// display Member Record


#pragma once
#include "Quoted.h"

class MbrRcd;
class EntRcd;


class MemberRpts {

DspType       dspType;
Quoted        quoted;

public:

  MemberRpts(DspType dt) : dspType(dt), quoted(dt) { }
 ~MemberRpts() { }

  void excel();
  void backup();
  void comparison();

  void covidList();

private:

  void   header(bool comparison = false);
  void   display(MbrRcd& rcd);
  bool   dspEntity(EntRcd* ent, MbrRcd* rcd = 0);

  MemberRpts() : dspType(NilDspType), quoted(NilDspType) { }
  };








#if 0
//enum BadgeSort {BdgDateSort, BdgFCCSort};
//enum FmrSort   {FmrNameSort, FmrFCCSort};


struct MemberInfo {
String sortKey;
String firstName;
String lastName;
String badgeNumber;
String callSign;
bool   badgeOk;
String badgeExpDate;

  MemberInfo() : badgeOk(false) { }
  MemberInfo(MemberInfo& mi) {copy(mi);}

  //  *p == *q
  //  *p >  *q
  //  *p <= *q
  //  *s =  *p

  MemberInfo& operator=  (MemberInfo& mi) {copy(mi); return *this;}
  bool        operator>  (MemberInfo& mi) {return sortKey >  mi.sortKey;}
  bool        operator>= (MemberInfo& mi) {return sortKey >= mi.sortKey;}
  bool        operator<= (MemberInfo& mi) {return sortKey <= mi.sortKey;}
  bool        operator== (MemberInfo& mi) {return sortKey == mi.sortKey;}

private:

  void copy(MemberInfo& mi) {
    sortKey     = mi.sortKey;
    firstName   = mi.firstName;   lastName     = mi.lastName;
    badgeNumber = mi.badgeNumber; callSign     = mi.callSign;
    badgeOk     = mi.badgeOk;     badgeExpDate = mi.badgeExpDate;
    }
  };
#endif
#if 0
  void idList();

  void info();
  void badgesCS();
  void badgesDT();

  void formerNm();
  void formerCS();
#endif
#if 0
  void   dspBadges(BadgeSort badgeSort);
  String getDateKey(String& d);
  String decodeDate(String& d);

  void   former(FmrSort sortKey);
  bool   getFormerMbrInfo(MbrRcd& rcd, MemberInfo& memberInfo);

  bool   getMemberInfo(MbrRcd& rcd, MemberInfo& memberInfo);
#endif

