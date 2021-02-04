// AssgnPref Table Extension Template


#pragma once
#include "AssgnPrefMap.h"


class AgPfIter {

typedef AssgnPrefMap::MyMap MyMap;
typedef MyMap::iterator     MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  AgPfIter(AssgnPrefMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  AssgnPrefRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  AssgnPrefRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  AssgnPrefRecord* operator-- (int) {return decr();}

  AssgnPrefRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  AssgnPrefRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  AssgnPrefRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  AgPfIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class AssgnPrefMap;
  friend class AssgnPrefTable;
  };


class AssgnPrefTable : public AssgnPrefMap {

public:

  AssgnPrefTable() : AssgnPrefMap() { }

  AssgnPrefRecord* get(String& aPKey, String& txt);

  AssgnPrefRecord* find(const long key) {AgPfIter iter(*this); return iter.find(key);}

  long add(TCchar* aPKey, TCchar* txt);
  bool add(AssgnPrefRecord& rcd) {return AssgnPrefMap::add(rcd);}

  long findID(String& key);
  long findID(String& aPKey, String& txt);

  bool toDatabase() {return AssgnPrefMap::toDatabase();}

private:

  AssgnPrefRecord* find(String& aPKey, String& txt);
  };
