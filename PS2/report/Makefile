LATEX = pdflatex
LATEXFLAGS = -shell-escape
BIBTEX = bibtex
DOCNAME = report
TWOSIDE = report-twoside
TEMPS = toc bbl blg log out lof lot lol aux pyg

.PHONY: clean remake purge

all: $(DOCNAME).pdf

%.pdf:
	$(LATEX) $(LATEXFLAGS) $*.tex
	$(BIBTEX) $*.aux
	$(LATEX) $(LATEXFLAGS) $*.tex
	$(LATEX) $(LATEXFLAGS) $*.tex

clean:
	for s in $(TEMPS); do rm -f $(DOCNAME).$$s $(TWOSIDE).$$s; done
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

purge: clean
	-rm -f $(DOCNAME).pdf
	-rm -f $(TWOSIDE).pdf

remake:
	-rm -f $(DOCNAME).pdf
	$(MAKE) all
