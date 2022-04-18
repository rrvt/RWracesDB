// Status Update -- Update Database from MemberStatus downloaded from Google Files


#pragma once

class Archive;
class CSVstsRcd;
class MbrRcd;
class EntRcd;
class NotePad;


class StatusUpdate {

int noUpdates;

public:

  StatusUpdate() { }
 ~StatusUpdate() { }

  void load(Archive& ar);
  bool isLoaded();

  int  noRecords();

  void store(TCchar* path);

private:

  void uploadOneStsCSV(CSVstsRcd& csv);
  void dspMemberName(MbrRcd* rcd);
  void setDspTabs(NotePad& np);
  void dspRcdName(EntRcd* entity);
  };

