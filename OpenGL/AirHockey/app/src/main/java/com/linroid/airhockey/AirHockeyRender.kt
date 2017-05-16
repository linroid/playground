package com.linroid.airhockey

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import android.opengl.GLES20.*
import android.opengl.Matrix
import com.linroid.airhockey.program.ColorShaderProgram
import com.linroid.airhockey.program.TextureShaderProgram
import com.linroid.airhockey.shape.Mallet
import com.linroid.airhockey.shape.Table
import com.linroid.airhockey.utils.GLLoader

/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class AirHockeyRender : GLSurfaceView.Renderer {
    private val projectionMatrix = FloatArray(16)
    private val modelMatrix = FloatArray(16)
    private lateinit var table: Table
    private lateinit var mallet: Mallet
    private var textureId: Int = 0
    private lateinit var textureShaderProgram: TextureShaderProgram
    private lateinit var colorShaderProgram: ColorShaderProgram


    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        glClearColor(0f, 0f, 0f, 0f)
        table = Table()
        mallet = Mallet()
        textureId = GLLoader.texture(R.drawable.air_hockey_surface)
        textureShaderProgram = TextureShaderProgram()
        colorShaderProgram = ColorShaderProgram()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        glViewport(0, 0, width, height)

        Matrix.setIdentityM(modelMatrix, 0)
        Matrix.translateM(modelMatrix, 0, 0f, 0f, -2.5f)
        Matrix.rotateM(modelMatrix, 0, -60f, 1f, 0f, 0f)

        Matrix.perspectiveM(projectionMatrix, 0, 45f, width.toFloat() / height.toFloat(), 1f, 10f)

        val temp = FloatArray(16)
        Matrix.multiplyMM(temp, 0, projectionMatrix, 0, modelMatrix, 0)
        System.arraycopy(temp, 0, projectionMatrix, 0, temp.size)

    }

    override fun onDrawFrame(gl: GL10) {
        glClear(GL_COLOR_BUFFER_BIT)

        textureShaderProgram.useProgram()
        textureShaderProgram.setUniforms(projectionMatrix, textureId)
        table.bindData(textureShaderProgram)
        table.draw()

        colorShaderProgram.useProgram()
        colorShaderProgram.setUniforms(projectionMatrix)
        mallet.bindData(colorShaderProgram)
        mallet.draw()
    }
}