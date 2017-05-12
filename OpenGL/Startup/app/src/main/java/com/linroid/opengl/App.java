package com.linroid.opengl;

import android.app.Application;

import timber.log.Timber;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        Timber.plant(new Timber.DebugTree());
    }
}
