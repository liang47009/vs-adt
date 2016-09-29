package com.yunfeng.mufeng;

import android.app.Application;
import android.content.Context;

public class App extends Application {

	@Override
	protected void attachBaseContext(Context base) {
		// TODO Auto-generated method stub
		super.attachBaseContext(base);
		NDKHelper.setContext(base);
	}

}
