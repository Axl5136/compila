BYACCJ = ./byaccj

all: compile

Parser.java: forma.y
	$(BYACCJ) -J forma.y

compile: Parser.java
	javac *.java

run: compile
	java Parser

clean:
	rm -f Parser.java ParserVal.java *.class y.output
