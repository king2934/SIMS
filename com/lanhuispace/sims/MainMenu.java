package com.lanhuispace.sims;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainMenu extends JMenuBar
{
	public MainMenu()
	{
		JMenu fileMenu = new JMenu("文件");
        JMenu editMenu = new JMenu("编辑");
        JMenu viewMenu = new JMenu("视图");
        JMenu aboutMenu = new JMenu("关于");
		
		JMenuItem newMenuItem = new JMenuItem("新建");
		fileMenu.add(newMenuItem);		
		
		newMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("新建  被点击");
            }
        });
		
		this.add(fileMenu);
		this.add(editMenu);
		this.add(viewMenu);
		this.add(aboutMenu);
	}
	
	//
	
	
}