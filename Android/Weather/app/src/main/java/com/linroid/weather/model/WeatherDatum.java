
package com.linroid.weather.model;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;

public class WeatherDatum implements Parcelable {

    @Expose
    private String date;
    @Expose
    private String dayPictureUrl;
    @Expose
    private String nightPictureUrl;
    @Expose
    private String weather;
    @Expose
    private String wind;
    @Expose
    private String temperature;

    /**
     * 
     * @return
     *     The date
     */
    public String getDate() {
        return date;
    }

    /**
     * 
     * @param date
     *     The date
     */
    public void setDate(String date) {
        this.date = date;
    }

    /**
     * 
     * @return
     *     The dayPictureUrl
     */
    public String getDayPictureUrl() {
        return dayPictureUrl;
    }

    /**
     * 
     * @param dayPictureUrl
     *     The dayPictureUrl
     */
    public void setDayPictureUrl(String dayPictureUrl) {
        this.dayPictureUrl = dayPictureUrl;
    }

    /**
     * 
     * @return
     *     The nightPictureUrl
     */
    public String getNightPictureUrl() {
        return nightPictureUrl;
    }

    /**
     * 
     * @param nightPictureUrl
     *     The nightPictureUrl
     */
    public void setNightPictureUrl(String nightPictureUrl) {
        this.nightPictureUrl = nightPictureUrl;
    }

    /**
     * 
     * @return
     *     The weather
     */
    public String getWeather() {
        return weather;
    }

    /**
     * 
     * @param weather
     *     The weather
     */
    public void setWeather(String weather) {
        this.weather = weather;
    }

    /**
     * 
     * @return
     *     The wind
     */
    public String getWind() {
        return wind;
    }

    /**
     * 
     * @param wind
     *     The wind
     */
    public void setWind(String wind) {
        this.wind = wind;
    }

    /**
     * 
     * @return
     *     The temperature
     */
    public String getTemperature() {
        return temperature;
    }

    /**
     * 
     * @param temperature
     *     The temperature
     */
    public void setTemperature(String temperature) {
        this.temperature = temperature;
    }

    @Override
    public String toString() {
        return "WeatherDatum{" +
                "date='" + date + '\'' +
                ", dayPictureUrl='" + dayPictureUrl + '\'' +
                ", nightPictureUrl='" + nightPictureUrl + '\'' +
                ", weather='" + weather + '\'' +
                ", wind='" + wind + '\'' +
                ", temperature='" + temperature + '\'' +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(this.date);
        dest.writeString(this.dayPictureUrl);
        dest.writeString(this.nightPictureUrl);
        dest.writeString(this.weather);
        dest.writeString(this.wind);
        dest.writeString(this.temperature);
    }

    public WeatherDatum() {
    }

    private WeatherDatum(Parcel in) {
        this.date = in.readString();
        this.dayPictureUrl = in.readString();
        this.nightPictureUrl = in.readString();
        this.weather = in.readString();
        this.wind = in.readString();
        this.temperature = in.readString();
    }

    public static final Parcelable.Creator<WeatherDatum> CREATOR = new Parcelable.Creator<WeatherDatum>() {
        public WeatherDatum createFromParcel(Parcel source) {
            return new WeatherDatum(source);
        }

        public WeatherDatum[] newArray(int size) {
            return new WeatherDatum[size];
        }
    };
}
