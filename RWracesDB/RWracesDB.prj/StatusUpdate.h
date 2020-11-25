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

  bool load();
  void load(Archive& ar);

  int  noRecords();

  void toDatabase();
  int  header(NotePad& np, bool printing);
  void setDspTabs(NotePad& np);

private:

  void uploadOneStsCSV(StatusRcd& csv);
  void dspMemberName(MemberRecord* rcd);
  void dspRcdName(EntityRecord* entity);
  };

