svn_version --path ..\ --format tex --recursive --quiet --suffix Doc
spm -v > SPMversion.tex
python QuickReference.tex
"C:\Program Files\MiKTeX 2.7\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\makeindex.exe" SPM
python QuickReference.tex
"C:\Program Files\MiKTeX 2.7\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\makeindex.exe" SPM
python QuickReference.tex
"C:\Program Files\MiKTeX 2.7\miktex\bin\pdflatex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\bibtex.exe" SPM
"C:\Program Files\MiKTeX 2.7\miktex\bin\makeindex.exe" SPM

