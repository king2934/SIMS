#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/**
*** 服务安装
**/
int install()
{
	char basePath[256];
	char simsPath[256];
	char db_Path[256];
	char db_conf[256];
	
	getcwd(basePath,sizeof(basePath));
	
	strcpy(simsPath,basePath);
	strcat(simsPath,"\\SIMSService.exe");
	
	strcpy(db_Path,basePath);
	strcat(db_Path,"\\db\\mariadb\\bin\\mysqld.exe ");
	
	strcpy(db_conf,basePath);
	strcat(db_conf,"\\db\\mariadb\\my.ini ");
	
	
	/**
	*** SIMSService 服务
	**/
	char	sc_sims[1024],
			sc_sims_config[1024],
			sc_db[1024],
			sc_db_config[1024];
	
	strcpy(sc_sims,"sc create SIMSService displayname= SIMSService depend= Tcpip start= auto ");
	strcat(sc_sims,"binpath=\"");
	strcat(sc_sims,simsPath);
	strcat(sc_sims," --service ");
	strcat(sc_sims,"\"");
	
	strcpy(sc_sims_config,"sc config SIMSService  binpath=\"");
	strcat(sc_sims_config,simsPath);
	strcat(sc_sims_config," --service ");
	strcat(sc_sims_config,"\"");
	
	
	strcpy(sc_db,"sc create SIMSDB displayname= SIMSDB depend= Tcpip start= auto ");
	strcat(sc_db,"binpath=\"");
	strcat(sc_db,db_Path);
	strcat(sc_db," --defaults-file=");
	strcat(sc_db,db_conf);
	strcat(sc_db," SIMSDB ");
	strcat(sc_db,"\"");
	
	strcpy(sc_db_config,"sc config SIMSDB  binpath=\"");
	strcat(sc_db_config,db_Path);
	strcat(sc_db_config," --defaults-file=");
	strcat(sc_db_config,db_conf);
	strcat(sc_db_config," SIMSDB ");
	strcat(sc_db_config,"\"");
	
	WinExec(sc_sims,SW_HIDE);//system(sc_sims);	
	WinExec(sc_sims_config,SW_HIDE);//system(sc_sims_config);
	WinExec(sc_db,SW_HIDE);//system(sc_db);
	WinExec(sc_db_config,SW_HIDE);//system(sc_db_config);
	WinExec("sc description SIMSDB \"SIMSDB数据\"",SW_HIDE);
	WinExec("sc description SIMSService \"SIMS服务\"",SW_HIDE);
	
	WinExec("net start SIMSService",SW_HIDE);
	WinExec("net start SIMSDB",SW_HIDE);
}

/**
*** 服务卸载
**/
int uninstall()
{
	WinExec("net stop SIMSService",SW_HIDE);
	WinExec("net stop SIMSDB",SW_HIDE);
	WinExec("sc delete SIMSService",SW_HIDE);
	WinExec("sc delete SIMSDB",SW_HIDE);
}

/**
*** 主函数
**/
int main(int argc, char *argv[])
{
	if(argc>1){
		if(stricmp(argv[1],"--install")==0){
			install();
		}else if(stricmp(argv[1],"--uninstall")==0){
			uninstall();
		}else{
			printf("参数没有对上，执行默认\n");
		}
	}else{
		WinExec("jdk/bin/java -jar sims.jar",SW_HIDE);//jdk/bin/java
	}
	return 0;
}