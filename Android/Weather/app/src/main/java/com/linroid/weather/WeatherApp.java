package com.linroid.weather;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.Application;
import android.content.ContentResolver;

import com.linroid.weather.data.WeatherService;
import com.linroid.weather.provider.DataContract;
import com.squareup.okhttp.OkHttpClient;

import retrofit.ErrorHandler;
import retrofit.RequestInterceptor;
import retrofit.RestAdapter;
import retrofit.RetrofitError;
import retrofit.client.OkClient;
import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class WeatherApp extends Application {
    Account account;
    WeatherService weatherService;

    @Override
    public void onCreate() {
        super.onCreate();
        if(BuildConfig.DEBUG){
            Timber.plant(new Timber.DebugTree());
        }else{
            Timber.plant(new Timber.HollowTree());
        }
        account = new Account(getString(R.string.app_name), Config.ACCOUNT_TYPE);
        AccountManager am = (AccountManager) getSystemService(ACCOUNT_SERVICE);
        if(am.addAccountExplicitly(account, null, null)){
            Timber.i("add account success");
            ContentResolver.setSyncAutomatically(account, DataContract.CONTENT_AUTHORITY, true);
            ContentResolver.setIsSyncable(account, DataContract.CONTENT_AUTHORITY, 1);
            ContentResolver.setMasterSyncAutomatically(true);
        }
        initWeatherService();
    }

    private void initWeatherService() {
        RestAdapter restAdapter = new RestAdapter.Builder()
                .setEndpoint(Config.ENDPOINT)
                .setClient(new OkClient(new OkHttpClient()))
                .setLogLevel(RestAdapter.LogLevel.BASIC)
                .setErrorHandler(new ErrorHandler() {
                    @Override
                    public Throwable handleError(RetrofitError retrofitError) {
                        Timber.e(retrofitError, "访问 %s 出错", retrofitError.getUrl());
                        return retrofitError;
                    }
                })
                .setRequestInterceptor(new RequestInterceptor() {
                    @Override
                    public void intercept(RequestFacade requestFacade) {
                        requestFacade.addQueryParam("ak", Config.BAIDU_AK);
                        requestFacade.addEncodedQueryParam("mcode", Config.M_CODE);
                        requestFacade.addQueryParam("output", "json");
                    }
                })
                .build();
        weatherService = restAdapter.create(WeatherService.class);
    }

    public WeatherService getWeatherService() {
        return weatherService;
    }

    public Account getAccount() {
        return account;
    }
}
