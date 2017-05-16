package com.linroid.airhockey.shape

import android.opengl.GLES20.*
import com.linroid.airhockey.data.VertexArray
import com.linroid.airhockey.utils.Sizeof
import com.linroid.airhockey.program.TextureShaderProgram


/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class Table : Shape() {
    private val TEXTURE_COORDINATES_COMPONENT_COUNT = 2
    private val POSITION_COMPONENT_COUNT = 2
    private val STRIDE = (POSITION_COMPONENT_COUNT + TEXTURE_COORDINATES_COMPONENT_COUNT) * Sizeof.FLOAT

    val vertexArray: VertexArray

    private val VERTEX_DATA_ARRAY = floatArrayOf(
            // Order of coordinates: X, Y, S, T

            // Triangle Fan
            0f, 0f, 0.5f, 0.5f,
            -0.5f, -0.8f, 0f, 0.9f,
            0.5f, -0.8f, 1f, 0.9f,
            0.5f, 0.8f, 1f, 0.1f,
            -0.5f, 0.8f, 0f, 0.1f,
            -0.5f, -0.8f, 0f, 0.9f)

    init {
        vertexArray = VertexArray(VERTEX_DATA_ARRAY)
    }

    fun bindData(textureProgram: TextureShaderProgram) {
        vertexArray.setVertexAttribPointer(
                0,
                textureProgram.aPositionLocation,
                POSITION_COMPONENT_COUNT,
                STRIDE)
        vertexArray.setVertexAttribPointer(
                POSITION_COMPONENT_COUNT,
                textureProgram.aTextureCooridinates,
                TEXTURE_COORDINATES_COMPONENT_COUNT,
                STRIDE)
    }

    override fun draw() {
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6)
    }

}