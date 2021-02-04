// Entity Table Extension Template


#pragma once
#include "EntityMap.h"


class EntyIter {

typedef EntityMap::MyMap MyMap;
typedef MyMap::iterator  MyIter;

MyMap& myMap;
MyIter iter;

typedef pair<MyIter, bool> Pair;

public:

enum Dir {Fwd, Rev};

  EntyIter(EntityMap& dataStore) : myMap(dataStore.myMap), iter(myMap.end())  { }

  EntityRecord* operator() (Dir rev = Fwd) {
    if (rev) {iter = myMap.end();   return decr();}
    else     {iter = myMap.begin(); return iter == myMap.end() ? 0 : &iter->second;}
    }

  EntityRecord* operator++ (int)
                            {return iter == myMap.end() ? 0 : ++iter == myMap.end() ? 0 : &iter->second;}

  EntityRecord* operator-- (int) {return decr();}

  EntityRecord* current() {return iter == myMap.end() ? 0 : &iter->second;}

  bool isLast()  {MyIter x = iter; x++;  return x == myMap.end();}
  bool isFirst() {return iter == myMap.begin();}

  void remove() {iter = myMap.erase(iter);}

private:

  long curKey() {return iter != myMap.end() ?  iter->first  : -1;}

  EntityRecord* find(const long key)
                               {iter = myMap.find(key);  return iter == myMap.end() ? 0 : &iter->second;}

  EntityRecord* decr() {return iter == myMap.begin() ? 0 : &(--iter)->second;}

  EntyIter() : myMap(*(MyMap*) 0) { }                   // Prevents uninitizlized iterator

  friend class EntityMap;
  friend class EntityTable;
  };


class EntityTable : public EntityMap {

public:

  EntityTable() : EntityMap() { }

  EntityRecord* get(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2);

  EntityRecord* find(const long key) {EntyIter iter(*this); return iter.find(key);}

  bool add(EntityRecord& rcd) {return EntityMap::add(rcd);}

  long findID(String& key);
  long findID(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2);

  bool toDatabase() {return EntityMap::toDatabase();}

private:

  EntityRecord* find(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2);
  };
