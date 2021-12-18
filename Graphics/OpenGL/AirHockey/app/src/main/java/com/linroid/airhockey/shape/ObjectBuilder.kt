package com.linroid.airhockey.shape

import android.opengl.GLES20.*
import com.linroid.airhockey.utils.Geometry
import com.linroid.airhockey.utils.Sizeof
import com.linroid.airhockey.utils.Geometry.DrawCommand
import timber.log.Timber


/**
 * @author linroid <linroid@gmail.com>
 * @since 18/05/2017
 */
class ObjectBuilder(sizeInVertices: Int) {
    val FLOATS_PER_VERTEX = 3
    val vertexData: FloatArray
    var offset = 0
    val drawList = ArrayList<Geometry.DrawCommand>()

    init {
        vertexData = FloatArray(sizeInVertices * FLOATS_PER_VERTEX)
    }

    companion object {
        fun sizeOfCycleInVertices(numPoints: Int): Int {
            return 1 + (numPoints + 1)
        }

        fun sizeOfOpenCylinderInVertices(numPoints: Int): Int {
            return (numPoints + 1) * 2
        }

        /**
         * build a puck with a cylinder
         */
        fun createPuck(cylinder: Geometry.Cylinder, numPoints: Int): Geometry.GeneratedData {
            val size = sizeOfCycleInVertices(numPoints) + sizeOfOpenCylinderInVertices(numPoints)
            val builder = ObjectBuilder(size)
            val puckTop = Geometry.Circle(cylinder.center.translateY(cylinder.height / 2f), cylinder.radius)
            builder.appendCircle(puckTop, numPoints)
            builder.appendOpenCylinder(cylinder, numPoints)
            return builder.build()
        }

        fun createMallet(center: Geometry.Point, radius: Float, height: Float, numPoints: Int): Geometry.GeneratedData {
            val size = (sizeOfCycleInVertices(numPoints) + sizeOfOpenCylinderInVertices(numPoints)) * 2
            val builder = ObjectBuilder(size)

            // base
            val baseHeight = 0.25f * height
            val baseCircle = Geometry.Circle(center.translateY(-baseHeight), radius)
            val baseCylinder = Geometry.Cylinder(baseCircle.center.translateY(-baseHeight / 2f), radius, baseHeight)
            builder.appendCircle(baseCircle, numPoints)
            builder.appendOpenCylinder(baseCylinder, numPoints)

            // handle
            val handleHeight = 0.75f * height
            val handleRadius = radius / 3f

            val handleCircle = Geometry.Circle(center.translateY(height * 0.5f), handleRadius)
            val handleCylinder = Geometry.Cylinder(handleCircle.center.translateY(-handleHeight / 2f), handleRadius, handleHeight)
            builder.appendCircle(handleCircle, numPoints)
            builder.appendOpenCylinder(handleCylinder, numPoints)

            return builder.build()
        }
    }

    private fun appendOpenCylinder(cylinder: Geometry.Cylinder, numPoints: Int) {
        val startVertex = offset / FLOATS_PER_VERTEX
        val numVertices = sizeOfOpenCylinderInVertices(numPoints)

        val yTop = cylinder.center.y + cylinder.height / 2f
        val yBottom = cylinder.center.y - cylinder.height / 2f

        val perAngleInRadians = 2 * Math.PI / numPoints
        for (i in 0..numPoints) {
            val angleRadians = perAngleInRadians * i
            val x = (cylinder.center.x + cylinder.radius * Math.cos(angleRadians)).toFloat()
            val z = (cylinder.center.z + cylinder.radius * Math.sin(angleRadians)).toFloat()
            vertexData[offset++] = x
            vertexData[offset++] = yBottom
            vertexData[offset++] = z

            vertexData[offset++] = x
            vertexData[offset++] = yTop
            vertexData[offset++] = z
        }
        drawList.add(object : DrawCommand {
            override fun draw() {
                glDrawArrays(GL_TRIANGLE_STRIP, startVertex, numVertices)
                Timber.d("GL_TRIANGLE_STRIP %d %d", startVertex, numVertices)
            }

        })
    }

    private fun appendCircle(circle: Geometry.Circle, numPoints: Int) {
        val startVertex = offset / FLOATS_PER_VERTEX
        val numVertices = sizeOfCycleInVertices(numPoints)
        // center point
        vertexData[offset++] = circle.center.x
        vertexData[offset++] = circle.center.y
        vertexData[offset++] = circle.center.z

        val perAngleInRadians = 2 * Math.PI / numPoints
        for (i in 0..numPoints) {
            val angleInRadians = perAngleInRadians * i

            vertexData[offset++] = (circle.center.x + circle.radius * Math.cos(angleInRadians)).toFloat()
            vertexData[offset++] = circle.center.y
            vertexData[offset++] = (circle.center.z + circle.radius * Math.sin(angleInRadians)).toFloat()

        }
        drawList.add(object : DrawCommand {
            override fun draw() {
                glDrawArrays(GL_TRIANGLE_FAN, startVertex, numVertices)
                Timber.d("GL_TRIANGLE_FAN %d %d", startVertex, numVertices)
            }
        })
    }

    private fun build(): Geometry.GeneratedData {
        return Geometry.GeneratedData(vertexData, drawList)
    }
}