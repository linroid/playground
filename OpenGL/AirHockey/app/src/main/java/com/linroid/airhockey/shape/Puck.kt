package com.linroid.airhockey.shape

import com.linroid.airhockey.data.VertexArray
import com.linroid.airhockey.program.ColorShaderProgram
import com.linroid.airhockey.utils.Geometry

/**
 * @author linroid <linroid@gmail.com>
 * @since 19/05/2017
 */
class Puck(radius: Float,
           val height: Float,
           numPoints: Int) : Shape() {
    private val POSITION_COMPONENT_COUNT = 3
    private val puckData: Geometry.GeneratedData
    private val vertexArray: VertexArray

    init {
        puckData = ObjectBuilder.createPuck(Geometry.Cylinder(Geometry.Point(0f, 0f, 0f), radius, height), numPoints)
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