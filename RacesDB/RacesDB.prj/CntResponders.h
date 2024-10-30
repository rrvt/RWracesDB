// Count Responders


#pragma once

class MbrRcd;


class CntResponders {

public:

  CntResponders() { }
 ~CntResponders() { }

  void operator() ();

private:

  int getRspClass(MbrRcd* rcd);
  };

