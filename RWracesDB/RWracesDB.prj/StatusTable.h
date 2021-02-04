// Status Table Extension Template


#pragma once
#include "StatusMap.h"


class SttsIter {

typedef StatusMap::MyMap MyMap;
typedef MyMap::iterator  MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  SttsIter(StatusMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  StatusRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  StatusRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  StatusRecord* operator-- (int) {return decr();}

  StatusRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  StatusRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  StatusRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  SttsIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class StatusMap;
  friend class StatusTable;
  };


class StatusTable : public StatusMap {

public:

  StatusTable() : StatusMap() { }

  StatusRecord* get(String& abbreviation, String& description);

  StatusRecord* find(const long key) {SttsIter iter(*this); return iter.find(key);}

  long add(TCchar* abbreviation, TCchar* description);
  bool add(StatusRecord& rcd) {return StatusMap::add(rcd);}

  long findID(String& key);
  long findID(String& abbreviation, String& description);

  bool toDatabase() {return StatusMap::toDatabase();}

private:

  StatusRecord* find(String& abbreviation, String& description);
  };
