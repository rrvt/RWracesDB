// Database Restoration


#pragma once
#include "Quoted.h"

class Archive;
class BackupRcd;
class MemberRcd;
class EntityRcd;
class AddressRcd;
class CityStateRcd;


class DataBase {

Quoted        quoted;

public:

  DataBase(DspType dt) : quoted(dt) { }
 ~DataBase() { }

  void restore();
  void load(Archive& ar);

private:

  void          csvToDB();
  bool          rstrRcd(   BackupRcd& csv);
  MemberRcd*    rstrMbr(   BackupRcd& csv);
  EntityRcd*    rstrMbrEnt(BackupRcd& csv);
  EntityRcd*    rstrEmpEnt(BackupRcd& csv);
  EntityRcd*    rstrICEent(BackupRcd& csv);

  EntityRcd*    rstrEnt(String& first, String& last, String& eMail, String& ph1, String& ph2);
  void          rstrRest(EntityRcd* rcd, String& midInit, String& suffix, bool IsPO, String& locZip);
  AddressRcd*   rstrAddr(String& addr1, String& addr2);
  CityStateRcd* rstrCitySt(String& city, String& state, String& zip);


  DataBase() : quoted(NilDspType) { }
  };



