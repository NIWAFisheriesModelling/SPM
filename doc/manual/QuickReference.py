import string

FILE = [open('Syntax/GeneralSyntax.tex', 'r'),open('Syntax/PopulationSyntax.tex', 'r'),
        open('Syntax/EstimationSyntax.tex', 'r'),open('Syntax/OutputSyntax.tex', 'r')]
OUTFILE = open('QuickReference.tex', 'w')

OUTFILE.write("\section{Quick Reference\label{sec:quick-reference}}\n\n")

for i in range(len(FILE)):
  for line in FILE[i]:
    # strip white space at start & end
    line = line.strip()
    # if a line has a label, then delete it
    find = string.find(line,'\label')
    # if line if not blank, add a closing bracket
    if line != "":
      line = line[0:find] + "}"
    # recode subsections, subsubsection to be excluded from the contents
    if line[1:11] == "subsection" :
      line = "\subsection*" + line[11:]
    if line[1:14] == "subsubsection" :
      line = "\subsubsection*" + line[14:]
    # keep line only if it is a section, defCom, defComlab, defComArg, or defSub
    if ( line[1:8]=="section" or line[1:11]=="subsection" or line[1:14]=="subsubsection"
         or line[1:7]=="defCom" or line[1:7]=="defSub") :
      OUTFILE.write(line)
      OUTFILE.write('\n')
