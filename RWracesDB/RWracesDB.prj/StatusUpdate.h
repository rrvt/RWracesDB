// Status Update -- Update Database from MemberStatus downloaded from Google Files


#pragma once

class  Archive;
class  StatusRcd;
struct MemberRecord;
struct EntityRecord;
class  NotePad;


class StatusUpdate {

int noUpdates;

public:

  StatusUpdate() { }
 ~StatusUpdate() { }

  void load(Archive& ar);
  bool isLoaded();

  int  noRecords();

  void toDatabase();

private:

  void uploadOneStsCSV(StatusRcd& csv);
  void dspMemberName(MemberRecord* rcd);
  void setDspTabs(NotePad& np);
  void dspRcdName(EntityRecord* entity);
  };

