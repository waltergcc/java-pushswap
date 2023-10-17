PROGRAM = Main

JAVAC = javac
JAVA = java
JAR = jar
BINDIR = bin
SRC = src/Main.java
RM = rm -rf
MANIFEST = manifest.txt

.SUFFIXES: .java .class

.java.class:
	$(JAVAC) -d $(BINDIR) $<

all: $(SRC:.java=.class)

run: all
	$(JAVA) -cp $(BINDIR) $(PROGRAM)

clean:
	$(RM) $(BINDIR)

fclean: clean
	$(RM) $(PROGRAM).jar

$(MANIFEST):
	echo "Main-Class: $(PROGRAM)" > $@

jar: $(MANIFEST)
	$(JAR) cvf $(PROGRAM).jar $(MANIFEST) -C $(BINDIR) .

.PHONY: all clean run jar
