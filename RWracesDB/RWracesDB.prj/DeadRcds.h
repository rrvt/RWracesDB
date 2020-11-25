// Dead Record Removal


#pragma once


class DeadRcds {

public:

  DeadRcds() { }
 ~DeadRcds() { }

  void fix();

private:

  int  removeDeadEntityRcds();
  bool entityRcdNeeded(long id);
  int  removeDeadAddrRcds();
  bool addrRcdNeeded(long id);
  int  removeDeadCityRcds();
  bool cityRcdNeeded(long id);
  };

