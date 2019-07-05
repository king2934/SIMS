#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
##cp -rf Main.class release/Main.class

CC = javac 
RM = rm -rf

#gcc -mwindows main.c -o sims.exe
all:
	windres icon.rc -o icon.o
	gcc -mwindows main.c icon.o -o release/sims.exe
	gcc -Wall -shared logw.c -o logw.dll
	gcc -Iinclude -Llib SIMSService.c -o release/SIMSService.exe -llibmariadb
	$(CC)  -encoding utf8 *.java
	jar cvfm release/sims.jar META-INF/MANIFEST.MF *.class com/lanhuispace/sims/*.class
	$(RM) *.jar *.exe *.o *.class com/lanhuispace/sims/*.class
clear:
	$(RM) *.jar *.exe *.o *.class com/lanhuispace/sims/*.class release/*.jar release/*.exe release/*.class