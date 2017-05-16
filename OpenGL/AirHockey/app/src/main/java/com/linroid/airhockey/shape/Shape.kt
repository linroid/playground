package com.linroid.airhockey.shape

import android.opengl.GLES20.*
import com.linroid.airhockey.data.VertexArray
import com.linroid.airhockey.program.ShaderProgram

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
abstract class Shape {

    abstract fun draw()
}