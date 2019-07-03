package com.lanhuispace.sims;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class RedrawWindowEvent extends MouseAdapter
{
	public MainWindow mContext;
	public JLabel mJLabel;
	
	private Point prePos,curPos,jfPos;
	private static final double Boundary = 15.0;//边界拉伸范围
	private int DragType;
	private static final int Drag_move = 1;
	private static final int Drag_up = 2;
	private static final int Drag_up_left = 3;
	private static final int Drag_up_right = 4;
	private static final int Drag_left = 5;
	private static final int Drag_right = 6;
	private static final int Drag_bottom = 7;
	private static final int Drag_bottom_left = 8;
	private static final int Drag_bottom_right = 9;
	
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
		prePos = e.getLocationOnScreen();
		this.mJLabel.setText("mousePressed");
	}
	
	/**
	*** 将鼠标光标移动到组件但未按下任何按钮时调用。
	**/
	@Override
	public void mouseMoved(MouseEvent e){ 
		ReSizeScale(e.getPoint());
	}
	
	/**
	*** 在组件上按下鼠标按钮然后拖动时调用。
	**/
	@Override
	public void mouseDragged(MouseEvent e){ 
		curPos = e.getLocationOnScreen();
		jfPos = this.mContext.getLocation();
		dragAction();
		prePos = curPos;
	}
	
	/**
	*** void mouseClicked(MouseEvent e)			在组件上单击(按下并释放)鼠标按钮时调用。
	*** void mouseEntered(MouseEvent e)			鼠标进入组件时调用。
	*** void mouseExited(MouseEvent e)			鼠标退出组件时调用。
	*** void mouseReleased(MouseEvent e)		在组件上释放鼠标按钮时调用。
	*** void mouseWheelMoved(MouseWheelEvent e)	旋转鼠标滚轮时调用。
	**/
	
	public boolean ReSizeScale(Point p)
	{
		double X = p.getX();
		double Y = p.getY();
		double W = this.mContext.getWidth();
		double H = this.mContext.getHeight();
		
		if( X <= Boundary && Y <= Boundary ){ 
			this.DragType = Drag_up_left;
			this.mContext.setCursor(new Cursor(Cursor.NW_RESIZE_CURSOR));
		}else if( X > Boundary && X < (W-Boundary) && Y <= Boundary ){ 
			this.DragType = Drag_up;
			this.mContext.setCursor(new Cursor(Cursor.N_RESIZE_CURSOR));
		}else if( X >=(W-Boundary) && Y<=Boundary ){
			this.DragType = Drag_up_right;
			this.mContext.setCursor(new Cursor(Cursor.NE_RESIZE_CURSOR));
		}else if( X<=Boundary  && Y<(H-Boundary) && Y>Boundary ){ 
			this.DragType = Drag_left;
			this.mContext.setCursor(new Cursor(Cursor.W_RESIZE_CURSOR));
		}else if(X>=(W-Boundary) && p.getY()<(H-Boundary) && Y>Boundary ){ 
			this.DragType = Drag_right;
			this.mContext.setCursor(new Cursor(Cursor.E_RESIZE_CURSOR));
		}else if( X<=Boundary && Y>=(H-Boundary) ){ 
			this.DragType = Drag_bottom_left;
			this.mContext.setCursor(new Cursor(Cursor.SW_RESIZE_CURSOR));
		}else if( X>Boundary  && X<(W-Boundary) && Y>=(H-Boundary) ){ 
			this.DragType = Drag_bottom;
			this.mContext.setCursor(new Cursor(Cursor.S_RESIZE_CURSOR));
		}else if( X>=(W-Boundary) && Y>=(H-Boundary) ){ 
			this.DragType = Drag_bottom_right;
			this.mContext.setCursor(new Cursor(Cursor.SE_RESIZE_CURSOR));
		}else{ 
			this.DragType = Drag_move;
			this.mContext.setCursor(new Cursor(Cursor.MOVE_CURSOR));
			return false;
		}
		return true;
	}
	
	private void dragAction()
	{
		int W = this.mContext.getWidth();
		int H = this.mContext.getHeight();
		
		switch(this.DragType)
		{
			case Drag_move: 
				this.mContext.setLocation(jfPos.x+curPos.x-prePos.x,jfPos.y+curPos.y-prePos.y); 
				break; 
			case Drag_up:	//x位置不变，y位置变化，并且Height变化 
				this.mContext.setLocation(jfPos.x,jfPos.y+curPos.y-prePos.y); 
				this.mContext.setSize(W, H-(curPos.y-prePos.y)); 
				break; 
			case Drag_left:	//y位置不变，x位置变化，width变化 
				this.mContext.setLocation(jfPos.x+curPos.x-prePos.x,jfPos.y); 
				this.mContext.setSize(W-(curPos.x-prePos.x), H); 
				break; 
			case Drag_right: //x,y位置不变，width变化 
				this.mContext.setLocation(jfPos.x,jfPos.y); 
				this.mContext.setSize(W+(curPos.x-prePos.x), H); 
				break; 
			case Drag_bottom: //x,y位置不变，Height变化 
				this.mContext.setLocation(jfPos.x, jfPos.y); 
				this.mContext.setSize(W, H+(curPos.y-prePos.y)); 
				break; 
			case Drag_up_left: //x,y位置均变化，h,w均变化 
				this.mContext.setLocation(jfPos.x+curPos.x-prePos.x,jfPos.y+curPos.y-prePos.y); 
				this.mContext.setSize(W-(curPos.x-prePos.x), H-(curPos.y-prePos.y)); 
				break;
			case Drag_bottom_right: //x,y位置均不变，h,w变化 
				this.mContext.setLocation(jfPos.x, 
				jfPos.y); 
				this.mContext.setSize(W+(curPos.x-prePos.x), H+(curPos.y-prePos.y)); 
				break; 
			case Drag_up_right: //x位置不变，y,w,h变化 
				this.mContext.setLocation(jfPos.x,jfPos.y+curPos.y-prePos.y); 
				this.mContext.setSize(W+(curPos.x-prePos.x), H-(curPos.y-prePos.y)); 
				break; 
			case Drag_bottom_left:// y不变，xwh变化 
				this.mContext.setLocation(jfPos.x+curPos.x-prePos.x,jfPos.y); 
				this.mContext.setSize(W-(curPos.x-prePos.x), H+(curPos.y-prePos.y)); 
				break; 
			default: 
				break; 
		} 
	}
}