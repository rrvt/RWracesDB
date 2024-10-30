

RacesDB.chm : *.htm RacesDB.hhp RacesDB.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesDB


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F RacesDB.chm


Release/RacesDB.chm : RacesDB.chm
  copy $(MAKEDIR)\RacesDB.chm  $(MAKEDIR)\..\Release\RacesDB.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del RacesDB.chm
  cd $(MAKEDIR)


Debug/RacesDB.chm : RacesDB.chm
  copy $(MAKEDIR)\RacesDB.chm  $(MAKEDIR)\..\Debug\RacesDB.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del RacesDB.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RacesDB.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RacesDB.chm


