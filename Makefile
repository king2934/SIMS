#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
#
CC = javac 
RM = rm -rf

#gcc -mwindows main.c -o sims.exe
all:
	windres icon.rc -o icon.o
	gcc -mwindows main.c icon.o -o sims.exe
	gcc SIMSService.c -o SIMSService.exe	
	$(CC)  -encoding utf8 Main.java
sc:
	gcc createservice.c -o scservice.exe
exe:
	windres icon.rc -o icon.o
	gcc -mwindows main.c icon.o -o sims.exe
service:
	gcc SIMSService.c -o SIMSService.exe
clean:
	$(RM) Main *.o *.so *.class com/lanhuispace/sims/*.class
clear:
	$(RM) *.exe *.o *.class com/lanhuispace/sims/*.class