package com.linroid.airhockey.utils

/**
 * @author linroid <linroid@gmail.com>
 * @since 18/05/2017
 */
class Geometry {

    data class Point(val x: Float,
                     val y: Float,
                     val z: Float) {

        fun translateY(offset: Float): Point {
            return Point(x, y + offset, z)
        }
    }

    // 圆
    data class Circle(val center: Point,
                      val radius: Float) {

        fun scale(scale: Float): Circle {
            return Circle(center, radius * scale)
        }
    }

    // 圆柱
    data class Cylinder(val center: Point,
                        val radius: Float,
                        val height: Float)

    interface DrawCommand {
        fun draw()
    }

    data class GeneratedData(val vertexData: FloatArray, val drawList: List<DrawCommand>)

}