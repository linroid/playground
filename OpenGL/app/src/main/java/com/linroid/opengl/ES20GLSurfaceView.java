package com.linroid.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;

import com.linroid.opengl.render.GLRenderer;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class ES20GLSurfaceView extends GLSurfaceView {
    private static final float TOUCH_FACTOR = 180.f / 320;
    private float previousX;
    private float previousY;
    private GLRenderer renderer;

    public ES20GLSurfaceView(Context context) {
        super(context);
        init(context);
    }

    public ES20GLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    private void init(Context context) {
        renderer = new GLRenderer();
        setEGLContextClientVersion(2);
        setRenderer(renderer);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();
        switch (event.getActionMasked()) {
            case MotionEvent.ACTION_MOVE:
                float dx = x - previousX;
                float dy = y - previousY;
                if (y > getHeight()/2) {
                    dx = dx * -1;
                }
                if (x < getWidth() / 2) {
                    dy = dy * -1;
                }
                renderer.setAngle(renderer.getAngle() + (dx + dy) * TOUCH_FACTOR);
                requestRender();
                break;
        }
        previousX = x;
        previousY = y;
        return true;
    }
}
