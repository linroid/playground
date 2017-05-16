package com.linroid.airhockey.program

import android.opengl.GLES20
import android.support.annotation.RawRes
import com.linroid.airhockey.utils.GLLoader
import android.opengl.GLES20.*

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
abstract class ShaderProgram(@RawRes vertexResId: Int, @RawRes fragResId: Int) {

    val program: Int

    init {
        val vertexShaderId = GLLoader.shader(vertexResId, GL_VERTEX_SHADER)
        val fragShaderId = GLLoader.shader(fragResId, GL_FRAGMENT_SHADER)
        program = GLLoader.link(vertexShaderId, fragShaderId)
    }

    fun useProgram() {
        GLES20.glUseProgram(program)
    }
}