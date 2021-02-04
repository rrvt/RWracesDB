// Address Table Extension Template


#pragma once
#include "AddressMap.h"


class AddsIter {

typedef AddressMap::MyMap MyMap;
typedef MyMap::iterator   MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  AddsIter(AddressMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  AddressRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  AddressRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  AddressRecord* operator-- (int) {return decr();}

  AddressRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  AddressRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  AddressRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  AddsIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class AddressMap;
  friend class AddressTable;
  };


class AddressTable : public AddressMap {

public:

  AddressTable() : AddressMap() { }

  AddressRecord* get(String& address1, String& address2);

  AddressRecord* find(const long key) {AddsIter iter(*this); return iter.find(key);}

  long add(TCchar* address1, TCchar* address2);
  bool add(AddressRecord& rcd) {return AddressMap::add(rcd);}

  long findID(String& key);
  long findID(String& address1, String& address2);

  bool toDatabase() {return AddressMap::toDatabase();}

private:

  AddressRecord* find(String& address1, String& address2);
  };
