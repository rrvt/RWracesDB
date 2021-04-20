// Status Update -- Update Database from MemberStatus downloaded from Google Files


#pragma once

class Archive;
class CSVstsRcd;
class MemberRcd;
class EntityRcd;
class NotePad;


class StatusUpdate {

int noUpdates;

public:

  StatusUpdate() { }
 ~StatusUpdate() { }

  void load(Archive& ar);
  bool isLoaded();

  int  noRecords();

  void store();

private:

  void uploadOneStsCSV(CSVstsRcd& csv);
  void dspMemberName(MemberRcd* rcd);
  void setDspTabs(NotePad& np);
  void dspRcdName(EntityRcd* entity);
  };

