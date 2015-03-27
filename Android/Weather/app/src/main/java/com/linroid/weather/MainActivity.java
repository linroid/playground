package com.linroid.weather;

import android.accounts.Account;
import android.app.AlertDialog;
import android.app.LoaderManager;
import android.app.ProgressDialog;
import android.content.ContentResolver;
import android.content.CursorLoader;
import android.content.DialogInterface;
import android.content.Loader;
import android.content.SyncStatusObserver;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.view.ViewPager;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import com.linroid.weather.data.WeatherService;
import com.linroid.weather.model.Data;
import com.linroid.weather.model.Result;
import com.linroid.weather.model.Weather;
import com.linroid.weather.provider.DataContract;

import butterknife.ButterKnife;
import butterknife.InjectView;
import retrofit.Callback;
import retrofit.RetrofitError;
import retrofit.client.Response;
import timber.log.Timber;


public class MainActivity extends ActionBarActivity implements SwipeRefreshLayout.OnRefreshListener, LoaderManager.LoaderCallbacks<Cursor> , AddCityFragment.OnCityAddedListener, WeatherFragment.OnDeleteListener{

    @InjectView(R.id.city_pager)
    ViewPager cityPager;
    @InjectView(R.id.refresher)
    SwipeRefreshLayout refreshLayout;

    CityPagerAdapter pagerAdapter;
    Account account;
    Object listener;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.inject(this);
        refreshLayout.setOnRefreshListener(this);
        pagerAdapter = new CityPagerAdapter(getSupportFragmentManager());
        cityPager.setAdapter(pagerAdapter);
        account = ((WeatherApp)getApplication()).getAccount();
        Timber.i("Account name:%s", account.name);
        triggerSync();
        getLoaderManager().initLoader(0, null, this);
        cityPager.setOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {

            }

            @Override
            public void onPageScrollStateChanged(int state) {
                if(state == ViewPager.SCROLL_STATE_DRAGGING){
                    refreshLayout.setEnabled(false);
                }else{
                    refreshLayout.setEnabled(true);
                }
            }
        });
    }

    public void triggerSync() {
        Bundle extras = new Bundle();
        extras.putBoolean(ContentResolver.SYNC_EXTRAS_MANUAL, true);
        extras.putBoolean(ContentResolver.SYNC_EXTRAS_EXPEDITED, true);
        ContentResolver.requestSync(account, DataContract.CONTENT_AUTHORITY, extras);
    }

    @Override
    protected void onResume() {
        super.onResume();
        listener = ContentResolver.addStatusChangeListener(ContentResolver.SYNC_OBSERVER_TYPE_PENDING | ContentResolver.SYNC_OBSERVER_TYPE_ACTIVE, mObserver);
    }

    @Override
    protected void onPause() {
        super.onPause();
        ContentResolver.removeStatusChangeListener(listener);
        listener = null;
    }

    @Override
    public void onRefresh() {
        triggerSync();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.action_add_city:
                showAddCityDialog();
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void showAddCityDialog() {
        new AddCityFragment().show(getSupportFragmentManager(), null);
    }

    @Override
    public Loader<Cursor> onCreateLoader(int id, Bundle args) {
        return new CursorLoader(this, DataContract.Weather.CONTENT_URI, null, null, null, DataContract.Weather._ID +" desc");
    }

    @Override
    public void onLoadFinished(Loader<Cursor> loader, Cursor data) {
        Timber.d("onLoadFinished, %s", data.toString());
        pagerAdapter.setCursor(data);
//        cityPager.setAdapter(null);
//        cityPager.setAdapter(pagerAdapter);
        cityPager.setCurrentItem(0);
//        cityPager.invalidate();
    }

    @Override
    public void onLoaderReset(Loader<Cursor> loader) {
        pagerAdapter.setCursor(null);
    }


    SyncStatusObserver mObserver = new SyncStatusObserver() {
        @Override
        public void onStatusChanged(int which) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    boolean isActive = ContentResolver.isSyncActive(account, DataContract.CONTENT_AUTHORITY);
                    boolean isPending = ContentResolver.isSyncPending(account, DataContract.CONTENT_AUTHORITY);
                    refreshLayout.setRefreshing(isActive || isPending);
                }
            });
        }
    };

    @Override
    public void onAddCity(String cityName) {
        final ProgressDialog dialog = new ProgressDialog(this);
        dialog.setMessage("添加中....");
        dialog.show();

        WeatherApp app = (WeatherApp) getApplication();
        WeatherService service = app.getWeatherService();
        service.getDataAsync(cityName, new Callback<Data>() {
            @Override
            public void success(Data data, Response response) {
                Result result = data.getResults().get(0);
                getContentResolver().insert(DataContract.Weather.CONTENT_URI, result.toContentValues());
//                triggerSync();
                Toast.makeText(MainActivity.this, R.string.add_city_success, Toast.LENGTH_SHORT).show();
                dialog.dismiss();
            }

            @Override
            public void failure(RetrofitError retrofitError) {
                Toast.makeText(MainActivity.this, R.string.add_city_fail, Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public void onDelete(final Weather weather) {
        AlertDialog dialog = new AlertDialog.Builder(this)
                .setTitle("确认删除 "+ weather.getCurrentCity() + "?")
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Uri uri = DataContract.Weather.CONTENT_URI.buildUpon().appendPath(String.valueOf(weather.getId())).build();
                        getContentResolver().delete(uri, null, null);
                        Toast.makeText(MainActivity.this, R.string.delete_city_fail, Toast.LENGTH_SHORT).show();
                    }
                })
                .setNegativeButton(android.R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                })
                .create();
        dialog.show();
    }
}
