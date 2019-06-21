package com.lanhuispace.sims;

import java.util.Properties;
import java.util.HashMap;
import java.util.Map;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;

public class ConfigDB
{
	//配置文件
	private static final String conf = "config.properties";
	
	private Map<String,String> configMap;
	
	// 入口
	public static void main(String[] args)
	{
		System.out.println("this class Config.");
		ConfigDB cdb = new ConfigDB();
	}
	
	//初始化
	public ConfigDB()
	{
		this.configMap = new HashMap<String,String>();
		this.checkConfig();
	}
	
	//
	private void checkConfig()
	{
		File cf = new File(this.conf);
		if ( cf.exists() ){
			if( cf.length() > 0 ){
				this.readConfig();
			}else{
				this.initConfig();
			}
		}else{
			try{
				cf.createNewFile();
				this.initConfig();
			}catch(IOException e){
				//e.printStackTrace();
				System.out.println("创建新配置文件出错。");
			}
		}
	}
	
	// 读取配置文件
	private void readConfig()
	{
		Properties prop = new Properties();
		try
		{
			InputStream is = new BufferedInputStream (new FileInputStream(this.conf));
			is = this.InputStreamS(is);
			prop.load(is);
			this.configMap.put("HostName",prop.getProperty("hostname"));
			this.configMap.put("HostPort",prop.getProperty("hostport"));
			this.configMap.put("UserName",prop.getProperty("username"));
			this.configMap.put("PassWord",prop.getProperty("password"));
			this.configMap.put("DataBase",prop.getProperty("database"));
			is.close();
		}
		catch(Exception e)
		{
			//e.printStackTrace();
			System.out.println("读取配置文件时发生了错误");
		}
	}
	
	//处理大小写问题
	private InputStream InputStreamS(InputStream is)
	{
		String str = this.InputStreamToString(is);
		return this.StringToInputStream(str);
	}
	
	//字符转InputStream
	private InputStream StringToInputStream(String str)
	{
		ByteArrayInputStream stream = new ByteArrayInputStream(str.getBytes());
		return stream;
	}
	
	// InputStream转字符串
	private String InputStreamToString(InputStream is)
	{
		String result = "" , lineStr = "" ;
		
		try
		{
			BufferedReader reader = new BufferedReader(new InputStreamReader(is));
			while ((lineStr = reader.readLine()) != null) {
				result += this.LowerCaseString(lineStr)+"\n";
			}
		}
		catch(IOException e)
		{
			//e.printStackTrace();
		}
		return result;
	}
	
	
	//内容转小写
	private String LowerCaseString(String lineData)
	{
        String result = "";
        if (lineData.contains("=")) {
            String[] str = lineData.split("=");
            result = str[0].toLowerCase()+"="+str[1];
        } else {
            result = lineData;
        }
		return result;
    }

	// 初始化配置文件
	private void initConfig()
	{
		Properties prop = new Properties();
		try
		{
			FileOutputStream fos = new FileOutputStream(this.conf);
			prop.setProperty("HostName", "localhost");
			prop.setProperty("HostPort", "3306");
			prop.setProperty("UserName", "root");
			prop.setProperty("PassWord", "king2934");
			prop.setProperty("DataBase", "mysql");
			prop.store(fos, "The " + this.conf + " file is MariaDB Config.");
			fos.close();
		}
		catch(Exception e)
		{
			//e.printStackTrace();
			System.out.println("初始化配置文件准备生成时发生了错误");
		}
	}
	
	//
	public Map<String,String> getConfig()
	{
		this.readConfig();
		return this.configMap;
	}
	
}