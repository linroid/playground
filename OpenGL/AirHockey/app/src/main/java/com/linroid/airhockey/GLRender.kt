package com.linroid.airhockey

import android.opengl.GLES20.*
import android.opengl.GLUtils.*
import android.opengl.Matrix.*
import android.opengl.GLSurfaceView
import com.linroid.airhockey.utils.GLLoader
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import android.opengl.GLES20.glUniform4f




/**
 * @author linroid <linroid@gmail.com>
 * *
 * @since 11/05/2017
 */
class GLRender(val surfaceView: GLSurfaceView) : GLSurfaceView.Renderer {
    private var fragShader: Int = 0
    private var vertexShader: Int = 0
    private var colorLocation: Int = 0
    private var positionLocation: Int = 0
    private lateinit var vertexData: FloatBuffer
    private val VERTEX_DATA_ARRAY = floatArrayOf(
            // Triangle 1
            -0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f,

            // Triangle 2
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,

            // Line 1
            -0.5f, 0f,
            0.5f, 0f,

            // Mallets
            0f, -0.25f,
            0f, 0.25f)

    init {
        surfaceView.setEGLContextClientVersion(2)
    }

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        glClearColor(0F, 0F, 0F, 0F)

        vertexData = GLLoader.vertex(VERTEX_DATA_ARRAY)

        vertexShader = GLLoader.shader(R.raw.simple_vertex_shader, GL_VERTEX_SHADER)
        fragShader = GLLoader.shader(R.raw.simple_fragment_shader, GL_FRAGMENT_SHADER)
        val program = GLLoader.link(vertexShader, fragShader)
        glUseProgram(program)

        colorLocation = glGetUniformLocation(program, "u_Color")
        positionLocation = glGetAttribLocation(program, "a_Position")

        vertexData.position(0)
        glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, vertexData)

        glEnableVertexAttribArray(positionLocation)
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        glClear(GL_COLOR_BUFFER_BIT)

        // draw two triangles
        glUniform4f(colorLocation, 1F, 1F, 1F, 1F)
        glDrawArrays(GL_TRIANGLES, 0, 6)

        // draw lines
        glUniform4f(colorLocation, 1F, 0F, 0F, 1F)
        glDrawArrays(GL_LINES, 6, 2)

        // draw first mallet
        glUniform4f(colorLocation, 0F, 0F, 1F, 1F)
        glDrawArrays(GL_POINTS, 8, 1)

        // draw second mallet
        glUniform4f(colorLocation, 1F, 0F, 0F, 1F)
        glDrawArrays(GL_POINTS, 9, 1)
    }

}
