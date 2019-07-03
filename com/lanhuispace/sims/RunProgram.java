package com.lanhuispace.sims;

public class RunProgram implements Runnable
{
	@Override
	public synchronized void run()
	{
		try {
			MainWindow window = new MainWindow();
			//window.mJFrame.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}