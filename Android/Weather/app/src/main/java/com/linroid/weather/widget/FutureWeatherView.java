package com.linroid.weather.widget;

import android.content.Context;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.linroid.weather.R;
import com.linroid.weather.model.WeatherDatum;
import com.linroid.weather.data.WeatherLogoParser;

import butterknife.ButterKnife;
import butterknife.InjectView;

/**
 * Created by linroid on 1/26/15.
 */
public class FutureWeatherView extends LinearLayout {
    @InjectView(R.id.future_logo)
    ImageView logo;

    @InjectView(R.id.future_date)
    TextView date;

    @InjectView(R.id.future_weather)
    TextView weather;

    @InjectView(R.id.future_temperature)
    TextView temperature;

    @InjectView(R.id.future_wind)
    TextView wind;

    public FutureWeatherView(Context context) {
        super(context);
        LinearLayout.LayoutParams params = new LayoutParams(-2, -2, 1.0f);
        setLayoutParams(params);
        setPadding(0, 0, 0, 10);
        setOrientation(VERTICAL);

//        setDividerPadding(10);
//        setShowDividers(SHOW_DIVIDER_MIDDLE);
//        setDividerDrawable(context.getResources().getDrawable(R.drawable.divider));

        View view = inflate(context, R.layout.merge_item_future_weather, this);
        ButterKnife.inject(this, view);
    }
    public void setWeather(WeatherDatum data){
        logo.setImageResource(WeatherLogoParser.getLogoResId(data.getWeather()));
        date.setText(data.getDate());
        weather.setText(data.getWeather());
        temperature.setText(data.getTemperature());
        wind.setText(data.getWind());
    }
}
