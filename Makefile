PROGRAM = Main

JAVAC = javac
JAVA = java
CLASSPATH = src
RM = rm -rf

all:
	$(JAVAC) src/Main.java src/PushSwap.java src/Info.java

clean:
	$(RM) $(CLASSPATH)/*.class

2:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 2)

3:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 3)

10:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 10)

25:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 25)

100:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 100)

500:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 500)

1250:
	$(JAVA) -cp $(CLASSPATH) $(PROGRAM) $(shell shuf -i 1-2000 -n 1250)

re: clean all

.PHONY: all clean re 2 3 10 25 100 500 1250
