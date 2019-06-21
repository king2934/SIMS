package com.lanhuispace.sims;

import javax.swing.JFrame;


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
		mJFrame.setSize(600,400);//w,h
		mJFrame.setLocationRelativeTo(null);//居中
		mJFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		MainMenu mm = new MainMenu();
		
		mJFrame.setJMenuBar(mm);
		
		mJFrame.setVisible(true);
	}
}

















