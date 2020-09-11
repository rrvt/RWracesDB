// Records related to an entry


#pragma once

#include "MapData.h"


struct Records {
AddressRecord*      addressRcd;
AssgnPrefRecord*    assgnPrefRcd;
CityStateRecord*    cityStRecord;
EntityRecord*       entityRecord;
LocationPrefRecord* locationPrefRcd;
MemberRecord*       memberRecord;
StatusRecord*       statusRcd;


  Records() : addressRcd(0), assgnPrefRcd(0), locationPrefRcd(0), statusRcd(0),
              cityStRecord(0), entityRecord(0), memberRecord(0) {}
 ~Records() {}
  };

