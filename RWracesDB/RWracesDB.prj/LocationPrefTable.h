// LocationPref Table Extension Template


#pragma once
#include "LocationPrefMap.h"


class LcPfIter {

typedef LocationPrefMap::MyMap MyMap;
typedef MyMap::iterator        MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  LcPfIter(LocationPrefMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  LocationPrefRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  LocationPrefRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  LocationPrefRecord* operator-- (int) {return decr();}

  LocationPrefRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  LocationPrefRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  LocationPrefRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  LcPfIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class LocationPrefMap;
  friend class LocationPrefTable;
  };


class LocationPrefTable : public LocationPrefMap {

public:

  LocationPrefTable() : LocationPrefMap() { }

  LocationPrefRecord* get(String& key, String& txt);

  LocationPrefRecord* find(const long key) {LcPfIter iter(*this); return iter.find(key);}

  long add(TCchar* key, TCchar* txt);
  bool add(LocationPrefRecord& rcd) {return LocationPrefMap::add(rcd);}

  long findID(String& key);
  long findID(String& key, String& txt);

  bool toDatabase() {return LocationPrefMap::toDatabase();}

private:

  LocationPrefRecord* find(String& key, String& txt);
  };
