// Records related to an entry


#pragma once



struct Records {
AddressRcd*      addressRcd;
AssgnPrefRcd*    assgnPrefRcd;
CityStateRcd*    cityStRecord;
EntityRcd*       entityRecord;
LocationPrefRcd* locationPrefRcd;
MemberRcd*       memberRecord;
StatusRcd*       statusRcd;


  Records() : addressRcd(0), assgnPrefRcd(0), locationPrefRcd(0), statusRcd(0),
              cityStRecord(0), entityRecord(0), memberRecord(0) {}
 ~Records() {}
  };

