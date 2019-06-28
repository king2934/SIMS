#include <windows.h>
#define SERVICE_NAME "SIMSService"
SERVICE_STATUS ServiceStatus; 
SERVICE_STATUS_HANDLE hStatus; 
void WINAPI ControlHandler(DWORD request)
{
	//响应服务控制台的消息 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwWin32ExitCode= 0;
	if(SERVICE_CONTROL_STOP==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
    if(SERVICE_CONTROL_SHUTDOWN==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
	
    SetServiceStatus(hStatus,&ServiceStatus);
	return;
}
void WINAPI ServiceMain(DWORD argc, char* argv[])
{	
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;	//接受两种服务控制台请求
    ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    hStatus = RegisterServiceCtrlHandlerA(TEXT(SERVICE_NAME),ControlHandler);
    if(0==hStatus){
    	//注册服务失败 
        ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
		ServiceStatus.dwWin32ExitCode= -1; 
		SetServiceStatus(hStatus,&ServiceStatus); 
    }else{
    	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    	SetServiceStatus(hStatus,&ServiceStatus);
    }
/*
	运行到这里，服务注册完毕。这里放要执行的代码 
*/
/*
	主动退出进程的方法 
	ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
	ServiceStatus.dwWin32ExitCode= 0; 
	SetServiceStatus(hStatus,&ServiceStatus);//通知服务管理器结束进程 
*/
	return;//这里返回后，程序不会自动结束 
}
// int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
// { 
	// SERVICE_TABLE_ENTRYA ServiceTable[2];
    // ServiceTable[0].lpServiceName = TEXT(SERVICE_NAME);
    // ServiceTable[0].lpServiceProc = ServiceMain;
    // ServiceTable[1].lpServiceName = 0;
    // ServiceTable[1].lpServiceProc = 0;

    // StartServiceCtrlDispatcherA(ServiceTable); 
    // return 0;//这里返回后，程序不会自动结束 
// }

int main()
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

    StartServiceCtrlDispatcherA(ServiceTable); 
    return 0;//这里返回后，程序不会自动结束 
}