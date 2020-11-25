// Update Request

// for all members that have reached responder status produce the body of an eMail that request an
// update of their Availability (Assignment Pref) and Prefered Locality (Location Pref.


#pragma once

struct MemberRecord;
struct AssgnPrefRecord;
struct LocationPrefRecord;


class UpdateRequest {

public:

  UpdateRequest() { }
 ~UpdateRequest() { }

  void operator() ();

  void display(MemberRecord& rcd);

private:

  AssgnPrefRecord* findAvail(TCchar* key);
  LocationPrefRecord* findLoc(TCchar* key);
  };

