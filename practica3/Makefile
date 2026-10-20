Gram = y.tab.c y.tab.h

all: $(Gram)
	gcc -o conj y.tab.c conjunto.c symbol.c init.c
	@echo Compiled

$(Gram): conjunto.y hoc.h conjunto.h
	bison -y -d conjunto.y

clean:
	rm -f *.tab.* conj y.output
	@echo Clean
