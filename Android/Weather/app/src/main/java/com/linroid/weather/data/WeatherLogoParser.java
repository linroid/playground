package com.linroid.weather.data;

import com.linroid.weather.R;

/**
 * Created by linroid on 1/26/15.
 */
public class WeatherLogoParser {
    public static int getLogoResId(String weather){
        int resId;
        switch (weather){
            case "阴":
                resId = R.drawable.day02_l;
                break;
            case "阴转小雨":
                resId = R.drawable.day08_l;
                break;
            case "小雨":
                resId = R.drawable.day09_l;
                break;
            case "霾转阴":
                resId = R.drawable.day17_l;
                break;
            default:
                resId = R.drawable.day01_l;
        }
        return resId;
    }
    public static int getMiniLogResId(String weather){
        int resId;
        switch (weather){
            case "阴":
                resId = R.drawable.day02;
                break;
            case "阴转小雨":
                resId = R.drawable.day08;
                break;
            case "小雨":
                resId = R.drawable.day09;
                break;
            case "霾转阴":
                resId = R.drawable.day17;
                break;
            default:
                resId = R.drawable.day01;
        }
        return resId;
    }
}
