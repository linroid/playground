package com.linroid.weather;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import timber.log.Timber;

public class AuthenticatorService extends Service {
    Authenticator authenticator;
    public AuthenticatorService() {
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Timber.i("onCreate");
        authenticator = new Authenticator(this);
    }

    @Override
    public IBinder onBind(Intent intent) {
        Timber.i("onBind");
        return authenticator.getIBinder();
    }

    @Override
    public boolean onUnbind(Intent intent) {
        return super.onUnbind(intent);
    }
}
