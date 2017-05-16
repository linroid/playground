package com.linroid.airhockey.shape

import com.linroid.airhockey.program.ColorShaderProgram
import com.linroid.airhockey.data.VertexArray
import android.opengl.GLES20.*
import com.linroid.airhockey.utils.Sizeof

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class Mallet : Shape() {

    companion object {
        private val POSITION_COMPONENT_COUNT = 2
        private val COLOR_COMPONENT_COUNT = 3
        private val STRIDE = (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * Sizeof.FLOAT
        private val VERTEX_DATA = floatArrayOf(
                // Order of coordinates: X, Y, R, G, B
                0f, -0.4f, 0f, 0f, 1f,
                0f, 0.4f, 1f, 0f, 0f)
    }

    private val vertexArray: VertexArray

    init {
        vertexArray = VertexArray(VERTEX_DATA)
    }

    fun bindData(colorProgram: ColorShaderProgram) {
        vertexArray.setVertexAttribPointer(
                0,
                colorProgram.aPositionLocation,
                POSITION_COMPONENT_COUNT,
                STRIDE)
        vertexArray.setVertexAttribPointer(
                POSITION_COMPONENT_COUNT,
                colorProgram.aColorLocation,
                COLOR_COMPONENT_COUNT,
                STRIDE)
    }

    override fun draw() {
        glDrawArrays(GL_POINTS, 0, 2)
    }

}