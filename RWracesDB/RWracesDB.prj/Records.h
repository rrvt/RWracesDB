// Records related to an entry


#pragma once



struct Records {
AdrRcd* addressRcd;
AsnRcd* assgnPrefRcd;
CtyRcd* cityStRecord;
EntRcd* entityRecord;
LocRcd* locationPrefRcd;
MbrRcd* memberRecord;
StsRcd* statusRcd;


  Records() : addressRcd(0), assgnPrefRcd(0), locationPrefRcd(0), statusRcd(0),
              cityStRecord(0), entityRecord(0), memberRecord(0) {}
 ~Records() {}
  };

