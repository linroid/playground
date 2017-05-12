package com.linroid.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.linroid.opengl.render.GLRenderer;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class ES20GLSurfaceView extends GLSurfaceView {

    public ES20GLSurfaceView(Context context) {
        super(context);
        init(context);
    }

    public ES20GLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    private void init(Context context) {
        GLRenderer renderer = new GLRenderer();
        setEGLContextClientVersion(2);
        setRenderer(renderer);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }
}
