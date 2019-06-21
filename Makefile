#
#CC = D:\mingw_w64\mingw64\bin\gcc.exe
#
CC = javac 
RM = rm -rf

#gcc -mwindows main.c -o sims.exe
exe:
	gcc -mwindows main.c -o sims.exe
all:
	$(CC)  -encoding utf8 Main.java	
clean:
	$(RM) Main *.o *.so *.class com/lanhuispace/sims/*.class
clear:
	$(RM) *.exe