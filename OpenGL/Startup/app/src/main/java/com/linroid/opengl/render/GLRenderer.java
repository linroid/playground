package com.linroid.opengl.render;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import hugo.weaving.DebugLog;

/**
 * @author linroid <linroid@gmail.com>
 * @since 19/04/2017
 */
public class GLRenderer implements GLSurfaceView.Renderer {
    private Square square;
    private Triangle triangle;

    @DebugLog
    public GLRenderer() {
    }

    @DebugLog
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.f, 0.f, 0.f, 1.f);
        square = new Square();
        triangle = new Triangle();
    }

    @DebugLog

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
    }

    @DebugLog
    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
        triangle.draw();
    }
}
