package com.linroid.airhockey.program

import com.linroid.airhockey.R
import android.opengl.GLES20.*

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class TextureShaderProgram
    : ShaderProgram(R.raw.texture_vertex_shader, R.raw.texture_fragment_shader) {
    // uniform
    val uMatrixLocation: Int
    val uTextureUnitLocation: Int

    // attribute
    val aPositionLocation: Int
    val aTextureCooridinates: Int

    init {
        uMatrixLocation = glGetUniformLocation(program, "u_Matrix")
        uTextureUnitLocation = glGetUniformLocation(program, "u_TextureUnit")

        aPositionLocation = glGetAttribLocation(program, "a_Position")
        aTextureCooridinates = glGetAttribLocation(program, "a_TextureCoordinates")
    }

    fun setUniforms(matrix: FloatArray, textureId: Int) {
        glUniformMatrix4fv(uMatrixLocation, 1, false, matrix, 0)
        glActiveTexture(GL_TEXTURE0)
        glBindTexture(GL_TEXTURE_2D, textureId)
        glUniform1i(uTextureUnitLocation, 0)
    }

}