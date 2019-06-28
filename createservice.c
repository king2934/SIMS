#include <windows.h>
int main()
{
	WinExec("sc create SIMSService binpath=\"E:\\Github\\SIMS\\SIMSService.exe\" displayname= SIMSService depend= Tcpip start= auto ",SW_HIDE);//jdk/bin/java
	WinExec("sc config SIMSService binpath= \"E:\\Github\\SIMS\\SIMSService.exe\"",SW_HIDE);
	WinExec("sc description SIMSService \"SIMS·þÎñ\"",SW_HIDE);
	WinExec("net start SIMSService",SW_HIDE);
	return 0;
}