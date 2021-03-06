// display Member Record


#pragma once
#include "Quoted.h"

struct MemberRecord;
struct EntityRecord;

enum BadgeSort {BdgDateSort, BdgFCCSort};
enum FmrSort   {FmrNameSort, FmrFCCSort};


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


class MemberRpts {

DspType       dspType;
Quoted        quoted;

public:

  MemberRpts(DspType dt) : dspType(dt), quoted(dt) { }
 ~MemberRpts() { }

  void info();
  void idList();

  void badgesCS();
  void badgesDT();

  void formerNm();
  void formerCS();

  void excel();
  void backup();
  void comparison();

private:

  void   dspBadges(BadgeSort badgeSort);
  String getDateKey(String& d);
  String decodeDate(String& d);

  void   former(FmrSort sortKey);
  bool   getFormerMbrInfo(MemberRecord& rcd, MemberInfo& memberInfo);

  bool   getMemberInfo(MemberRecord& rcd, MemberInfo& memberInfo);

  void   header(bool comparison = false);
  void   display (MemberRecord& rcd);
  bool   dspEntity(EntityRecord* ent, MemberRecord* rcd = 0);

  MemberRpts() : dspType(NilDspType), quoted(NilDspType) { }
  };

