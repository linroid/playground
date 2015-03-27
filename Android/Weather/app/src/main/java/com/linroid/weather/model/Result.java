
package com.linroid.weather.model;

import android.content.ContentValues;
import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.Gson;
import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import com.linroid.weather.provider.DataContract;

import java.util.ArrayList;
import java.util.List;

import timber.log.Timber;

public class Result implements Parcelable {

    @Expose
    protected String currentCity;
    @Expose
    protected String pm25;
    @Expose
    protected List<Index> index = new ArrayList<Index>();
    @SerializedName("weather_data")
    @Expose
    protected List<WeatherDatum> weatherData = new ArrayList<WeatherDatum>();

    /**
     * 
     * @return
     *     The currentCity
     */
    public String getCurrentCity() {
        return currentCity;
    }

    /**
     * 
     * @param currentCity
     *     The currentCity
     */
    public void setCurrentCity(String currentCity) {
        this.currentCity = currentCity;
    }

    /**
     * 
     * @return
     *     The pm25
     */
    public String getPm25() {
        return pm25;
    }

    /**
     * 
     * @param pm25
     *     The pm25
     */
    public void setPm25(String pm25) {
        this.pm25 = pm25;
    }

    /**
     * 
     * @return
     *     The index
     */
    public List<Index> getIndex() {
        return index;
    }

    /**
     * 
     * @param index
     *     The index
     */
    public void setIndex(List<Index> index) {
        this.index = index;
    }

    /**
     * 
     * @return
     *     The weatherData
     */
    public List<WeatherDatum> getWeatherData() {
        return weatherData;
    }

    /**
     * 
     * @param weatherData
     *     The weather_data
     */
    public void setWeatherData(List<WeatherDatum> weatherData) {
        this.weatherData = weatherData;
    }

    public ContentValues toContentValues(){
        Gson gson = new Gson();
        ContentValues values = new ContentValues();
        values.put(DataContract.Weather.COLUMN_CURRENT_CITY, currentCity);
        values.put(DataContract.Weather.COLUMN_PM25, pm25);
        String indexJson = gson.toJson(this.index);
        values.put(DataContract.Weather.COLUMN_INDEX, indexJson);
        String dataJson = gson.toJson(this.weatherData);
        values.put(DataContract.Weather.COLUMN_WEATHER_DATA, dataJson);
        Timber.i(dataJson);
        return values;
    }

    @Override
    public String toString() {
        return "Result{" +
                "currentCity='" + currentCity + '\'' +
                ", pm25='" + pm25 + '\'' +
                ", index=" + index +
                ", weatherData=" + weatherData +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(this.currentCity);
        dest.writeString(this.pm25);
        dest.writeTypedList(index);
        dest.writeTypedList(weatherData);
    }

    public Result() {
    }

    private Result(Parcel in) {
        this.currentCity = in.readString();
        this.pm25 = in.readString();
        in.readTypedList(index, Index.CREATOR);
        in.readTypedList(weatherData, WeatherDatum.CREATOR);
    }

}
