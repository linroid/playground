package com.linroid.fuckxtu;

import android.graphics.Color;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.squareup.okhttp.FormEncodingBuilder;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.RequestBody;
import com.squareup.okhttp.Response;

import java.io.IOException;


public class MainActivity extends ActionBarActivity {
    Button btn;
    TextView status;
    AuthorizationTask task;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btn = (Button) findViewById(R.id.btn);
        status = (TextView) findViewById(R.id.status);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(task!=null && !task.isCancelled()){
                    btn.setText("已停止");
                    task.cancel(true);
                    return;
                }
                btn.setText("认证中...");
                task = new AuthorizationTask();
                task.execute();
            }
        });
    }
    class AuthorizationTask extends AsyncTask<Void, String, String>{

        String password;
        String url;
        OkHttpClient client;
        @Override
        protected void onPreExecute() {
            this.password = "xtu2013";
            this.url = "http://192.168.252.246/";
            this.client = new OkHttpClient();
        }

        @Override
        protected String doInBackground(Void... params) {
            String account;
            for(;;) {
                for (int i=1; i<=12; i++) {
                    account = "ies" + (i < 10 ? "0" + i : i);
                    publishProgress(account);
                    RequestBody body = new FormEncodingBuilder()
                            .add("DDDDD", account)
                            .add("upass", password)
                            .add("0MKKey", "%B5%C7%C2%BC+Login")
                            .build();
                    Request request = new Request.Builder()
                            .url(url)
                            .post(body).build();
                    try {
                        Response response = client.newCall(request).execute();
                        String data = response.body().string();
                        System.out.println(data);
                        if (!TextUtils.isEmpty(data) && !data.contains("Msg=01")) {
                            return account;
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                        return null;
                    }
                }
            }
        }

        @Override
        protected void onPostExecute(String account) {
            task = null;
            if(TextUtils.isEmpty(account)){
                btn.setText("出错了:(");
            }else{
                btn.setText("认证成功:)");
            }
        }

        @Override
        protected void onProgressUpdate(String... values) {
            status.setText(values[0]);
        }
    }

}
