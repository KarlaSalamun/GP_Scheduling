DOT = $(wildcard *.dot)
PDF = $(patsubst %.dot, %.pdf, $(DOT))
PNG = $(patsubst %.dot, %.png, $(DOT))


%.pdf: %.dot
	dot -Tpdf $^ -o $@

%.png: %.dot
	dot -Tpng $^ -o $@

pdf: $(PDF)

png: $(PNG)
