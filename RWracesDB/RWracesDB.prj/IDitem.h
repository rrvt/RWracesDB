// ID item


#pragma once


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

