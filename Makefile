#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
#
CC = javac 
RM = rm -rf 

all:
	gcc -mwindows main.c -o sims.exe
	$(CC)  -encoding utf8 Main.java
	
clean:
	$(RM) Main *.exe *.o *.so *.class com/lanhuispace/sims/*.class