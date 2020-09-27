// Entity Table Extension Template


#pragma once
#include "EntityMap.h"


class EntityTbl : public EntityTable {

public:

  EntityTbl() : EntityTable() { }

  EntityRecord* get(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2);

  EntityRecord* find(const long key) {EntyIter iter(*this); return iter.find(key);}

private:

  EntityRecord* find(String& firstName, String& lastName, String& eMail, String& phone1, String& phone2);
  };
