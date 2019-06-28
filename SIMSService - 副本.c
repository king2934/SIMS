#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define SERVICE_NAME "SIMSService"
#define SLEEP_TIME 500

int isRuning = 0;

SERVICE_STATUS ServiceStatus; //�����״̬����
SERVICE_STATUS_HANDLE ServiceHandle; //������ƴ���

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
	char* file_name = "logs/logs.txt";
	FILE* fp = NULL; // �ļ�ָ��
	fopen_s(&fp, file_name, "a+");
	fputs("logs", fp);
	fclose(fp);
	return 0;
}

/**
*** ������־��¼
**/
int logs_start()
{
	char * file_name = "logs/runing.txt";
	FILE * fp = fopen(file_name,"w+");
	
	char str_datetime[19]={0};
	get_datetime(str_datetime);
	
	char* sm =" ��������...";
	char runing[]={0};
	
	strncat(runing,str_datetime,sizeof(str_datetime));
	strncat(runing,sm,strlen(sm));
	
	fputs(runing, fp);
	fclose(fp);
	return 0;
}
//��־��¼ ����ʧ��
int log_start_failed()
{
	char * file_name = "logs/error.txt";
	FILE * fp = fopen(file_name,"a+");
	
	char str_datetime[19]={0};
	get_datetime(str_datetime);
	
	char* sm =" �����ʼ��ʧ��...";
	char runing[]={0};
	
	strncat(runing,str_datetime,sizeof(str_datetime));
	strncat(runing,sm,strlen(sm));
	
	fputs(runing, fp);
	fclose(fp);
	return 0;
}

//��־��¼ ������ʼ���ɹ�
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
*** ��Ҫ���� ѭ������
**/
int whileRuningService()
{
	isRuning = 1;
	while(isRuning==1)
	{
		//char str_datetime[19]={0};
		//get_datetime(str_datetime);
		printf("���ڵ�ʱ����... \n");
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
	
	//��Ӧ�������̨����Ϣ 
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	ServiceStatus.dwWin32ExitCode= 0;
	if(SERVICE_CONTROL_STOP==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
    if(SERVICE_CONTROL_SHUTDOWN==request)ServiceStatus.dwCurrentState=SERVICE_STOPPED;
	
    SetServiceStatus(ServiceHandle,&ServiceStatus);
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
	ServiceStatus.dwServiceType = SERVICE_WIN32; //Win32 ���� SERVICE_WIN32_OWN_PROCESS|SERVICE_WIN32_SHARE_PROCESS
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING; //��ʼ״̬Ϊ ���ڳ�ʼ��
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN|SERVICE_ACCEPT_STOP;// �ػ�|ֹͣ
	
	ServiceStatus.dwWin32ExitCode = 0;//�˳�����ʱ
	ServiceStatus.dwServiceSpecificExitCode = 0;// ��ֹ���񲢱����˳�ϸ��ʱ
	
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	
	ServiceHandle = RegisterServiceCtrlHandlerA(TEXT(SERVICE_NAME), ControlHandler);//Ϊ����ע����ƴ����� ���������Ϳ��ƴ���������ָ�룩
	
	if ( ServiceHandle==0 ) {
		//log_start_failed();//��־��¼ ������ʼ��ʧ��
		
		//ע�����ʧ�� //��SCM ��������״̬
        ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
		ServiceStatus.dwWin32ExitCode= -1; 
		SetServiceStatus(ServiceHandle,&ServiceStatus); 
	}else{
		log_start_success();//��־��¼ ������ʼ���ɹ�
		//��SCM ��������״̬
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    	SetServiceStatus(ServiceHandle,&ServiceStatus);
	}
	
	//whileRuningService();//ѭ�����еķ���
}

/**
*** ��ں���
***/
int main()
{
	/*
	** ��ʼ��һ��SERVICE_TABLE_ENTRY ���ɱ�ṹ��
	** Ȼ�����StartServiceCtrlDispatcher()���ý��̵����߳�ת��Ϊ���Ʒ�����
	** ����������һ�����̣߳����߳����з��ɱ��ж�Ӧ����ķ����ServiceMain��������
	** ����֮��ϵͳ���Զ�����һ���߳�ȥִ��ServiceMain����������
	*/
	SERVICE_TABLE_ENTRYA ServiceTableEntry[2];
	ServiceTableEntry[0].lpServiceName = TEXT(SERVICE_NAME);//SERVICE_NAME;
    ServiceTableEntry[0].lpServiceProc = ServiceMain;
	ServiceTableEntry[1].lpServiceName = NULL;
    ServiceTableEntry[1].lpServiceProc = NULL;
	StartServiceCtrlDispatcherA(ServiceTableEntry);//��������Ŀ��Ʒ��ɻ��߳�
	printf("main\n");
	return 0;
}