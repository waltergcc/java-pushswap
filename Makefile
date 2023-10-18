PROGRAM = Main

JAVAC = javac
JAVA = java
CLASSPATH = src
RM = rm -rf

all:
	$(JAVAC) src/Main.java src/PushSwap.java src/Info.java

clean:
	$(RM) $(CLASSPATH)/*.class

2: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 2)

3: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 3)

10: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 10)

25: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 25)

100: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 100)

500: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 500)

1250: all
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 1250)

.PHONY: all clean run 2 3 10 25 100 500 1250
