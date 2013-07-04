#!/bin/sh

rm *.aux *.bbl *.blg *.log *.out *.toc
pdflatex pbdSLAP-guide.Rnw
bibtex pbdSLAP-guide
pdflatex pbdSLAP-guide.Rnw
pdflatex pbdSLAP-guide.Rnw
pdflatex pbdSLAP-guide.Rnw
rm *.aux *.bbl *.blg *.log *.out *.toc

mv -f *.pdf ../inst/doc/
cp -f *.Rnw ../inst/doc/
