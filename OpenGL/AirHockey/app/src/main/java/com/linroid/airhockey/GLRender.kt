package com.linroid.airhockey

import android.opengl.GLES20.*
import android.opengl.GLSurfaceView
import com.linroid.airhockey.utils.GLLoader
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import android.opengl.GLES20.glUniform4f
import android.opengl.Matrix
import com.linroid.airhockey.utils.Sizeof


/**
 * @author linroid <linroid@gmail.com>
 * *
 * @since 11/05/2017
 */
class GLRender(val surfaceView: GLSurfaceView) : GLSurfaceView.Renderer {

    private val POINT_COMPONENT_COUNT = 2
    private val COLOR_COMPONENT_COUNT = 3
    private val STRIDE = (POINT_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * Sizeof.FLOAT

    private var fragShader: Int = 0
    private var vertexShader: Int = 0

    private var aPositionLocation: Int = 0
    private var aColorLocation: Int = 0
    private var uMatrixLocation: Int = 0

    private lateinit var vertexData: FloatBuffer

    private val VERTEX_DATA_ARRAY = floatArrayOf(
            // Triangle
            0f, 0f, 1f, 1f, 1f,
            -0.5f, -0.8f, 0.7f, 0.7f, 0.7f,
            0.5f, -0.8f, 0.7f, 0.7f, 0.7f,
            0.5f, 0.8f, 0.7f, 0.7f, 0.7f,
            -0.5f, 0.8f, 0.7f, 0.7f, 0.7f,
            -0.5f, -0.8f, 0.7f, 0.7f, 0.7f,

            // Line 1
            -0.5f, 0f, 1f, 0f, 0f,
            0.5f, 0f, 1f, 0f, 0f,

            // Mallets
            0f, -0.25f, 0f, 0f, 1f,
            0f, 0.25f, 1f, 0f, 0f)

    private val projectionMatrix = FloatArray(16)

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

        aPositionLocation = glGetAttribLocation(program, "a_Position")
        aColorLocation = glGetAttribLocation(program, "a_Color")
        uMatrixLocation = glGetUniformLocation(program, "u_Matrix")

        vertexData.position(0)
        glVertexAttribPointer(aPositionLocation, POINT_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, vertexData)

        vertexData.position(POINT_COMPONENT_COUNT)
        glVertexAttribPointer(aColorLocation, COLOR_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, vertexData)

        glEnableVertexAttribArray(aPositionLocation)
        glEnableVertexAttribArray(aColorLocation)
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        var aspectRadio: Float

        if (width > height) {
            aspectRadio = width.toFloat() / height.toFloat()
            Matrix.orthoM(projectionMatrix, 0, -aspectRadio, aspectRadio, -1f, 1f, -1f, 1f)
        } else {
            aspectRadio = height.toFloat() / width.toFloat()
            Matrix.orthoM(projectionMatrix, 0, -1f, 1f, -aspectRadio, aspectRadio, -1f, 1f)
        }

        glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        glClear(GL_COLOR_BUFFER_BIT)

        // orthographic projection
        glUniformMatrix4fv(uMatrixLocation, 1, false, projectionMatrix, 0)

        // draw two triangles
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6)

        // draw lines
        glDrawArrays(GL_LINES, 6, 2)

        // draw first mallet
        glDrawArrays(GL_POINTS, 8, 1)

        // draw second mallet
        glDrawArrays(GL_POINTS, 9, 1)
    }

}
