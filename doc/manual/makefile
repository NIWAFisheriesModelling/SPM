

all: VERSION QUICKREF
	pdflatex -interaction=nonstopmode SPM.tex
	bibtex SPM.aux
	pdflatex -interaction=nonstopmode SPM.tex
	pdflatex -interaction=nonstopmode SPM.tex

once: VERSION
	latex -interaction=nonstopmode SPM.tex

VERSION: *.tex
	spm --version > SPMversion.tex
	svn_version --format tex --recursive --quiet --suffix Doc

QUICKREF:
	c:/progra~1/Python26/python < QuickReference.py

clean:
	rm -f *.log \
	rm -f *.aux \
	rm -f *.out \
	rm -f *.dvi \
	rm -f *.pdf \
	rm -f *.ps \
	rm -f *.toc \
	rm -f *.blg \
	rm -f *.bbl \
