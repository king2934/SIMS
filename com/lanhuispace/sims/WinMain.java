package com.lanhuispace.sims;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.border.*;

import java.awt.*;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

public class WinMain
{
	public JFrame mJFrame;
	
	/**
	 * Create the application.
	 */
	public WinMain()
	{
		initialize();
	}
	
	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		Image image = Toolkit.getDefaultToolkit().getImage("com/lanhuispace/sims/res/icon.png");
		
		mJFrame = new JFrame();
		mJFrame.setTitle("SIMS");
		mJFrame.setSize(1024,768);//w,h
		mJFrame.setLocationRelativeTo(null);//居中
		mJFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mJFrame.setIconImage(image);
		mJFrame.setUndecorated(false);//默认的边框
		//mJFrame.setBackground(Color.white);
		mJFrame.getContentPane().setBackground(new Color(200,200,200,1));
		
		MainMenu mm = new MainMenu();
		mm.getComponent().setBackground(Color.white);//背景色
		mm.setBorderPainted(false);//边框线
		Border border = mm.getBorder();
		Border margin = new EmptyBorder(1,0,1,0);
		mm.setBorder(new CompoundBorder(border,margin));		
		mJFrame.setJMenuBar(mm);
		mJFrame.setLayout(new BorderLayout());
		//mJFrame.getGraphicsConfiguration().getDevice().setFullScreenWindow(mJFrame);//setUndecorated=true	
		
		JLabel label = new JLabel("我是一个标签",JLabel.CENTER) ;   // 实例化标签对象
		label.setSize(200, 0);
		
		UtilDB db = new UtilDB();
		boolean isConnect = db.connect();
		List<Map> data = db.data("select host,user from user;");
		db.close();		
		
		if(isConnect){
			label.setText("连接成功"+data.toString());
		}else{
			label.setText("connect error");
		}
		
		//
		mJFrame.add(label);
		
		mJFrame.setVisible(true);
	}
}

















