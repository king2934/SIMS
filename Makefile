#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
#
CC = javac 
RM = rm -rf

#gcc -mwindows main.c -o sims.exe
all:
	$(CC)  -encoding utf8 Main.java
exe:
	gcc -mwindows main.c -o sims.exe
clean:
	$(RM) Main *.o *.so *.class com/lanhuispace/sims/*.class
clear:
	$(RM) *.exe