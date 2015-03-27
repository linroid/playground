package com.linroid.weather.data;

import com.linroid.weather.model.Data;

import retrofit.Callback;
import retrofit.http.GET;
import retrofit.http.Query;

/**
 * Created by linroid on 1/25/15.
 */
public interface WeatherService {
    @GET("/telematics/v3/weather")
    Data getData(@Query("location") String cityName);

    @GET("/telematics/v3/weather")
    void getDataAsync(@Query("location") String cityName, Callback<Data> callback);
}
