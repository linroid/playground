package com.linroid.weather;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.linroid.weather.model.Weather;
import com.linroid.weather.model.WeatherDatum;
import com.linroid.weather.data.WeatherLogoParser;
import com.linroid.weather.widget.FutureWeatherView;
import com.squareup.picasso.Picasso;

import butterknife.ButterKnife;
import butterknife.InjectView;

/**
 * Created by linroid on 1/25/15.
 */
public class WeatherFragment extends Fragment {
    public static final String ARG_WEATHER = "weather";
    Weather weather;
    @InjectView(R.id.city_name)
    TextView cityNameTV;
    @InjectView(R.id.weather_logo)
    ImageView weatherLogIV;
    @InjectView(R.id.weather_temperature)
    TextView weatherTemperatureTV;
    @InjectView(R.id.weather_wind)
    TextView windTV;
    @InjectView(R.id.weather_description)
    TextView descriptionTV;
    @InjectView(R.id.date)
    TextView dateTV;
    @InjectView(R.id.pm25)
    TextView pm25TV;
    @InjectView(R.id.future_container)
    LinearLayout futureContainer;
    @InjectView(R.id.btn_delete)
    ImageButton deleteBtn;
    View rootView;
    Picasso picasso;
    OnDeleteListener listener;
    public static WeatherFragment newInstance(Weather weather){
        Bundle args = new Bundle();
        args.putParcelable(ARG_WEATHER, weather);
        WeatherFragment fragment = new WeatherFragment();
        fragment.setArguments(args);
        return fragment;
    }
    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        listener = (OnDeleteListener) activity;
    }

    @Override
    public void onDetach() {
        super.onDetach();
        listener = null;
    }
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        weather = getArguments().getParcelable(ARG_WEATHER);
        picasso = Picasso.with(getActivity().getApplicationContext());
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.fragment_weather, container, false);
        ButterKnife.inject(this, rootView);
        setWeatherData(weather);
        return rootView;
    }
    public void setWeatherData(final Weather weather){
        this.weather = weather;
        if(rootView==null){
            return ;
        }
        cityNameTV.setText(weather.getCurrentCity());
//        picasso.load(datum.getNightPictureUrl()).into(weatherLogIV);
        deleteBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(listener !=null){
                    listener.onDelete(weather);
                }
            }
        });
        pm25TV.setText("PM25: "+weather.getPm25());

        if(weather.getWeatherData()==null || weather.getWeatherData().size()==0){
            return ;
        }
        int futureCount = weather.getWeatherData().size();
        for (int i=1; i<futureCount; i++){
            WeatherDatum futureData = weather.getWeatherData().get(i);
            FutureWeatherView futureWeatherView = new FutureWeatherView(futureContainer.getContext());
            futureContainer.addView(futureWeatherView);
            futureWeatherView.setWeather(futureData);
        }
        WeatherDatum datum = weather.getWeatherData().get(0);
        weatherLogIV.setImageResource(WeatherLogoParser.getLogoResId(datum.getWeather()));
        weatherTemperatureTV.setText(datum.getTemperature());
        windTV.setText(datum.getWind());
        descriptionTV.setText(datum.getWeather());
        dateTV.setText(datum.getDate());
    }
    public static interface OnDeleteListener{
        void onDelete(Weather weather);
    }
}
