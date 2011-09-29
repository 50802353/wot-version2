package titan.hellocubendk;

import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig; 
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements GLSurfaceView.Renderer
{
	//Context mContext;
	//Square square=new Square();
	public Cube cube = new Cube();
	public float m_width;
	public float m_height;
    public void onDrawFrame(GL10 gl) {
        GL2JNILib.onPaint();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GL2JNILib.init(width, height);
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Do nothing.
    }
}