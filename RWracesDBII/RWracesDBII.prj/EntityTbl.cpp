// Entity Table


#include "stdafx.h"
#include "EntityTbl.h"
#include "DAOfields.h"
#include "DAOrecords.h"
#include "NotePad.h"
#include "Utilities.h"


bool EntityTbl::load(DAOtable* daoTable) {
DAOrcdsIter iter(daoTable);
FieldsP     fields;
int         count;

  for (count = 0, fields = iter(DAOdenyWrite); fields; count++, fields = iter++) {
    EntityRcd rcd;   rcd.load(fields);   data = rcd;
    }

  notePad << count << nCrlf; return true;
  }


void EntityRcd::load(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   dsc;
variant_t   v;

  for (dsc = iter(); dsc; dsc = iter++) {
    v = dsc->value();
    switch (iter.index()) {
      case  0: id            = v; break;
      case  1: firstName     = v; break;
      case  2: middleInitial = v; break;
      case  3: lastName      = v; break;
      case  4: suffix        = v; break;
      case  5: addrID        = v; break;
      case  6: cityStID      = v; break;
      case  7: addrIsPO      = v; break;
      case  8: locationZip   = v; break;
      case  9: eMail         = v; break;
      case 10: phone1        = v; break;
      case 11: phone2        = v; break;
      default: throw _T("Entity Record Error");
      }
    }
  }


void EntityTbl::store() {
DAOtable*  daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Entity Table");
DAOrcds    daoRcds(daoTbl);
FieldsP    fieldsP;
EntIter    iter(*this);
EntityRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->isDeleted() && daoRcds.findRecord(rcd->id))
                                                       {daoRcds.delCurRcd();   iter.remove();   continue;}
    if (!rcd->isDirty()) continue;

    fieldsP = daoRcds.findRecord(rcd->id);   if (!fieldsP) continue;    // Add new records with addNewRcd

    daoRcds.edit();   rcd->store(fieldsP);   daoRcds.update();   rcd->clearMark();
    }
  }


EntityRcd* EntityTbl::add(EntityRcd& rcd) {
DAOtable* daoTbl = daoTables.bSearch(name);   if (!daoTbl) throw _T("Unable to locate Entity Table");
DAOrcds   daoRcds(daoTbl);
FieldsP   fieldsP;

  fieldsP = daoRcds.findRecord(rcd.id);   if (fieldsP) return 0;

  fieldsP = daoRcds.addNew();   rcd.store(fieldsP);  daoRcds.update();  rcd.clearMark();

  return data = rcd;
  }


void EntityRcd::store(FieldsP fields) {
DAOfldsIter iter(fields);
DAOfield*   field;
variant_t   v;

  for (field = iter(); field; field = iter++) {
    switch (iter.index()) {
      case  0: id = field->value(); continue;
      case  1: v  = firstName; break;
      case  2: v  = middleInitial; break;
      case  3: v  = lastName; break;
      case  4: v  = suffix; break;
      case  5: v  = addrID; break;
      case  6: v  = cityStID; break;
      case  7: v  = addrIsPO; break;
      case  8: v  = locationZip; break;
      case  9: v  = eMail; break;
      case 10: v  = phone1; break;
      case 11: v  = phone2; break;
      default: throw _T("Entity Record Error");
      }

    *field = v;
    }
  }


EntityRcd* EntityTbl::find(TCchar* firstName, TCchar* lastName, TCchar* eMail, TCchar* phone1, TCchar* phone2) {
EntIter    iter(*this);
EntityRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++)
                                 if (rcd->isInRcd(firstName, lastName, eMail, phone1, phone2)) return rcd;

  return 0;
  }


void EntityTbl::display() {
EntIter    iter(*this);
EntityRcd* rcd;

  setTabs();

  notePad << _T("Entity Table") << nCrlf;

  for (rcd = iter(); rcd; rcd = iter++) rcd->display();
  }


void EntityRcd::display() {
  notePad << nTab << id;
  notePad << nTab << firstName;
  notePad << nTab << lastName;
  notePad << nTab << eMail;
  notePad << nTab << phone1;
  notePad << nTab << phone2;
  notePad << nCrlf;
  }


void EntityTbl::setTabs() {
EntIter    iter(*this);
EntityRcd* rcd;
int        tab0 = 0;
int        tab1 = 0;
int        tab2 = 0;
int        tab3 = 0;
int        tab4 = 0;

  for (rcd = iter(); rcd; rcd = iter++) {
    maxLng(rcd->id, tab0);
    maxLng(rcd->firstName, tab1);
    maxLng(rcd->lastName, tab2);
    maxLng(rcd->eMail, tab3);
    maxLng(rcd->phone1, tab4);
    }

  tab1 += tab0 + 4;
  tab2 += tab1 + 2;
  tab3 += tab2 + 2;
  tab4 += tab3 + 2;

  notePad << nClrTabs;
  notePad << nSetRTab(tab0) << nSetTab(tab0 + 2);
  notePad << nSetTab(tab1);
  notePad << nSetTab(tab2);
  notePad << nSetTab(tab3);
  notePad << nSetTab(tab4);
  }

