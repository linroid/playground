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
    val aColorLocation: Int

    init {
        uMatrixLocation = glGetUniformLocation(program, "u_Matrix")
        aPositionLocation = glGetAttribLocation(program, "a_Position")
        aColorLocation = glGetAttribLocation(program, "a_Color")
    }

    fun setUniforms(matrix: FloatArray) {
        glUniformMatrix4fv(uMatrixLocation, 1, false, matrix, 0)
    }
}