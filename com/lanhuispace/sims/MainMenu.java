package com.lanhuispace.sims;

import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseAdapter;
import java.awt.Font;

public class MainMenu extends JMenuBar
{
	public MainMenu()
	{
		JMenu fileMenu = new JMenu("文件");
		fileMenu.setFont(Font.decode("新宋体"));//微软雅黑 PLAIN/BOLD/ITALIC
		
		JMenu editMenu = new JMenu("编辑");
		JMenu viewMenu = new JMenu("视图");
		JMenu aboutMenu = new JMenu("关于");
		
		fileMenu.setBorderPainted(false);//边框线		
		editMenu.setBorderPainted(false);//边框线		
		viewMenu.setBorderPainted(false);//边框线		
		aboutMenu.setBorderPainted(false);//边框线		
		
		fileMenu.setBackground(Color.WHITE);//背景颜色
		fileMenu.setForeground(Color.PINK);//文字颜色
		fileMenu.setOpaque(true);
		
		JMenuItem newMenuItem = new JMenuItem("新建");		
		newMenuItem.setBackground(Color.YELLOW);
		
		fileMenu.add(newMenuItem);		
		
		// fileMenu.addMouseListener(new MouseAdapter(){
			// public void mouseEntered(MouseEvent e)
			// {
				// fileMenu.setBackground(Color.red);
			// }
		// });
		
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
	
/* 	
Menu.acceleratorDelimiter	String
Menu.acceleratorFont	Font
Menu.acceleratorForeground	Color
Menu.acceleratorSelectionForeground	Color
Menu.ActionMap	ActionMap
Menu.arrowIcon	Icon
Menu.background	Color
Menu.border	Border
Menu.borderPainted	Boolean
Menu.checkIcon	Icon
Menu.delay	Integer
Menu.disabledForeground	Color
Menu.font	Font
Menu.foreground	Color
Menu.margin	Insets
Menu.menuPopupOffsetX	Integer
Menu.menuPopupOffsetY	Integer
Menu.opaque	Boolean
Menu.selectionBackground	Color
Menu.selectionForeground	Color
Menu.shortcutKeys	int[ ]
Menu.submenuPopupOffsetX	Integer
Menu.submenuPopupOffsetY	Integer
Menu.textIconGap	Integer
Menu.useMenuBarBackgroundForTopLevel	Boolean
menuPressedItemB	Color
menuPressedItemF	Color
menuText	Color
MenuUI	String 
*/
	
}