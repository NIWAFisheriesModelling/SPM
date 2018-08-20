svn_version --path ..\ --format tex --recursive --quiet --suffix Doc
"../../spm" -v > SPMversion.tex
python QuickReference.py
pdflatex.exe SPM
bibtex.exe SPM
makeindex.exe SPM
python QuickReference.py
pdflatex.exe SPM
bibtex.exe SPM
makeindex.exe SPM
python QuickReference.py
pdflatex.exe SPM
bibtex.exe SPM
makeindex.exe SPM

