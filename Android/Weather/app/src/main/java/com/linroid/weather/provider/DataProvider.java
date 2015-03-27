package com.linroid.weather.provider;

import android.content.ContentProvider;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentValues;
import android.content.Context;
import android.content.OperationApplicationException;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;

import java.util.ArrayList;

import timber.log.Timber;

/**
 * Created by linroid on 1/25/15.
 */
public class DataProvider extends ContentProvider {
    private static UriMatcher sUriMatcher;
    public static final int ROUTE_CITIES = 0x1;
    public static final int ROUTE_CITY_ID = 0x2;
    public static final int ROUTE_WEATHER = 0x3;
    public static final int ROUTE_WEATHER_ID = 0x4;
    static {
        sUriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        sUriMatcher.addURI(DataContract.CONTENT_AUTHORITY, DataContract.PATH_CITIES, ROUTE_CITIES);
        sUriMatcher.addURI(DataContract.CONTENT_AUTHORITY, DataContract.PATH_CITIES+"/*", ROUTE_CITY_ID);
        sUriMatcher.addURI(DataContract.CONTENT_AUTHORITY, DataContract.PATH_WEATHER, ROUTE_WEATHER);
        sUriMatcher.addURI(DataContract.CONTENT_AUTHORITY, DataContract.PATH_WEATHER +"/*", ROUTE_WEATHER_ID);
    }

    SQLiteOpenHelper openHelper;

    @Override
    public boolean onCreate() {
        openHelper = new WeatherDatabase(getContext());
        return true;
    }

    @Override
    public String getType(Uri uri) {
        String type;
        switch (sUriMatcher.match(uri)){
            case ROUTE_CITIES:
                type = DataContract.City.CONTENT_ITEM_TYPE;
                break;
            case ROUTE_CITY_ID:
                type = DataContract.City.CONTENT_TYPE;
                break;
            case ROUTE_WEATHER:
                type = DataContract.Weather.CONTENT_TYPE;
                break;
            case ROUTE_WEATHER_ID:
                type = DataContract.Weather.CONTENT_ITEM_TYPE;
                break;
            default:
                throw new UnsupportedOperationException("not implements yet");

        }
        return type;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
        int match = sUriMatcher.match(uri);
        SQLiteDatabase db = openHelper.getReadableDatabase();
        Cursor cursor = null;
        switch (match){
            case ROUTE_CITIES: {
                String id = uri.getLastPathSegment();
                cursor = db.query(DataContract.City.TABLE_NAME, projection, DataContract.City._ID+"=?", new String[]{id}, null, null, null);
                break;
            }
            case ROUTE_CITY_ID:{
                cursor = db.query(DataContract.City.TABLE_NAME, projection, selection, selectionArgs, null, null, null);
                cursor.setNotificationUri(getContext().getContentResolver(), uri);
                break;
            }
            case ROUTE_WEATHER_ID:
                String id = uri.getLastPathSegment();
                cursor = db.query(DataContract.Weather.TABLE_NAME, projection, DataContract.Weather._ID+"=?", new String[]{id}, null, null, sortOrder);
                cursor.setNotificationUri(getContext().getContentResolver(), uri);
                break;
            case ROUTE_WEATHER:
                cursor = db.query(DataContract.Weather.TABLE_NAME, projection, selection, selectionArgs, null, null, sortOrder);
                cursor.setNotificationUri(getContext().getContentResolver(), uri);
                break;
            default:
                throw new UnsupportedOperationException("unknown uri");
        }
        return cursor;
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        int match = sUriMatcher.match(uri);
        String nullNum = null;
        String tableName = null;
        switch (match){
            case ROUTE_CITIES:
                tableName = DataContract.City.TABLE_NAME;
                break;
            case ROUTE_WEATHER:
                tableName = DataContract.Weather.TABLE_NAME;
                nullNum = String.format("%s,%s,%s,%s",
                        DataContract.Weather._ID,
                        DataContract.Weather.COLUMN_INDEX,
                        DataContract.Weather.COLUMN_WEATHER_DATA,
                        DataContract.Weather.COLUMN_PM25);
                break;
            default:
                throw new IllegalArgumentException("not support");
        }

        SQLiteDatabase db = openHelper.getWritableDatabase();
        db.insert(tableName, nullNum, values);
        getContext().getContentResolver().notifyChange(uri, null, true);
        return uri;
    }

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        int match = sUriMatcher.match(uri);
        Timber.i("delete: %s", uri.toString());
        SQLiteDatabase db = openHelper.getWritableDatabase();
        int affectedNum = 0;
        switch (match){
            case ROUTE_CITY_ID: {
                String id = uri.getLastPathSegment();
                affectedNum = db.delete(DataContract.City.TABLE_NAME, DataContract.City._ID+"=?", new String[]{id});
                break;
            }
            case ROUTE_CITIES:{
                affectedNum = db.delete(DataContract.City.TABLE_NAME, selection, selectionArgs);
                break;
            }
            case ROUTE_WEATHER_ID:
                String id = uri.getLastPathSegment();
                db.delete(DataContract.Weather.TABLE_NAME, DataContract.Weather._ID+"=?", new String[]{id});
                break;
            case ROUTE_WEATHER:
                affectedNum = db.delete(DataContract.Weather.TABLE_NAME, selection, selectionArgs);
                break;
            default:
                affectedNum = 0;
                throw new UnsupportedOperationException("unknown uri");
        }
        getContext().getContentResolver().notifyChange(DataContract.Weather.CONTENT_URI, null, true);
        return affectedNum;
    }

    @Override
    public ContentProviderResult[] applyBatch(ArrayList<ContentProviderOperation> operations) throws OperationApplicationException {
        Timber.i("applyBatch");
        SQLiteDatabase db = openHelper.getWritableDatabase();
        ContentProviderResult[] results = new ContentProviderResult[operations.size()];
        try{
            db.beginTransaction();
            for (int i=0; i<operations.size(); i++){
                ContentProviderOperation operation = operations.get(i);
                results[i] = operation.apply(this, results, i);
            }
            db.setTransactionSuccessful();
        }finally {
            db.endTransaction();
        }
        return results;
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
        Timber.i("update");
        int match = sUriMatcher.match(uri);
        SQLiteDatabase db = openHelper.getWritableDatabase();
        int affectedNum = 0;
        switch (match){
            case ROUTE_CITY_ID: {
                String id = uri.getLastPathSegment();
                affectedNum = db.update(DataContract.City.TABLE_NAME, values, DataContract.City._ID+"=?", new String[]{id});
                break;
            }
            case ROUTE_CITIES:{
                affectedNum = db.update(DataContract.City.TABLE_NAME, values, selection, selectionArgs);
                break;
            }
            case ROUTE_WEATHER_ID:
                String id = uri.getLastPathSegment();
                db.update(DataContract.Weather.TABLE_NAME, values, DataContract.Weather._ID+"=?", new String[]{id});
                break;
            case ROUTE_WEATHER:
                affectedNum = db.update(DataContract.Weather.TABLE_NAME, values, selection, selectionArgs);
                break;
            default:
                affectedNum = 0;
                throw new UnsupportedOperationException("unknown uri");
        }
        return affectedNum;
    }

    public static class WeatherDatabase extends SQLiteOpenHelper {
        public static final String DB_NAME = "weather.db";
        public static final int VERSION = 1;
        public static final String SQL_CREATE_CITY = "CREATE TABLE " + DataContract.City.TABLE_NAME + " (" +
                DataContract.City._ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
                DataContract.City.COLUMN_NAME + " text " +
                ")";
        public static final String SQL_CREATE_DATA = "CREATE TABLE " + DataContract.Weather.TABLE_NAME + " (" +
                DataContract.Weather._ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
                DataContract.Weather.COLUMN_CURRENT_CITY + " text, " +
                DataContract.Weather.COLUMN_PM25 + " text, " +
                DataContract.Weather.COLUMN_WEATHER_DATA + " text, " +
                DataContract.Weather.COLUMN_INDEX + " text " +
                ")";
        public WeatherDatabase(Context ctx){
            super(ctx, DB_NAME, null, VERSION);
        }
        @Override
        public void onCreate(SQLiteDatabase db) {
            Timber.i("onCreate");
            db.beginTransaction();
            db.execSQL(SQL_CREATE_CITY);
            db.execSQL(SQL_CREATE_DATA);
            db.setTransactionSuccessful();
            db.endTransaction();
        }
        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        }
    }
}
