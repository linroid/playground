package com.linroid.weather.provider;

import android.content.ContentResolver;
import android.net.Uri;
import android.provider.BaseColumns;

/**
 * Created by linroid on 1/25/15.
 */
public class DataContract {
    public static final String CONTENT_AUTHORITY = "com.linroid.weather.provider";
    public static final Uri CONTENT_URI = Uri.parse("content://"+CONTENT_AUTHORITY);
    public static final String PATH_WEATHER = "weather";
    public static final String PATH_CITIES = "cities";

    public static class City implements BaseColumns {
        public static final String CONTENT_TYPE = ContentResolver.CURSOR_DIR_BASE_TYPE+"/vnd.weather.cities";
        public static final String CONTENT_ITEM_TYPE = ContentResolver.CURSOR_ITEM_BASE_TYPE+"/vnd.weather.city";
        public static final Uri CONTENT_URI = DataContract.CONTENT_URI.buildUpon().appendPath(PATH_CITIES).build();

        public static final String TABLE_NAME = "cities";
        public static final String COLUMN_NAME = "name";
    }
    public static class Weather implements BaseColumns {
        public static final String CONTENT_TYPE = ContentResolver.CURSOR_ITEM_BASE_TYPE+"/vnd.weather.weather";
        public static final String CONTENT_ITEM_TYPE = ContentResolver.CURSOR_ITEM_BASE_TYPE+"/vnd.weather.weather";
        public static final Uri CONTENT_URI = DataContract.CONTENT_URI.buildUpon().appendPath(PATH_WEATHER).build();

        public static final String TABLE_NAME = "weather";

        public static final String COLUMN_CURRENT_CITY = "current_city";
        public static final String COLUMN_PM25 = "pm25";
        public static final String COLUMN_INDEX = "_index";
        public static final String COLUMN_WEATHER_DATA = "weather_data";
    }

}
