// List of Members suitable for sorting

#pragma once
#include "Expandable.h"
#include "IterT.h"

class MemberRcd;


enum SortCriteria {GoogleEarthSrt, EverbridgeSrt};


class Member {
int    folderOrder;
String firstName;
String lastName;

public:

MemberRcd* p;

  Member() : folderOrder(0), firstName(), lastName(), p(0) {}
  Member(const Member& m) : folderOrder(m.folderOrder), firstName(m.firstName),
                                                                          lastName(m.lastName), p(m.p) {}
 ~Member() {firstName.clear(); lastName.clear(); p = 0;}


  Member& operator= (Member& m)
    {folderOrder = m.folderOrder; firstName = m.firstName; lastName = m.lastName; p = m.p; return *this;}

  bool operator== (Member& m);
  bool operator>  (Member& m);
  bool operator<= (Member& m);

  friend class MemberList;
  };


class MemberList;
typedef IterT<MemberList, MemberRcd> MLstIter;


class MemberList {
int                   i;
int                   nList;
Expandable<Member, 2> list;

public:

  MemberList(SortCriteria sortCriteria);
 ~MemberList() {}

private:

  MemberList() {}

  // returns either a pointer to data (or datum) at index i in array or zero
  MemberRcd* datum(int i) {return 0 <= i && i < nData() ? list[i].p : 0;}

  // returns number of data items in array
  int   nData()      {return list.end();}

  friend typename MLstIter;
  };

