package com.linroid.opengl.render;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import hugo.weaving.DebugLog;
import timber.log.Timber;

/**
 * @author linroid <linroid@gmail.com>
 * @since 19/04/2017
 */
public class GLRenderer implements GLSurfaceView.Renderer {
    private Square square;
    private Triangle triangle;

    private final float[] MVPMatrix = new float[16]; // Model View Projection Matrix
    private final float[] projectionMatrix = new float[16];
    private final float[] viewMatrix = new float[16];
    private final float[] rotateMatrix = new float[16];
    private float angle;

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
        GLES20.glViewport(0, 0, width, height);
        float ratio = (float) width / height;
        Matrix.frustumM(projectionMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
    }

    @DebugLog
    @Override
    public void onDrawFrame(GL10 gl) {
        float[] scratch = new float[16];

        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);

        // Define a Camera View
        Matrix.setLookAtM(viewMatrix, 0, 0, 0, -3, 0f, 0f, 0f, 0f, 1.f, 0f);
        Matrix.multiplyMM(MVPMatrix, 0, projectionMatrix, 0, viewMatrix, 0);

        Matrix.setRotateM(rotateMatrix, 0, angle, 0, 0, -1.f);
        Matrix.multiplyMM(scratch, 0, MVPMatrix, 0, rotateMatrix, 0);

        triangle.draw(scratch);
    }

    public float getAngle() {
        return angle;
    }

    public void setAngle(float angle) {
        this.angle = angle;
    }
}
