package com.linroid.airhockey

import android.app.Activity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : Activity() {

    private lateinit var render: GLRender

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        render = GLRender(surfaceView)
        surfaceView.setRenderer(render)
    }

    override fun onResume() {
        super.onResume()
        surfaceView.onResume()
    }

    override fun onPause() {
        super.onPause()
        surfaceView.onPause()
    }
}
