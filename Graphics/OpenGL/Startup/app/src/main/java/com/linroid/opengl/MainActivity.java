package com.linroid.opengl;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ES20GLSurfaceView surfaceView = (ES20GLSurfaceView) findViewById(R.id.surface_view);
    }
}
