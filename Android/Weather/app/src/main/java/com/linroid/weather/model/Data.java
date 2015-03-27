
package com.linroid.weather.model;

import com.google.gson.annotations.Expose;

import java.util.ArrayList;
import java.util.List;

public class Data {

    @Expose
    private Integer error;
    @Expose
    private String status;
    @Expose
    private String date;
    @Expose
    private List<Result> results = new ArrayList<Result>();

    @Expose
    private String message;

    /**
     * 
     * @return
     *     The error
     */
    public Integer getError() {
        return error;
    }

    /**
     * 
     * @param error
     *     The error
     */
    public void setError(Integer error) {
        this.error = error;
    }

    /**
     * 
     * @return
     *     The status
     */
    public String getStatus() {
        return status;
    }

    /**
     * 
     * @param status
     *     The status
     */
    public void setStatus(String status) {
        this.status = status;
    }

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
     *     The results
     */
    public List<Result> getResults() {
        return results;
    }

    /**
     * 
     * @param results
     *     The results
     */
    public void setResults(List<Result> results) {
        this.results = results;
    }

    public String getMessage() {
        return message;
    }

    @Override
    public String toString() {
        return "Data{" +
                "error=" + error +
                ", status='" + status + '\'' +
                ", date='" + date + '\'' +
                ", results=" + results +
                ", message='" + message + '\'' +
                '}';
    }
}
