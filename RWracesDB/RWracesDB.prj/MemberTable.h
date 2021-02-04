// Member Table Extension Template


#pragma once
#include "MemberMap.h"


class MmbrIter {

typedef MemberMap::MyMap MyMap;
typedef MyMap::iterator  MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  MmbrIter(MemberMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  MemberRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  MemberRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  MemberRecord* operator-- (int) {return decr();}

  MemberRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  MemberRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  MemberRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  MmbrIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class MemberMap;
  friend class MemberTable;
  };


class MemberTable : public MemberMap {

public:

  MemberTable() : MemberMap() { }

  MemberRecord* get(String& callSign);

  MemberRecord* find(const long key) {MmbrIter iter(*this); return iter.find(key);}

  bool add(MemberRecord& rcd) {return MemberMap::add(rcd);}

  long findID(String& key);

  bool toDatabase() {return MemberMap::toDatabase();}

private:

  MemberRecord* find(String& callSign);
  };
