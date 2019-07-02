package com.lanhuispace.sims;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Test
{
	public static void main(String[] args)
	{
		UtilDB db = new UtilDB();
		db.connect();
		List<Map> data = db.data("select host,user,password from user;");
		db.close();
		System.out.println("o"+data.toString() );
	}
	
	public String str()
	{
		return "Text";
	}
}