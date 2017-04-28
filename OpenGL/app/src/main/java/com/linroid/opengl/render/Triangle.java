package com.linroid.opengl.render;

import android.opengl.GLES20;

import com.linroid.opengl.GLUtils;
import com.linroid.opengl.R;
import com.linroid.opengl.Sizeof;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class Triangle {
    private FloatBuffer vertexBuffer;

    private int MVPMatrixHandle;

    // 三角形的坐标矩阵
    private static final float TRIANGLE_COORDS[] = {
            0.0f, 0.0f, 0.5f, 1.f, 1.f, 1.f, 1.f,
            -0.5f, -0.3f, 0.5f, 1.f, 0.f, 0.f, 1.f,
            0.5f, -0.3f, 0.5f, 0.f, 1.f, 0.f, 1.f,
            0.f, 0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f,
            -0.5f, -0.3f, 0.5f, 1.f, 0.f, 0.f, 1.f,
    };
    // 颜色
    private float color[] = {0.63671875f, 0.76953125f, 0.22265625f, 1.0f};
    private final int program;
    private int positionHandle;
    private int colorHandle;

    private final int COLOR_COMPONENT_COUNT = 4;
    private final int POSITION_COMPONENT_COUNT = 3;
    private final int COMPONENT_COUNT = COLOR_COMPONENT_COUNT + POSITION_COMPONENT_COUNT;
    private final int VERTEX_COUNT = TRIANGLE_COORDS.length / COMPONENT_COUNT;
    private final int VERTEX_STRIDE = Sizeof.FLOAT(COMPONENT_COUNT);

    public Triangle() {
        ByteBuffer bb = ByteBuffer.allocateDirect(TRIANGLE_COORDS.length * Sizeof.FLOAT);
        bb.order(ByteOrder.nativeOrder());
        vertexBuffer = bb.asFloatBuffer();
        vertexBuffer.put(TRIANGLE_COORDS);

        int vertexShader = GLUtils.loadShader(GLES20.GL_VERTEX_SHADER, R.raw.triangle_vert);
        int fragmentShader = GLUtils.loadShader(GLES20.GL_FRAGMENT_SHADER, R.raw.triangle_frag);

        program = GLUtils.linkProgram(vertexShader, fragmentShader);
        GLUtils.validateProgram(program);

        GLES20.glUseProgram(program);

        positionHandle = GLES20.glGetAttribLocation(program, "aPosition");
        colorHandle = GLES20.glGetAttribLocation(program, "aColor");
        MVPMatrixHandle = GLES20.glGetUniformLocation(program, "uMVPMatrix");

        vertexBuffer.position(0);
        GLES20.glVertexAttribPointer(positionHandle, POSITION_COMPONENT_COUNT, GLES20.GL_FLOAT, false, VERTEX_STRIDE, vertexBuffer);
        GLES20.glEnableVertexAttribArray(positionHandle);


        vertexBuffer.position(POSITION_COMPONENT_COUNT);
        GLES20.glVertexAttribPointer(colorHandle, COLOR_COMPONENT_COUNT, GLES20.GL_FLOAT, false, VERTEX_STRIDE, vertexBuffer);
        GLES20.glEnableVertexAttribArray(colorHandle);
    }

    public void draw(float[] mvpMatrix) {


        GLES20.glUniformMatrix4fv(MVPMatrixHandle, 1, false, mvpMatrix, 0);

        // draw triangle
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_FAN, 0, VERTEX_COUNT);

//        GLES20.glDisableVertexAttribArray(positionHandle);
    }
}
