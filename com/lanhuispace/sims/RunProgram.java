package com.lanhuispace.sims;

public class RunProgram implements Runnable
{
	@Override
	public synchronized void run()
	{
		try {
			WinMain window = new WinMain();
			window.mJFrame.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}