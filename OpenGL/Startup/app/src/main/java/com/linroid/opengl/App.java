package com.linroid.opengl;

import android.app.Application;

import timber.log.Timber;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class App extends Application {
    private static App sApp;

    @Override
    public void onCreate() {
        super.onCreate();
        sApp = this;
        Timber.plant(new Timber.DebugTree());
    }

    public static App get() {
        return sApp;
    }
}
