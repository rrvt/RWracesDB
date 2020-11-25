// Survey

// for all members produce the body of an eMail that requests an update contact information.


#pragma once
#include "IDitem.h"
#include "maps.h"


class Archive;
class SrvyLine;



class Survey {
MemberRecord& rcd;
public:

  Survey(MemberRecord* r) : rcd(*r) {  }
 ~Survey() {}

  void request();
  void dspeMail(EntityRecord* mbrRcd, String& eMail);

private:

  void phone(TCchar* prefix, EntityRecord* eRcd, bool cellPh, SrvyLine& sl);
  void eMail(TCchar* prefix, EntityRecord* eRcd, int  width,  SrvyLine& sl);
  void addr(TCchar* prefix,  EntityRecord* eRcd,              SrvyLine& sl);

enum EquipData {HandHeldData, PortMobileData, PortPacketData, OtherEquipData, OtherCapData};

  void equip(TCchar* prefix, EquipData equipData);
  };



class SurveyCommand {

Expandable<IDitem, 1> idList;

public:

  SurveyCommand() { }

  void operator() ();

  void load(Archive& ar);

  bool surveyDone(String& callSign);

  void getItem(String& line);
  };

