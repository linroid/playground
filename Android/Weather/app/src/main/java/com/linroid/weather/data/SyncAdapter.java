package com.linroid.weather.data;

import android.accounts.Account;
import android.app.Application;
import android.content.AbstractThreadedSyncAdapter;
import android.content.ContentProviderClient;
import android.content.ContentProviderOperation;
import android.content.ContentValues;
import android.content.Context;
import android.content.SyncResult;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.os.RemoteException;

import com.linroid.weather.WeatherApp;
import com.linroid.weather.model.Data;
import com.linroid.weather.model.Weather;
import com.linroid.weather.provider.DataContract;

import java.util.ArrayList;

import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class SyncAdapter extends AbstractThreadedSyncAdapter {
    WeatherService weatherService;

    public SyncAdapter(Application application, Context context, boolean autoInitialize) {
        super(context, autoInitialize);
        WeatherApp app = (WeatherApp) application;
        weatherService = app.getWeatherService();
    }

    @Override
    public void onPerformSync(Account account, Bundle extras, String authority, ContentProviderClient provider, SyncResult syncResult) {
        ArrayList<ContentProviderOperation> operations = new ArrayList<>();
        try {
            Cursor cursor = provider.query(DataContract.Weather.CONTENT_URI, null, null, null, null);
            Timber.d("cursor count:%d", cursor.getCount());
            for(int i=0; i<cursor.getCount(); i++){
                cursor.moveToPosition(i);
                Weather weather = Weather.fromCursor(cursor);
                Data data = weatherService.getData(weather.getCurrentCity());
                if (data.getResults() != null && data.getResults().size() > 0) {
                    Uri uri = DataContract.Weather.CONTENT_URI.buildUpon().appendPath(String.valueOf(weather.getId())).build();
                    Timber.i("update uri: %s", uri.toString());
                    ContentValues values = data.getResults().get(0).toContentValues();
                    ContentProviderOperation operation = ContentProviderOperation.newUpdate(uri)
                            .withValues(values)
                            .build();
                    operations.add(operation);
                    Timber.d("获取 %s 城市天气成功", data.getResults().get(0).getCurrentCity());
                } else {
                    Timber.e("(获取 %s 城市天气失败 %d)Status:%s, message:%s", weather.getCurrentCity(), data.getError(), data.getStatus(), data.getMessage());
                }
                syncResult.stats.numUpdates++;
            }

            Timber.i("同步了%d条数据", syncResult.stats.numUpdates);
        }catch(RemoteException e){
            e.printStackTrace();
        }
    }
}
