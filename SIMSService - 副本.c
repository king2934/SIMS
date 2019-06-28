#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define SERVICE_NAME "SIMSService"
#define SLEEP_TIME 500

int isRuning = 0;

SERVICE_STATUS ServiceStatus; //服务的状态处理
SERVICE_STATUS_HANDLE ServiceHandle; //服务控制处理

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
	char* file_name = "logs/logs.txt";
	FILE* fp = NULL; // 文件指针
	fopen_s(&fp, file_name, "a+");
	fputs("logs", fp);
	fclose(fp);
	return 0;
}

/**
*** 启动日志记录
**/
int logs_start()
{
	char * file_name = "logs/runing.txt";
	FILE * fp = fopen(file_name,"w+");
	
	char str_datetime[19]={0};
	get_datetime(str_datetime);
	
	char* sm =" 正常启动...";
	char runing[]={0};
	
	strncat(runing,str_datetime,sizeof(str_datetime));
	strncat(runing,sm,strlen(sm));
	
	fputs(runing, fp);
	fclose(fp);
	return 0;
}
//日志记录 启动失败
int log_start_failed()
{
	char * file_name = "logs/error.txt";
	FILE * fp = fopen(file_name,"a+");
	
	char str_datetime[19]={0};
	get_datetime(str_datetime);
	
	char* sm =" 服务初始化失败...";
	char runing[]={0};
	
	strncat(runing,str_datetime,sizeof(str_datetime));
	strncat(runing,sm,strlen(sm));
	
	fputs(runing, fp);
	fclose(fp);
	return 0;
}

//日志记录 启动初始化成功
int log_start_success()
{
	//char RuningPath[80];
	//getcwd(RuningPath,sizeof(runPath));
	
	//strncat(RuningPath,"\\logs\\success.txt",strlen(RuningPath));
	
	char * file_name = "logs.txt";
	FILE * fp = fopen(file_name,"a+");

	fputs("logs\n", fp);
	fclose(fp);
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
		printf("现在的时间是... \n");
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
	// ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	// ServiceStatus.dwWin32ExitCode= 0;
	// switch(request)
	// {
		// case SERVICE_CONTROL_STOP:
			// isRuning = 0;
			// ServiceStatus.dwCurrentState = SERVICE_STOPPED;
			// break;
		// case SERVICE_CONTROL_SHUTDOWN:
			// isRuning = 0;
			// ServiceStatus.dwCurrentState = SERVICE_STOPPED;
			// break;
		// default:
			// break;
	// }
	// SetServiceStatus(ServiceHandle, &ServiceStatus);
	// return;
	
	//响应服务控制台的消息 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwWin32ExitCode= 0;
	if(SERVICE_CONTROL_STOP==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
    if(SERVICE_CONTROL_SHUTDOWN==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
	
    SetServiceStatus(ServiceHandle,&ServiceStatus);
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
	ServiceStatus.dwServiceType = SERVICE_WIN32; //Win32 服务 SERVICE_WIN32_OWN_PROCESS|SERVICE_WIN32_SHARE_PROCESS
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING; //开始状态为 正在初始化
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;// 关机|停止
	
	ServiceStatus.dwWin32ExitCode = 0;//退出服务时
	ServiceStatus.dwServiceSpecificExitCode = 0;// 终止服务并报告退出细节时
	
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	
	ServiceHandle = RegisterServiceCtrlHandlerA(TEXT(SERVICE_NAME), ControlHandler);//为服务注册控制处理器 （服务名和控制处理器函数指针）
	
	if ( ServiceHandle==0 ) {
		//log_start_failed();//日志记录 启动初始化失败
		
		//注册服务失败 //向SCM 报告运行状态
        ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
		ServiceStatus.dwWin32ExitCode= -1; 
		SetServiceStatus(ServiceHandle,&ServiceStatus); 
	}else{
		log_start_success();//日志记录 启动初始化成功
		//向SCM 报告运行状态
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    	SetServiceStatus(ServiceHandle,&ServiceStatus);
	}
	
	//whileRuningService();//循环运行的服务
}

/**
*** 入口函数
***/
int main()
{
	/*
	** 初始化一个SERVICE_TABLE_ENTRY 分派表结构体
	** 然后调用StartServiceCtrlDispatcher()调用进程的主线程转换为控制分派器
	** 分派器启动一个新线程，该线程运行分派表中对应于你的服务的ServiceMain（）函数
	** 在这之后系统将自动创建一个线程去执行ServiceMain函数的内容
	*/
	SERVICE_TABLE_ENTRYA ServiceTableEntry[2];
	ServiceTableEntry[0].lpServiceName = TEXT(SERVICE_NAME);//SERVICE_NAME;
    ServiceTableEntry[0].lpServiceProc = ServiceMain;
	ServiceTableEntry[1].lpServiceName = NULL;
    ServiceTableEntry[1].lpServiceProc = NULL;
	StartServiceCtrlDispatcherA(ServiceTableEntry);//启动服务的控制分派机线程
	printf("main\n");
	return 0;
}