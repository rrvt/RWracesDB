# RWracesDB
Manipulate SJ RACES Database in a variety of ways:

  - Connect to the RACES database and show the number of records in each table
  - Print anything in the window
  - Save content of the window to a file (all reports are output to the window)
  - Load an attendance/activity csv file maintained by other members into the App.
  - Upload the information from the attendance/activity csv into the database
  - Produce Monthly update reports based on the database:
    * Excel compatible csv file, one line per member, all database fields
    * Google Earth csv file useful for updating Google Earth Pro with the locations of each
      member
    * Everbridge compatible csv file
    * Counts of members by readiness categories
    * List of FCC call signs
  - Produce the text for asking a new responder his readiness parameters
  - Produce the text for asking the members (i.e. survey) to check their contact information,
    filtered by having already responded
  - Produce a list containing the identities of each user (used as a check list for the survey)
  - Produce a list for each current member for use with the eICs211 program.  It contains the members
    name, call sign and badge number in a csv format.

## Getting Started

RWracesDB is composed of three projects and compiled with Visual Studio 2017.  The three projects are:
  - RWracesDB -- Solution File is in the ...\RWracesDB\RWracesDB\ folder.  It references the other two
    projects (Library and Installer)
  - Library -- This project produces a static library of which some object files are loaded into
    the executable and the msi (installer file)
  - Installer -- A Wix Toolset Installer.  Currently this file (Product.wxs) contains reference to only
    one file RWracesDB.exe (and renames RacesDB on the desktop and elsewhere).  If you wish to change
    the installer then I suggest you look at WixApp.

### Prerequisites

Of course this all depends on having the SJ RACES database, a Visual Studio 2017 +/- and the ability to
debug if things don't go right.  The Extension "Wix Toolset visual Studio 2017 Extension" is also
required.  It can be found in "Tools/Extensions and Updates".

A version of the Data Access Object dynamic library must be on your system.  The library module,
AceDao.h, contains the following lines (which you may have to change):
```
#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;
```
Here is an explanation of DAO:
```
   https://en.wikipedia.org/wiki/Data_access_object
```

All the code is contained in the two directories.


## Updates

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### August 16, 2020

Internal changes only.  Functionality is the same.

### July 20, 2020

The initial try at the Everbridge csv file had a couple of flaws.  Apparently there is some time when
the Access database shows a blank but RWracesDB gets a zero.  Test for that and eliminate it from the
Everbridge output.  Also moved the END on the records to the same column as the END in the header.
Changed one of the header names too.


### July 16, 2020

The Chief Radio Officer (CRO) has the use of Everbridge, a management application used by Emergency Service
Agencies.  He needs the data from the SJ RACES database in a particular format to upload into Everbridge.
Recently he has discovered that the original csv file produced by RWracesDB was not adequate for this
purpose.  The CRO did find a sample format for the file and RWracesDB has been changed to provide the
correct input to Everbridge.  The CRO needs to test this version of the csv so while I am saving the
current version it remains to be seen if it is correct.

## Authors

Robert R. Van Tuyl, K6RWY, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

