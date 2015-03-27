package com.linroid.weather.data;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class SyncService extends Service {
    public static final String EXTRA_CITY = "city";

    private static final Object sLock = new Object();
    private static SyncAdapter syncAdapter;
    @Override
    public void onCreate() {
        super.onCreate();
        synchronized(sLock){
            if(syncAdapter==null){

                syncAdapter = new SyncAdapter(getApplication(), this, true);
            }
        }
        Timber.i("onCreate");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Timber.i("onBind");
        return syncAdapter.getSyncAdapterBinder();
    }

}
