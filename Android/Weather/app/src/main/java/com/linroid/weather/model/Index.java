
package com.linroid.weather.model;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;

public class Index implements Parcelable {

    @Expose
    private String title;
    @Expose
    private String zs;
    @Expose
    private String tipt;
    @Expose
    private String des;

    /**
     * 
     * @return
     *     The title
     */
    public String getTitle() {
        return title;
    }

    /**
     * 
     * @param title
     *     The title
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * 
     * @return
     *     The zs
     */
    public String getZs() {
        return zs;
    }

    /**
     * 
     * @param zs
     *     The zs
     */
    public void setZs(String zs) {
        this.zs = zs;
    }

    /**
     * 
     * @return
     *     The tipt
     */
    public String getTipt() {
        return tipt;
    }

    /**
     * 
     * @param tipt
     *     The tipt
     */
    public void setTipt(String tipt) {
        this.tipt = tipt;
    }

    /**
     * 
     * @return
     *     The des
     */
    public String getDes() {
        return des;
    }

    /**
     * 
     * @param des
     *     The des
     */
    public void setDes(String des) {
        this.des = des;
    }

    @Override
    public String toString() {
        return "Index{" +
                "title='" + title + '\'' +
                ", zs='" + zs + '\'' +
                ", tipt='" + tipt + '\'' +
                ", des='" + des + '\'' +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(this.title);
        dest.writeString(this.zs);
        dest.writeString(this.tipt);
        dest.writeString(this.des);
    }

    public Index() {
    }

    private Index(Parcel in) {
        this.title = in.readString();
        this.zs = in.readString();
        this.tipt = in.readString();
        this.des = in.readString();
    }

    public static final Parcelable.Creator<Index> CREATOR = new Parcelable.Creator<Index>() {
        public Index createFromParcel(Parcel source) {
            return new Index(source);
        }

        public Index[] newArray(int size) {
            return new Index[size];
        }
    };
}
