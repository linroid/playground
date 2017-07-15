package com.linroid.airhockey.shape

import com.linroid.airhockey.program.ColorShaderProgram
import com.linroid.airhockey.data.VertexArray
import android.opengl.GLES20.*
import com.linroid.airhockey.utils.Geometry
import com.linroid.airhockey.utils.Sizeof

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class Mallet(val radius: Float,
             val height: Float,
             val numPoints: Int) : Shape() {

    private val POSITION_COMPONENT_COUNT = 3
    private val puckData: Geometry.GeneratedData
    private val vertexArray: VertexArray

    init {
        puckData = ObjectBuilder.createMallet(Geometry.Point(0f, 0f, 0f), radius, height, numPoints)
        vertexArray = VertexArray(puckData.vertexData)
    }

    fun bindData(colorShaderProgram: ColorShaderProgram) {
        vertexArray.setVertexAttribPointer(0, colorShaderProgram.aPositionLocation, POSITION_COMPONENT_COUNT, 0)
    }

    override fun draw() {
        for (command in puckData.drawList) {
            command.draw()
        }
    }
}