package com.lanhuispace.sims;

import javax.swing.JMenuBar;
import javax.swing.JMenu;

public class MainMenu extends JMenuBar
{
	public MainMenu()
	{
		JMenu fileMenu = new JMenu("文件");
        JMenu editMenu = new JMenu("编辑");
        JMenu viewMenu = new JMenu("视图");
        JMenu aboutMenu = new JMenu("关于");
		this.add(fileMenu);
		this.add(editMenu);
		this.add(viewMenu);
		this.add(aboutMenu);
	}
}