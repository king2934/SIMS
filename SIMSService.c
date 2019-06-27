#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define FILE_NAME "logs/success.txt" // �ļ�����

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


int logs()
{
	char* file_name = "logs/success.txt";
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

int main()
{
	logs_start();//������־��¼
	
	int i = 0;
	while(1)
	{
		i++;		
		char runPath[80];
		getcwd(runPath,sizeof(runPath));
		//printf("Hello, World!%d pwd:%s\n",i,runPath);
		char str_datetime[19]={0};
		get_datetime(str_datetime);
		printf("���ڵ�ʱ���� %s \n", str_datetime);
		Sleep(500);
	}	
	return 0;
}