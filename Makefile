#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
#
CC = javac 
RM = rm -rf

#gcc -mwindows main.c -o sims.exe
all:
	$(CC)  -encoding utf8 Main.java
exe:
	windres icon.rc -o icon.o
	gcc -mwindows main.c icon.o -o sims.exe
clean:
	$(RM) Main *.o *.so *.class com/lanhuispace/sims/*.class
clear:
	$(RM) *.exe *.o