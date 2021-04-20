// EntityTable


#pragma once
#include "DBtables.h"
#include "DAOfields.h"
#include "ExpandableP.h"


class EntityRcd : public DBrcd {
public:
String firstName;
String middleInitial;
String lastName;
String suffix;
long   addrID;
long   cityStID;
bool   addrIsPO;
String locationZip;
String eMail;
String phone1;
String phone2;

  EntityRcd() : DBrcd(), addrID(0), cityStID(0), addrIsPO(false) { }
 ~EntityRcd() { }

          void load(FieldsP fields);
          void store(FieldsP fields);

  virtual void display();

  // Needed for Insertion Sort of Primary Key
  bool operator== (EntityRcd& r) {return id == r.id;}
  bool operator>= (EntityRcd& r) {return id >= r.id;}

  // Needed for Binary Search of Primary Key
  bool operator== (long id) {return this->id == id;}
  bool operator<  (long id) {return this->id <  id;}
  bool operator>  (long id) {return this->id >  id;}

  // Needed for Linear Search with one or more arguments
  bool isInRcd(TCchar* firstName, TCchar* lastName, TCchar* eMail, TCchar* phone1, TCchar* phone2)
{return this->firstName == firstName && this->lastName == lastName && this->eMail == eMail && this->phone1 == phone1 && this->phone2 == phone2;}
  };


// Iterator Declaration, see IterT.h for details
class EntityTbl;
typedef IterT<EntityTbl, EntityRcd> EntIter;

// Record Pointer Declaration, see ExpandableP.h for details
typedef RcdPtrT<EntityRcd> EntityRcdP;


class EntityTbl : public DBtable {

ExpandableP<EntityRcd, EntityRcdP, 2> data;

public:

  EntityTbl() : DBtable(_T("Entity")) {dbTables = this;}
 ~EntityTbl() { }

  virtual bool operator== (TCchar* name) {return this->name == name;}

          bool load(DAOtable* daoTable);  // load database table into memory, does not use addNewRcd.

    EntityRcd* add(EntityRcd& rcd);     // Add a new record to table and database
          void store();

    EntityRcd* find(long id) {return data.bSearch(id);}
    EntityRcd* find(TCchar* firstName, TCchar* lastName, TCchar* eMail, TCchar* phone1, TCchar* phone2);

  virtual void display();

  virtual void setTabs();
private:

// returns either a pointer to data (or datum) at index i in array or zero

  EntityRcd* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename EntIter;
  };


  extern EntityTbl entityTbl;

