package com.linroid.airhockey.utils

/**
 * @author linroid <linroid@gmail.com>
 * @since 18/05/2017
 */
class Geometry {

    class Point(val x: Float,
                val y: Float,
                val z: Float) {

        fun translateY(offset: Float): Point {
            return Point(x, y + offset, z)
        }
    }

    class Circle(val point: Point,
                 val radius: Float) {

        fun scale(scale: Float): Circle {
            return Circle(point, radius * scale)
        }
    }

    class Cylinder(val point: Point,
                   val radius: Float,
                   val height: Float) {
    }
}