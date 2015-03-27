package com.linroid.weather.model;

import android.content.ContentValues;
import android.database.Cursor;
import android.os.Parcel;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.linroid.weather.provider.DataContract;

import java.util.List;

/**
 * Created by linroid on 1/25/15.
 */
public class Weather extends Result implements android.os.Parcelable {
    Integer id;
    public static Weather fromCursor(Cursor cursor){
        Gson gson = new Gson();
        Weather weather = new Weather();
        weather.id = cursor.getInt(cursor.getColumnIndex(DataContract.Weather._ID));
        weather.currentCity = cursor.getString(cursor.getColumnIndex(DataContract.Weather.COLUMN_CURRENT_CITY));
        weather.pm25 = cursor.getString(cursor.getColumnIndex(DataContract.Weather.COLUMN_PM25));

        String indexJson = cursor.getString(cursor.getColumnIndex(DataContract.Weather.COLUMN_INDEX));
        weather.index = gson.fromJson(indexJson, new TypeToken<List<Index>>(){}.getType());
        String dataJson = cursor.getString(cursor.getColumnIndex(DataContract.Weather.COLUMN_WEATHER_DATA));
        weather.weatherData = gson.fromJson(dataJson, new TypeToken<List<WeatherDatum>>(){}.getType());
        return weather;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Override
    public ContentValues toContentValues() {
        ContentValues values = super.toContentValues();
        values.put(DataContract.Weather._ID, id);
        return values;
    }


    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeValue(this.id);
        dest.writeString(this.currentCity);
        dest.writeString(this.pm25);
        dest.writeTypedList(index);
        dest.writeTypedList(weatherData);
    }

    public Weather() {
    }

    private Weather(Parcel in) {
        this.id = (Integer) in.readValue(Integer.class.getClassLoader());
        this.currentCity = in.readString();
        this.pm25 = in.readString();
        in.readTypedList(index, Index.CREATOR);
        in.readTypedList(weatherData, WeatherDatum.CREATOR);
    }

    public static final Creator<Weather> CREATOR = new Creator<Weather>() {
        public Weather createFromParcel(Parcel source) {
            return new Weather(source);
        }

        public Weather[] newArray(int size) {
            return new Weather[size];
        }
    };
}
