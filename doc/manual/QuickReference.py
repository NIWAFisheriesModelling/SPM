import string
import re
p = re.compile('\{\w+',re.IGNORECASE)

FILE = [open('Syntax/GeneralSyntax.tex', 'r'),
        open('Syntax/PopulationSyntax.tex', 'r'),
        open('Syntax/EstimationSyntax.tex', 'r'),
        open('Syntax/ObservationSyntax.tex', 'r'),
        open('Syntax/OutputSyntax.tex', 'r')]
OUTFILE = open('QuickReference.tex', 'w')
VERSION = open('SPMversion.tex', 'r')
SYNTAX_OUTFILE = open('SPM.syn', 'w')

OUTFILE.write("\section{Quick reference\label{sec:quick-reference}}\n")

SYNTAX_OUTFILE.write("; TextPad syntax definitions for SPM version ")
SYNTAX_OUTFILE.write(VERSION.read())
SYNTAX_OUTFILE.write("; ===================================================================================\n;\n;\n")
SYNTAX_OUTFILE.write("C=1\n")
SYNTAX_OUTFILE.write("[Syntax]\n")
SYNTAX_OUTFILE.write("Namespace1 = 6\n")
SYNTAX_OUTFILE.write("IgnoreCase = Yes\n")
SYNTAX_OUTFILE.write("KeyWordLength = 0\n")
SYNTAX_OUTFILE.write("BracketChars = ([])\n")
SYNTAX_OUTFILE.write("OperatorChars = -+*/!~%^&|=$:!_<>\n")
SYNTAX_OUTFILE.write("PreprocStart =\n")
SYNTAX_OUTFILE.write("HexPrefix = 0x\n")
SYNTAX_OUTFILE.write("SyntaxStart =\n")
SYNTAX_OUTFILE.write("SyntaxEnd =\n")
SYNTAX_OUTFILE.write("CommentStart = {\n")
SYNTAX_OUTFILE.write("CommentEnd = }\n")
SYNTAX_OUTFILE.write("CommentStartAlt =\n")
SYNTAX_OUTFILE.write("CommentEndAlt =\n")
SYNTAX_OUTFILE.write("SingleComment = #\n")
SYNTAX_OUTFILE.write("SingleCommentCol =\n")
SYNTAX_OUTFILE.write("SingleCommentAlt = @comment\n")
SYNTAX_OUTFILE.write("SingleCommentColAlt =\n")
SYNTAX_OUTFILE.write("SingleCommentEsc =\n")
SYNTAX_OUTFILE.write("StringsSpanLines = No\n")
SYNTAX_OUTFILE.write("StringStart = \"\n")
SYNTAX_OUTFILE.write("StringEnd = \"\n")
SYNTAX_OUTFILE.write("StringAlt =\n")
SYNTAX_OUTFILE.write("StringEsc = \\ \n")
SYNTAX_OUTFILE.write("CharStart = '\n")
SYNTAX_OUTFILE.write("CharEnd = '\n")
SYNTAX_OUTFILE.write("CharEsc = \\ \n")

Keywords1 = []
Keywords2 = []
Keywords3 = ["F","False","T","True"]
Keywords4 = []
Keywords5 = []
Keywords6 = []

for i in range(len(FILE)):
  count=0
  for line in FILE[i]:
    # strip white space at start & end
    line = line.strip()
    # if a line has a label, then delete it
    find = string.find(line,'\label')
    # if line if not blank, add a closing bracket
    if line != "":
      line = line[0:find] + "}"
    # recode subsections, subsubsection to be excluded from the contents
    if line[1:14] == "subsubsection" :
      mat = string.find(line,']')+1
      line = "\\par\\textbf" + line[mat:] + "\\par"
    if line[1:11] == "subsection" :
      line = "\\subsubsection" + line[11:]
      line = ""
    if line[1:8] == "section" :
      line = "\\subsection" + line[8:]
    # keep line only if it is a section, defCom, defComlab, defComArg, or defSub
    if (line[1:11]=="subsection" or line[1:14]=="subsubsection" or line[1:11]=="par\\textbf" or line[1:7]=="defCom" or line[1:7]=="defSub") :
      if (line[1:11]=="subsection") :
        count=0
      if (line[1:7]=="defCom") :
        m = p.search(line)
        Keywords1.append("@" + m.group()[1:])
        if (count!=0):
          line = "\\par " + line
        else:
          count=1
        if(i > 0):
          line = line + "\\par"
      if (line[1:7]=="defSub") :
        m = p.search(line)
        Keywords2.append(m.group()[1:])

      OUTFILE.write(line)
      OUTFILE.write('\n')

Keywords1 = list(set(Keywords1))
Keywords2 = list(set(Keywords2))
Keywords3 = list(set(Keywords3))
Keywords4 = list(set(Keywords4))
Keywords5 = list(set(Keywords5))
Keywords6 = list(set(Keywords6))
Keywords1.sort()
Keywords2.sort()
Keywords3.sort()
Keywords4.sort()
Keywords5.sort()
Keywords6.sort()

SYNTAX_OUTFILE.write("\n[Keywords 1]\n")
for i in Keywords1 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")

SYNTAX_OUTFILE.write("\n[Keywords 2]\n")
for i in Keywords2 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")

SYNTAX_OUTFILE.write("\n[Keywords 3]\n")
for i in Keywords3 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")

SYNTAX_OUTFILE.write("\n")
SYNTAX_OUTFILE.write("\n[Keywords 4]\n")
for i in Keywords4 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")

SYNTAX_OUTFILE.write("\n[Keywords 5]\n")
for i in Keywords5 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")

SYNTAX_OUTFILE.write("\n[Preprocessor keywords]\n")
for i in Keywords6 :
  SYNTAX_OUTFILE.write(i)
  SYNTAX_OUTFILE.write("\n")
