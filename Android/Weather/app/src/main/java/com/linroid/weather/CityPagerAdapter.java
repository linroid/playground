package com.linroid.weather;

import android.database.Cursor;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.app.FragmentTransaction;
import android.util.SparseArray;
import android.view.ViewGroup;

import com.linroid.weather.model.Weather;

import java.util.ArrayList;
import java.util.List;

import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class CityPagerAdapter extends FragmentPagerAdapter {
    private List<Weather> weathers = new ArrayList<>();

    SparseArray<Fragment> fragments = new SparseArray<>();
    FragmentManager fm;
    public CityPagerAdapter(FragmentManager fm) {
        super(fm);
        this.fm = fm;
    }

    @Override
    public Fragment getItem(int position) {
        Weather weather = weathers.get(position);
        Fragment fragment = WeatherFragment.newInstance(weather);
        fragments.put(position, fragment);
        return fragment;
    }
    @Override
    public int getCount() {
        return weathers.size();
    }

    @Override
    public int getItemPosition(Object object) {
        return POSITION_NONE;
    }

    public void setCursor(Cursor cursor){
        int count = cursor==null ? 0 : cursor.getCount();
        Timber.d("cursor count : %d", count);
        weathers.clear();
        if(count==0){
            return;
        }
        for (int i=0; i<count; i++){
            cursor.moveToPosition(i);
            Weather weather = Weather.fromCursor(cursor);
            weathers.add(weather);
        }
//        removeALlFragments();
        notifyDataSetChanged();
    }

    @Override
    public Object instantiateItem(ViewGroup container, int position) {
        WeatherFragment fragment = (WeatherFragment) super.instantiateItem(container, position);
        Weather weather = weathers.get(position);
        fragment.setWeatherData(weather);
        return fragment;
    }

    private void removeALlFragments(){
        FragmentTransaction transaction = fm.beginTransaction();
        for (int i=0; i<fragments.size(); i++){
            Fragment fg = fragments.get(i);
            transaction.remove(fg);
        }
        transaction.commit();
        fragments.clear();
    }
}
