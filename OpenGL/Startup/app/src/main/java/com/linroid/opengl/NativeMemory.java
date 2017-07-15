package com.linroid.opengl;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * @author linroid <linroid@gmail.com>
 * @since 18/04/2017
 */
public class NativeMemory {
    private void test() {
        float[] rectangle = {
                -0.5f, -0.5f,
                0.5f, 0.5f,
                -0.5f, 0.5f,

                -0.5f, 0.5f,
                0.5f, -0.5f,
                0.5f, 0.5f
        };
        final int BYTES_PER_FLOAT = 4;
        FloatBuffer vertexData = ByteBuffer.allocateDirect(rectangle.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer();
        vertexData.put(rectangle);
    }
}
