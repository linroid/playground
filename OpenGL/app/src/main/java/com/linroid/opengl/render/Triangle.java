package com.linroid.opengl.render;

import android.opengl.GLES20;

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
    private static final int COORDS_PER_VERTEX = 3;

    private final String vertexShaderCode =
            "uniform mat4 uMVPMatrix;" +
            "attribute vec4 vPosition;" +
                    "void main() {" +
                    " gl_Position = uMVPMatrix * vPosition;" +
                    "}";
    private final String fragmentShaderCode =
            "precision mediump float;" +
                    "uniform vec4 vColor;" +
                    "void main() {" +
                    "gl_FragColor = vColor;" +
                    "}";

    private int MVPMatrixHandle;

    // 三角形的坐标矩阵
    private static final float TRIANGLE_COORDS[] = {
            0.0f, 0.5f, 0.0f, // top
            -0.5f, -0.3f, 0.0f, // bottom left
            0.5f, -0.3f, 0.0f  // bottom right
    };
    // 颜色
    private float color[] = {0.63671875f, 0.76953125f, 0.22265625f, 1.0f};
    private final int program;
    private int positionHandle;
    private int colorHandle;
    private final int vertexCount = TRIANGLE_COORDS.length / COORDS_PER_VERTEX;
    private final int vertexStride = COORDS_PER_VERTEX * Sizeof.INT;

    public Triangle() {
        ByteBuffer bb = ByteBuffer.allocateDirect(TRIANGLE_COORDS.length * Sizeof.FLOAT);
        bb.order(ByteOrder.nativeOrder());
        vertexBuffer = bb.asFloatBuffer();
        vertexBuffer.put(TRIANGLE_COORDS);
        // 设置 buffer 读取第一个坐标
        vertexBuffer.position(0);

        int vertexShader = GLShader.loadShader(GLES20.GL_VERTEX_SHADER, vertexShaderCode);
        int fragmentShader = GLShader.loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderCode);

        program = GLES20.glCreateProgram();
        GLES20.glAttachShader(program, vertexShader);
        GLES20.glAttachShader(program, fragmentShader);
        // create OpenGL ES  program executables
        GLES20.glLinkProgram(program);
    }

    public void draw(float[] mvpMatrix) {
        GLES20.glUseProgram(program);

        positionHandle = GLES20.glGetAttribLocation(program, "vPosition");
        GLES20.glEnableVertexAttribArray(positionHandle);
        GLES20.glVertexAttribPointer(positionHandle, COORDS_PER_VERTEX, GLES20.GL_FLOAT, false, vertexStride, vertexBuffer);

        colorHandle = GLES20.glGetUniformLocation(program, "vColor");
        GLES20.glUniform4fv(colorHandle, 1, color, 0);

        MVPMatrixHandle = GLES20.glGetUniformLocation(program, "uMVPMatrix");
        GLES20.glUniformMatrix4fv(MVPMatrixHandle, 1, false, mvpMatrix, 0);

        // draw triangle
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, vertexCount);

        GLES20.glDisableVertexAttribArray(positionHandle);
    }
}
