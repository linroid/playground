package com.linroid.airhockey.data

import android.opengl.GLES20
import com.linroid.airhockey.utils.Sizeof
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class VertexArray(arr: FloatArray) {
    private val floatBuffer: FloatBuffer = ByteBuffer.allocateDirect(arr.size * Sizeof.FLOAT)
            .order(ByteOrder.nativeOrder())
            .asFloatBuffer()
            .put(arr)

    fun setVertexAttribPointer(offset: Int, attributeLocation: Int, componentCount: Int, stride: Int) {
        floatBuffer.position(offset)
        GLES20.glVertexAttribPointer(attributeLocation, componentCount, GLES20.GL_FLOAT, false, stride, floatBuffer)
        GLES20.glEnableVertexAttribArray(attributeLocation)
        floatBuffer.position(0)
    }

}