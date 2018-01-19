JAVADIR=/usr/share/java
JARNAME=mmt-app

all:
	(cd src; javac -cp ../../po-uuilib.jar:../../mmt-core/mmt-core.jar -encoding UTF-8 `find . -name \*.java`)
	(cd src; jar cvf ../$(JARNAME).jar `find . -name \*.class -o -name \*.java` )

clean:
	$(RM) $(JARNAME).jar `find . -name \*.class`
