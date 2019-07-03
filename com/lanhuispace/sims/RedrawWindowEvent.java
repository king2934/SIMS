package com.lanhuispace.sims;

import javax.swing.*; 
import java.awt.*; 
import java.awt.event.MouseAdapter; 
import java.awt.event.MouseEvent;

public class RedrawWindowEvent extends MouseAdapter
{
	public MainWindow mContext;
	public JLabel mJLabel;
	
	public RedrawWindowEvent(MainWindow context)
	{
		this.mContext = context;
	}
	
	public RedrawWindowEvent(MainWindow context,JLabel label)
	{
		this.mContext = context;
		this.mJLabel = label;
	}
	
	/**
	*** 在组件上按下鼠标按钮时调用。
	**/
	@Override
	public void mousePressed(MouseEvent e){
		//e.getLocationOnScreen();
		this.mJLabel.setText("mousePressed");
	}
}