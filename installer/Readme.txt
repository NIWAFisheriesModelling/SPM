Readme.txt for Spatial Population Model (SPM)
============================================

About
=====

The Spatial Population Model (SPM) is a generalised spatially explicit
age-structured population dynamics and movement model.

SPM can model population dynamics and movement parameters for an age-
structured population using a range of observations, including tagging,
relative abundance, and age frequency data. SPM implements an age-
structured population within an arbitrary shaped spatial structure,
which can have user defined categories (e.g., immature, mature, male,
female, etc.), and age range. Movement can be modelled as either adjacent
cell movements or global movements based on covariates.

See the SPM User Manual for more information.

License
=======

See the SPM User Manual for a copy of the software license.

Installation
============

Use the the Microsoft Windows installer for SPM. This copies the progam
files to the SPM install directory, creates icons in your start menu,
and modifies the system registry to,
(i)   add to the the SPM install directory to the systems PATH
(ii)  associate .spm icons with Notepad.exe
(iii) register the uninstall information required to uninstall SPM.

Removing SPM
============

To uninstall, use the Microsoft Windows uninstaller. To uninstall
manually, delete the files from your computer (typically stored in
c:\Program Files\SPM, but this depends on your choices when you
installed the program) and any program links in your Start menu.
You could also modify your PATH to remove references to the SPM
directory and delete the following registry keys;

HKEY_CLASSES_ROOT\SPM.textfile\
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\SPM\
