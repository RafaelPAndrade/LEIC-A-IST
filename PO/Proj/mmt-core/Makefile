JARNAME=mmt-core

all:
	(cd src; javac -Xlint:unchecked -encoding UTF-8 `find . -name \*.java`)
	(cd src; jar cvf ../$(JARNAME).jar `find . -name \*.class -o -name \*.java`)

clean:
	$(RM) $(JARNAME).jar `find . -name \*.class`

doc: all
	(javadoc -d ~/Downloads/docs/ -private -cp $(JARNAME).jar mmt)
