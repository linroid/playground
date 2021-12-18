package com.linroid.airhockey

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import android.opengl.GLES20.*
import android.opengl.Matrix
import com.linroid.airhockey.program.ColorShaderProgram
import com.linroid.airhockey.program.TextureShaderProgram
import com.linroid.airhockey.shape.Mallet
import com.linroid.airhockey.shape.Puck
import com.linroid.airhockey.shape.Table
import com.linroid.airhockey.utils.GLLoader


/**
 * @author linroid <linroid@gmail.com>
 * @since 16/05/2017
 */
class AirHockeyRender : GLSurfaceView.Renderer {
    private val viewMatrix = FloatArray(16)
    private val viewProjectionMatrix = FloatArray(16)
    private val modelViewProjectionMatrix = FloatArray(16)

    private val projectionMatrix = FloatArray(16)
    private val modelMatrix = FloatArray(16)

    private lateinit var table: Table
    private lateinit var puck: Puck
    private lateinit var mallet: Mallet
    private var textureId: Int = 0
    private lateinit var textureShaderProgram: TextureShaderProgram
    private lateinit var colorShaderProgram: ColorShaderProgram


    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        glClearColor(0f, 0f, 0f, 0f)
        table = Table()
        mallet = Mallet(0.08f, 0.15f, 32)
        puck = Puck(0.06f, 0.02f, 32)

        textureId = GLLoader.texture(R.drawable.air_hockey_surface)
        textureShaderProgram = TextureShaderProgram()
        colorShaderProgram = ColorShaderProgram()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        glViewport(0, 0, width, height)

        Matrix.perspectiveM(projectionMatrix, 0, 45f, width.toFloat() / height.toFloat(), 1f, 10f)
        Matrix.setLookAtM(viewMatrix, 0, 0f, 1.2f, 2.2f, 0f, 0f, 0f, 0f, 1f, 0f)
    }

    override fun onDrawFrame(gl: GL10) {
        glClear(GL_COLOR_BUFFER_BIT)

        Matrix.multiplyMM(viewProjectionMatrix, 0, projectionMatrix, 0, viewMatrix, 0)

        // draw table
        positionTableInScene()
        textureShaderProgram.useProgram()
        textureShaderProgram.setUniforms(modelViewProjectionMatrix, textureId)
        table.bindData(textureShaderProgram)
        table.draw()

        // draw mallets
        positionObjectInScene(0f, mallet.height / 2f, -0.4f)
        colorShaderProgram.useProgram()
        colorShaderProgram.setUniforms(modelViewProjectionMatrix, 1f, 0f, 0f)
        mallet.bindData(colorShaderProgram)
        mallet.draw()

        positionObjectInScene(0f, mallet.height / 2f, 0.4f)
        colorShaderProgram.setUniforms(modelViewProjectionMatrix, 0f, 0f, 1f)
        mallet.draw()

        // draw puck
        positionObjectInScene(0f, puck.height / 2f, 0f)
        colorShaderProgram.setUniforms(viewProjectionMatrix, 0.8f, 0.8f, 1f)
        puck.bindData(colorShaderProgram)
        puck.draw()
    }

    private fun positionTableInScene() {
        Matrix.setIdentityM(modelMatrix, 0)
        Matrix.setRotateM(modelMatrix, 0, 90f, 1f, 0f, 0f)
        Matrix.multiplyMM(modelViewProjectionMatrix, 0, viewProjectionMatrix, 0, modelMatrix, 0)
    }

    private fun positionObjectInScene(x: Float, y: Float, z: Float) {
        Matrix.setIdentityM(modelMatrix, 0)
        Matrix.translateM(modelMatrix, 0, x, y, z)
        Matrix.multiplyMM(modelViewProjectionMatrix, 0, viewProjectionMatrix, 0, modelMatrix, 0)
    }
}