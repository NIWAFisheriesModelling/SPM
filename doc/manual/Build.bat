svn_version --path ..\ --format tex --recursive --quiet --suffix Doc
"../../spm" -v > SPMversion.tex
python QuickReference.py
"C:\Program Files\MiKTeX 2.9\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\makeindex.exe" SPM
python QuickReference.py
"C:\Program Files\MiKTeX 2.9\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\makeindex.exe" SPM
python QuickReference.py
"C:\Program Files\MiKTeX 2.9\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.9\miktex\bin\makeindex.exe" SPM

