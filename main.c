#include <windows.h>
int main()
{
	WinExec("jdk/bin/java -classpath \".;./lib/*\" Main",SW_HIDE);//jdk/bin/java
	return 0;
}