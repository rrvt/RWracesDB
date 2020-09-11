// Survey

// for all members produce the body of an eMail that requests an update contact information.


#pragma once
#include "maps.h"
#include "NotePad.h"
#include "RWracesDB.h"

class SrvyLine;




class IDitem {
public:
String name;
String callSign;
String badgeNumber;
bool   check;

  IDitem() : check(false) { }
 ~IDitem() {check = true;}

  bool operator==    (IDitem& item) {return name == item.name;}         //  *p == *q
  bool operator>     (IDitem& item) {return name >  item.name;}         //  *p >  *q
  bool operator<=    (IDitem& item) {return name <= item.name;}         //  *p <= *q

  // *s =  *p
  IDitem& operator= (IDitem& item) {
    name = item.name; callSign = item.callSign; badgeNumber = item.badgeNumber; check = item.check;
    return *this;
    }
  };



class Survey {
MemberRecord& rcd;
public:

  Survey(MemberRecord* r) : rcd(*r) {  }
 ~Survey() {}

  void request();
  void dspeMail(EntityRecord* mbrRcd, String& eMail);

private:

  void phone(TCchar* prefix, EntityRecord* eRcd, bool cellPh, SrvyLine& sl);
  void eMail(TCchar* prefix, EntityRecord* eRcd, int  width,  SrvyLine& sl);
  void addr(TCchar* prefix,  EntityRecord* eRcd,              SrvyLine& sl);

enum EquipData {HandHeldData, PortMobileData, PortPacketData, OtherEquipData, OtherCapData};

  void equip(TCchar* prefix, EquipData equipData);

  };



class SurveyCommand {
RWracesDBDoc& doc;
Expandable<IDitem, 1> idList;
public:

  SurveyCommand(RWracesDBDoc& d) : doc(d) { }
  void doIt();
  bool surveyDone(String& callSign);

  bool loadIDfilter();
  void getItem(String& line);

private:

  SurveyCommand() : doc(*(RWracesDBDoc*)0) { }
  };

