package com.lanhuispace.sims;

import javax.swing.*;
import javax.swing.border.*;

import java.awt.*;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

public class MainWindow extends JFrame
{
	public JPanel jp_north;		//up
	public JPanel jp_south;		//down
	public JPanel jp_west;		//left
	public JPanel jp_east;		//right
	public JPanel jp_center;	//center
	
	public Image imageIcon;
	
	public MainWindow()
	{
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		int width=800,height=600;
		this.jp_north = new JPanel();//up
		this.jp_south = new JPanel();//down
		this.jp_west = new JPanel();//left
		this.jp_east = new JPanel();//right
		this.jp_center = new JPanel();//center
		
		this.jp_north.setPreferredSize(new Dimension(width,40));
		this.jp_south.setPreferredSize(new Dimension(width,20));
		this.jp_west.setPreferredSize(new Dimension(160,height));
		this.jp_east.setPreferredSize(new Dimension(0,height));
		
		this.jp_north.setBackground(Color.orange);
		this.jp_south.setBackground(new Color(200,66,200,255));
		this.jp_west.setBackground(new Color(200,66,88,255));
		this.jp_east.setBackground(new Color(200,36,12,255));
		this.jp_center.setBackground(Color.red);
		
		this.imageIcon = Toolkit.getDefaultToolkit().getImage("images/icon.png");
		
		this.setTitle("SIMS");
		this.setSize(width,height);//w,h
		this.setLocationRelativeTo(null);//居中
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setIconImage(this.imageIcon);
		this.setUndecorated(false);//默认的边框
		this.setLayout(new BorderLayout());//边界布局 东西南北中（上左中右下）
		this.setBackground(Color.white);
		this.getContentPane().setBackground(new Color(200,200,200,1));
		
		/**
		*** 容器中添加组件
		**/
		
		/**
		*** 菜单
		**/
		MainMenu mm = new MainMenu();
		mm.getComponent().setBackground(Color.white);//背景色
		mm.setBorderPainted(false);//边框线
		mm.setBorder(new CompoundBorder(mm.getBorder(),new EmptyBorder(1,0,1,0)));
		this.jp_north.add(mm);//this.setJMenuBar(mm);//添加菜单
		
		JLabel label = new JLabel("我是一个标签",JLabel.CENTER) ;   // 实例化标签对象
		label.setSize(200, 0);
		this.jp_center.add(label);
		
		/**
		***
		**/
		JButton btn1 = new JButton("快捷菜单一");
		JButton btn2 = new JButton("快捷菜单二");
		JButton btn3 = new JButton("快捷菜单三");
		JButton btn4 = new JButton("快捷菜单四");
		JButton btn5 = new JButton("快捷菜单五");
		
		this.jp_west.add(btn1);
		this.jp_west.add(btn2);
		this.jp_west.add(btn3);
		this.jp_west.add(btn4);
		this.jp_west.add(btn5);
		
		
		/************************************************************************/
		RedrawWindowEvent rwe = new RedrawWindowEvent(this,label);//窗口重绘 大小resize
		this.addMouseListener(rwe);
		this.addMouseMotionListener(rwe);
		
		this.add(jp_south,BorderLayout.SOUTH);//南边
		this.add(jp_north,BorderLayout.NORTH);//北边
		this.add(jp_center,BorderLayout.CENTER);//中间
		this.add(jp_west,BorderLayout.WEST);//西边
		this.add(jp_east,BorderLayout.EAST);//东边

		this.setVisible(true);
	}
}