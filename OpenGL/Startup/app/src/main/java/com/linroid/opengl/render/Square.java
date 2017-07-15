package com.linroid.opengl.render;

import com.linroid.opengl.Sizeof;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

/**
 * @author linroid <linroid@gmail.com>
 * @since 23/04/2017
 */
public class Square {
    private FloatBuffer vertexBuffer;
    private ShortBuffer drawListBuffer;
    private static final int COORDS_PER_VERTEX = 3;
    private static float SQUARE_COORDS[] = {
            -0.5f, 0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            -0.5f, -0.5f, 0.f,
    };
    private short drawOrder[] = {0, 1, 2, 0, 2, 3}; // 设置定点顺序

    public Square() {
        ByteBuffer bb = ByteBuffer.allocateDirect(SQUARE_COORDS.length * Sizeof.FLOAT);
        bb.order(ByteOrder.nativeOrder());
        vertexBuffer = bb.asFloatBuffer();
        vertexBuffer.put(SQUARE_COORDS);
        vertexBuffer.position(0);

        ByteBuffer dlb = ByteBuffer.allocateDirect(drawOrder.length * Sizeof.SHORT);
        dlb.order(ByteOrder.nativeOrder());
        drawListBuffer = dlb.asShortBuffer();
        drawListBuffer.put(drawOrder);
        drawListBuffer.position(0);
    }
}
