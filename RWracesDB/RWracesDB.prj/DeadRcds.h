// Dead Record Removal


#pragma once


class DeadRcds {

public:

  DeadRcds() { }
 ~DeadRcds() { }

  void fix(TCchar* path);

private:

  int  removeDeadEntityRcds(TCchar* path);
  bool entityRcdNeeded(long id);
  int  removeDeadAddrRcds(TCchar* path);
  bool addrRcdNeeded(long id);
  int  removeDeadCityRcds(TCchar* path);
  bool cityRcdNeeded(long id);
  };

