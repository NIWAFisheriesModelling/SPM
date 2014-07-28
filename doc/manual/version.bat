"../../spm" -v > SPMversion.tex
svn_version --path ..\ --format tex --recursive --quiet --suffix Doc
python QuickReference.py

