package com.linroid.airhockey.program

import com.linroid.airhockey.R
import android.opengl.GLES20.*

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class ColorShaderProgram
    : ShaderProgram(R.raw.simple_vertex_shader, R.raw.simple_fragment_shader) {

    val uMatrixLocation: Int
    val aPositionLocation: Int
    val uColorLocation: Int

    init {
        uMatrixLocation = glGetUniformLocation(program, "u_Matrix")
        uColorLocation = glGetUniformLocation(program, "u_Color")

        aPositionLocation = glGetAttribLocation(program, "a_Position")
    }

    fun setUniforms(matrix: FloatArray, r: Float, g: Float, b: Float) {
        glUniformMatrix4fv(uMatrixLocation, 1, false, matrix, 0)
        glUniform4f(uColorLocation, r, g, b, 1f)
    }
}