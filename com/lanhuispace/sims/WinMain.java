package com.lanhuispace.sims;

import javax.swing.JFrame;
import java.awt.Color;
import javax.swing.border.*;
import java.awt.FlowLayout; 

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
		mJFrame = new JFrame();
		mJFrame.setTitle("标题");
		mJFrame.setSize(1024,768);//w,h
		mJFrame.setLocationRelativeTo(null);//居中
		mJFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mJFrame.setUndecorated(true);//默认的边框
		//mJFrame.setBackground(Color.white);
		mJFrame.getContentPane().setBackground(new Color(200,200,200,1));
		
		MainMenu mm = new MainMenu();
		mm.getComponent().setBackground(Color.white);//背景色
		mm.setBorderPainted(false);//边框线
		Border border = mm.getBorder();
		Border margin = new EmptyBorder(1,0,1,0);
		mm.setBorder(new CompoundBorder(border,margin));
		
		mJFrame.setJMenuBar(mm);
		//mJFrame.setLayout(new FlowLayout());
		mJFrame.getGraphicsConfiguration().getDevice().setFullScreenWindow(mJFrame);//setUndecorated=true	
		mJFrame.setVisible(true);		
	}
}

















