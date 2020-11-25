// Database Restoration


#pragma once
#include "Quoted.h"

class Archive;
class BackupRcd;


class DataBase {

Quoted        quoted;

public:

  DataBase(DspType dt) : quoted(dt) { }
 ~DataBase() { }

  void restore();
  void load(Archive& ar);

private:

  void   csvToDB();
  bool   restoreRcd(BackupRcd& csv);

  DataBase() : quoted(NilDspType) { }
  };

