Gram = y.tab.c y.tab.h

all: $(Gram)
	gcc -o conj y.tab.c conjunto.c
	@echo Compiled

$(Gram): conjunto.y
	bison -y -d conjunto.y

clean:
	rm -f *.tab.* conj
	@echo Clean
