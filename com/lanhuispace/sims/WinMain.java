package com.lanhuispace.sims;

import javax.swing.JFrame;
import java.awt.Color;


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
		mJFrame.setUndecorated(false);
		//mJFrame.setBackground(Color.white);
		mJFrame.getContentPane().setBackground(new Color(200,200,200,1));
		
		MainMenu mm = new MainMenu();
		
		mJFrame.setJMenuBar(mm);
		
		mJFrame.setVisible(true);
	}
}

















