PROGRAM = Main

JAVAC = javac
JAVA = java
CLASSPATH = src
RM = rm -rf

all:
	$(JAVAC) src/Main.java src/PushSwap.java src/Info.java

run: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM)

clean:
	$(RM) $(CLASSPATH)/*.class

.PHONY: all clean run
