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
*** ȡ���ַ�������ʱ��
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
*** ��־��¼ д��־
**/
int WriteToLog(char* str)
{
	char* file_name = "E:\\Github\\SIMS\\logs\\logs.txt";
	FILE* fp = NULL; // �ļ�ָ��
	fopen_s(&fp, file_name, "a+");
	fputs(str, fp);
	fclose(fp);
	return 0;
}

/**
*** д��־
*** logs("\\logs\\logs.log","��־\n");
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
***��־��¼ ������ʼ���ɹ�
**/
int log_start_success()
{
	char logStr[255]={0};
	get_datetime(logStr);
	strcat(logStr," ���������ɹ���\n");
	
	logs("\\logs\\success.log",logStr);
	return 0;
}

/**
*** ��־��¼ ����ʧ��
**/
int log_start_failed()
{
	char logStr[255]={0};
	get_datetime(logStr);
	strcat(logStr," ʧ�ܣ���������ʱ�����˴���\n");
	
	logs("\\logs\\error.log",logStr);
	return 0;
}

/**
*** �������·��
**/
int log_init()
{
	logs("\\logs\\logs.log","��־\n");
	return 0;
}

/**
*** ��������������ʱ ��һЩ��ʼ��
**/
int init()
{
	char regname[] = "SYSTEM\\CurrentControlSet\\Services\\SIMSService";
	HKEY hkResult;
	int ret = RegOpenKey(HKEY_LOCAL_MACHINE,regname,&hkResult);
	char szpath[1024];
	DWORD dwSize = sizeof(szpath);
	RegQueryValueEx(hkResult,"ImagePath",NULL,NULL,(LPBYTE)szpath,&dwSize);//��ȡ����	
	strncpy(RuningPath, szpath, (dwSize-28));
	return 0;
}

/**
*** ��Ҫ���� ѭ������
**/
int whileRuningService()
{
	isRuning = 1;
	while(isRuning==1)
	{
		//char str_datetime[19]={0};
		//get_datetime(str_datetime);
		//printf("���ڵ�ʱ����... \n");
		//WriteToLog("��־��¼\n");
		Sleep(SLEEP_TIME);
	}
	return 0;
}

/**
*** ���ƴ�����
**/
void WINAPI ControlHandler(DWORD request)
{
	//��Ӧ�������̨����Ϣ 
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
*** ������Ҫ���� ѭ��
***
*** dwServiceType ��ָʾ�������ͣ����� Win32 ���񡣸�ֵ SERVICE_WIN32��
*** dwCurrentState ��ָ������ĵ�ǰ״̬����ʼ��״̬Ϊ SERVICE_START_PENDING�������ڳ�ʼ��
*** dwControlsAccepted �������֪ͨ SCM ��������ĸ���SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;�ػ���ֹͣ�������ֿ�������
*** dwWin32ExitCode �� dwServiceSpecificExitCode : ��������������ֹ���񲢱����˳�ϸ��ʱ�����á�
*** dwCheckPoint �� dwWaitHint�����������ʾ��ʼ��ĳ���������ʱҪ30�����ϡ�
*** RegisterServiceCtrlHandler���� ��Ϊ����ע����ƴ�����
**/
void WINAPI ServiceMain(DWORD argc, char* argv[])
{
	init();
    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;	//�������ַ������̨����
    ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    hStatus = RegisterServiceCtrlHandlerA(TEXT(SERVICE_NAME),ControlHandler);
    if(0==hStatus){
		log_start_failed();//��־��¼ ������ʼ��ʧ��		
    	//ע�����ʧ��
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwWin32ExitCode= -1;
		SetServiceStatus(hStatus,&ServiceStatus);
    }else{
		log_start_success();//��־��¼ ������ʼ���ɹ�
    	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    	SetServiceStatus(hStatus,&ServiceStatus);
    }
	
/*
	���е��������ע����ϡ������Ҫִ�еĴ��� 
*/

whileRuningService();

/*
	�����˳����̵ķ��� 
	ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
	ServiceStatus.dwWin32ExitCode= 0; 
	SetServiceStatus(hStatus,&ServiceStatus);//֪ͨ����������������� 
*/
	return;//���ﷵ�غ󣬳��򲻻��Զ����� 
}

/**
*** ����װ
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
	WinExec("sc description SIMSService \"SIMS����\"",SW_HIDE);
	system("net start SIMSService");
}

/**
*** ����ж��
**/
int uninstall()
{
	WinExec("sc delete SIMSService",SW_HIDE);
}

/**
*** ��ں���
***/
int main(int argc, char *argv[])
{
	/*
	** ��ʼ��һ��SERVICE_TABLE_ENTRY ���ɱ�ṹ��
	** Ȼ�����StartServiceCtrlDispatcher()���ý��̵����߳�ת��Ϊ���Ʒ�����
	** ����������һ�����̣߳����߳����з��ɱ��ж�Ӧ����ķ����ServiceMain��������
	** ����֮��ϵͳ���Զ�����һ���߳�ȥִ��ServiceMain����������
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
			printf("����û�ж��ϣ�ִ��Ĭ��\n");
		}
	}else{
		printf("û�в�����ִ��Ĭ��\n");
	}

    return 0;//���ﷵ�غ󣬳��򲻻��Զ����� 
}