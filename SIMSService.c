#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define SERVICE_NAME "SIMSService"
#define SLEEP_TIME 500

SERVICE_STATUS ServiceStatus; 
SERVICE_STATUS_HANDLE hStatus;

int isRuning = 0;
char RuningPath[1024]={""};

/**
*** 取得字符串日期时间
**/
int get_datetime(char * str_datetime)
{
	char acYear[6] = {0};
	char acMonth[5] = {0};
	char acDay[5] = {0};
	char acHour[5] = {0};
	char acMin[5] = {0};
	char acSec[5] = {0};

	time_t now;
    struct tm* timenow;
    
    time(&now);
    timenow = localtime(&now);

    strftime(acYear,sizeof(acYear),"%Y-",timenow);
    strftime(acMonth,sizeof(acMonth),"%m-",timenow);
    strftime(acDay,sizeof(acDay),"%d ",timenow);
    strftime(acHour,sizeof(acHour),"%H:",timenow);
    strftime(acMin,sizeof(acMin),"%M:",timenow);
    strftime(acSec,sizeof(acSec),"%S",timenow);

	strncat(str_datetime, acYear, 5);
	strncat(str_datetime, acMonth, 3);
	strncat(str_datetime, acDay, 3);
	strncat(str_datetime, acHour, 3);
	strncat(str_datetime, acMin, 3);
	strncat(str_datetime, acSec, 2);
	
	return 0;
}

/**
*** 日志记录 写日志
**/
int WriteToLog(char* str)
{
	char* file_name = "E:\\Github\\SIMS\\logs\\logs.txt";
	FILE* fp = NULL; // 文件指针
	fopen_s(&fp, file_name, "a+");
	fputs(str, fp);
	fclose(fp);
	return 0;
}

/**
*** 写日志
*** logs("\\logs\\logs.log","日志\n");
**/
int logs(char* logpath,char* str)
{
	char basePath[1024]={""};
	strcpy(basePath,RuningPath);
	strcat(basePath,logpath);
	
	FILE* fp = fopen(basePath,"a+");
	fputs(str, fp);
	fclose(fp);
	return 0;
}

/**
***日志记录 启动初始化成功
**/
int log_start_success()
{
	char logStr[255]={0};
	get_datetime(logStr);
	strcat(logStr," 服务启动成功。\n");
	
	logs("\\logs\\success.log",logStr);
	return 0;
}

/**
*** 日志记录 启动失败
**/
int log_start_failed()
{
	char logStr[255]={0};
	get_datetime(logStr);
	strcat(logStr," 失败，服务启动时发生了错误。\n");
	
	logs("\\logs\\error.log",logStr);
	return 0;
}

/**
*** 服务程序路径
**/
int log_init()
{
	logs("\\logs\\logs.log","日志\n");
	return 0;
}

/**
*** 服务主程序运行时 的一些初始化
**/
int init()
{
	char regname[] = "SYSTEM\\CurrentControlSet\\Services\\SIMSService";
	HKEY hkResult;
	int ret = RegOpenKey(HKEY_LOCAL_MACHINE,regname,&hkResult);
	char szpath[1024];
	DWORD dwSize = sizeof(szpath);
	RegQueryValueEx(hkResult,"ImagePath",NULL,NULL,(LPBYTE)szpath,&dwSize);//提取内容	
	strncpy(RuningPath, szpath, (dwSize-28));
	return 0;
}

/**
*** 主要服务 循环运行
**/
int whileRuningService()
{
	isRuning = 1;
	while(isRuning==1)
	{
		//char str_datetime[19]={0};
		//get_datetime(str_datetime);
		//printf("现在的时间是... \n");
		//WriteToLog("日志记录\n");
		Sleep(SLEEP_TIME);
	}
	return 0;
}

/**
*** 控制处理器
**/
void WINAPI ControlHandler(DWORD request)
{
	//响应服务控制台的消息 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwWin32ExitCode= 0;
	
	switch(request)
	{
		case SERVICE_CONTROL_STOP:
			isRuning = 0;
			ServiceStatus.dwCurrentState=SERVICE_STOPPED;
			break;
		case SERVICE_CONTROL_SHUTDOWN:
			isRuning = 0;
			ServiceStatus.dwCurrentState=SERVICE_STOPPED;
			break;
		default:
			break;
	}
	
    SetServiceStatus(hStatus,&ServiceStatus);
	return;
}

/**
*** 服务主要函数 循环
***
*** dwServiceType ：指示服务类型，创建 Win32 服务。赋值 SERVICE_WIN32；
*** dwCurrentState ：指定服务的当前状态。初始化状态为 SERVICE_START_PENDING；即正在初始化
*** dwControlsAccepted ：这个域通知 SCM 服务接受哪个域。SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;关机和停止服务两种控制命令
*** dwWin32ExitCode 和 dwServiceSpecificExitCode : 这两个域在你终止服务并报告退出细节时很有用。
*** dwCheckPoint 和 dwWaitHint：这两个域表示初始化某个服务进程时要30秒以上。
*** RegisterServiceCtrlHandler函数 ：为服务注册控制处理器
**/
void WINAPI ServiceMain(DWORD argc, char* argv[])
{
	init();
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;	//接受两种服务控制台请求
    ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    hStatus = RegisterServiceCtrlHandlerA(TEXT(SERVICE_NAME),ControlHandler);
    if(0==hStatus){
		log_start_failed();//日志记录 启动初始化失败		
    	//注册服务失败
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwWin32ExitCode= -1;
		SetServiceStatus(hStatus,&ServiceStatus);
    }else{
		log_start_success();//日志记录 启动初始化成功
    	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    	SetServiceStatus(hStatus,&ServiceStatus);
    }
	
/*
	运行到这里，服务注册完毕。这里放要执行的代码 
*/

whileRuningService();

/*
	主动退出进程的方法 
	ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
	ServiceStatus.dwWin32ExitCode= 0; 
	SetServiceStatus(hStatus,&ServiceStatus);//通知服务管理器结束进程 
*/
	return;//这里返回后，程序不会自动结束 
}

/**
*** 服务安装
**/
int install()
{
	char RunPath[255];
	getcwd(RunPath,sizeof(RunPath));
	strcat(RunPath,"\\SIMSService.exe");
	
	char cmdStr[1024];
	strcpy(cmdStr,"sc create SIMSService ");
	strcat(cmdStr,"displayname= SIMSService depend= Tcpip start= auto ");
	strcat(cmdStr,"binpath=\"");
	strcat(cmdStr,RunPath);
	strcat(cmdStr," --service ");
	strcat(cmdStr,"\"");
	
	char cmdStrb[1024];
	strcpy(cmdStrb,"sc config SIMSService  binpath=\"");
	strcat(cmdStrb,RunPath);
	strcat(cmdStrb," --service ");
	strcat(cmdStrb,"\"");
	
	printf("%s\n",cmdStr);
	//WinExec("sc create SIMSService binpath=\"E:\\Github\\SIMS\\SIMSService.exe\" displayname= SIMSService depend= Tcpip start= auto ",SW_HIDE);
	WinExec(cmdStr,SW_HIDE);
	WinExec(cmdStrb,SW_HIDE);
	WinExec("sc description SIMSService \"SIMS服务\"",SW_HIDE);
	system("net start SIMSService");
}

/**
*** 服务卸载
**/
int uninstall()
{
	WinExec("sc delete SIMSService",SW_HIDE);
}

/**
*** 入口函数
***/
int main(int argc, char *argv[])
{
	/*
	** 初始化一个SERVICE_TABLE_ENTRY 分派表结构体
	** 然后调用StartServiceCtrlDispatcher()调用进程的主线程转换为控制分派器
	** 分派器启动一个新线程，该线程运行分派表中对应于你的服务的ServiceMain（）函数
	** 在这之后系统将自动创建一个线程去执行ServiceMain函数的内容
	*/

	SERVICE_TABLE_ENTRYA ServiceTable[2];
    ServiceTable[0].lpServiceName = TEXT(SERVICE_NAME);
    ServiceTable[0].lpServiceProc = ServiceMain;
    ServiceTable[1].lpServiceName = 0;
    ServiceTable[1].lpServiceProc = 0;
	
	if(argc>1){
		if(stricmp(argv[1],"--service")==0){
			StartServiceCtrlDispatcherA(ServiceTable);
		}else if(stricmp(argv[1],"--install")==0){
			install();
		}else if(stricmp(argv[1],"--uninstall")==0){
			uninstall();
		}else{
			printf("参数没有对上，执行默认\n");
		}
	}else{
		printf("没有参数，执行默认\n");
	}

    return 0;//这里返回后，程序不会自动结束 
}