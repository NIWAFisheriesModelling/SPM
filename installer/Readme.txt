Readme.txt for Spatial Population Model (SPM)
============================================

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

Your can either

Use the Microsoft Windows installer for SPM. This copies the progam
files to the SPM install directory, creates icons in your start menu,
and modifies the system registry to,
(i)   Add to the the SPM install directory to the systems PATH
(ii)  Associate .spm files with the SPM icon and to open with Notepad.exe
(iii) Register the uninstall information required for Microsoft Windows
      to uninstall SPM.

Note that, depending on your system setup, you may need to reboot after
installing to re-initialise the system PATH. 

Or

Manually copy the SPM executable to a location of your choice.

In both cases, only the SPM executable is required. But note that SPM
is a console program, and can only be used from the command line.

Removing SPM
============

To uninstall, use the Microsoft Windows uninstaller. To uninstall
manually, delete the files from your computer (typically stored in
c:\Program Files\SPM, but this depends on your choices when you
installed the program) and any program links in your Start menu.

If you have used the installer to install SPM, then you may also
wish to modify your PATH to remove references to the SPM directory
and delete the following registry keys (if required);

HKEY_CLASSES_ROOT\.spm\
HKEY_CLASSES_ROOT\SPM.textfile\
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\SPM\

Contact
=======

For more information about SPM, please read the SPM User Manual or contact
the authors.
