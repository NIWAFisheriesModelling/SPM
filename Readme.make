Readme.make for Spatial Population Model (SPM)
==============================================

The Spatial Population Model (SPM) is a generalised spatially explicit
age-structured population dynamics and movement model.

See the SPM User Manual for more information about the program.

License
=======

See the SPM User Manual for a copy of the software license.

To build SPM from the source files
==================================

To build the Microdoft Windows version of SPM uing MinGW gcc, issue 
the following commands in the SPM/ directory

> cmake -G "MinGW Makefiles"
> mingw32-make all
> strip spm.exe

For Linux systems using gcc, issue the folloowing commands

> cmake -G "Unix Makefiles"
> make all
> strip spm

Note that you will need the BOOST (version 1.48.0) libraries and header
files installed. Currently, the locations of these are hard-coded in the 
CMake CMakeLists.txt file. You will need to edit the paths for these 
libraries in order for SPM to compile.

Other compilers may work, but we have not tested compilation using 
anything other than MinGW and Linux gcc versions 4.6.1

Contact
=======

For more information about SPM, please read the SPM User Manual or contact
the authors.
