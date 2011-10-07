package titan.hellocubendk;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.opengles.GL10;

public class Cube {
	// Our vertices.
	public float move[] = {0.0f, 0.0f, 0.0f};
	public float touchmove[] = {0.0f, 0.0f, 0.0f};
	private float vertices[] = {
		      -1.0f,  1.0f,  1.0f,  // 0, Top Left
		      -1.0f, -1.0f,  1.0f,  // 1, Bottom Left
		       1.0f, -1.0f,  1.0f,  // 2, Bottom Right
		       1.0f,  1.0f,  1.0f,  // 3, Top Right
		       
		      -1.0f,  1.0f, -1.0f,  // 0, Top Left
			  -1.0f, -1.0f, -1.0f,  // 1, Bottom Left
			   1.0f, -1.0f, -1.0f,  // 2, Bottom Right
			   1.0f,  1.0f, -1.0f,  // 3, Top Right 
		};

	// The order we like to connect them.
	private short[] indices = { 0, 1, 2, 0, 2, 3,
								3, 2, 6, 3, 6, 7,
								7, 6, 5, 7, 5, 4,
								4, 5, 1, 4, 1, 0,
								4, 0, 3, 4, 3, 7,
								2, 1, 5, 2, 5, 6
								};

	// Our vertex buffer.
	private FloatBuffer vertexBuffer;

	// Our index buffer.
	private ShortBuffer indexBuffer;

	public Cube() {
		// a float is 4 bytes, therefore we multiply the number if
		// vertices with 4.
		ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
		vbb.order(ByteOrder.nativeOrder());
		vertexBuffer = vbb.asFloatBuffer();
		vertexBuffer.put(vertices);
		vertexBuffer.position(0);

		// short is 2 bytes, therefore we multiply the number if
		// vertices with 2.
		ByteBuffer ibb = ByteBuffer.allocateDirect(indices.length * 2);
		ibb.order(ByteOrder.nativeOrder());
		indexBuffer = ibb.asShortBuffer();
		indexBuffer.put(indices);
		indexBuffer.position(0);
	}

	/**
	 * This function draws our square on screen.
	 * @param gl
	 */
	public void draw(GL10 gl) {
		gl.glLoadIdentity();
		gl.glTranslatef(touchmove[0], touchmove[1], touchmove[2]);
		gl.glTranslatef(move[0], move[1], move[2]);
		gl.glTranslatef(0, 0, -4);
		// Counter-clockwise winding.
		gl.glFrontFace(GL10.GL_CCW); // OpenGL docs
		// Enable face culling.
		gl.glEnable(GL10.GL_CULL_FACE); // OpenGL docs
		// What faces to remove with the face culling.
		gl.glCullFace(GL10.GL_BACK); // OpenGL docs

		// Enabled the vertices buffer for writing and to be used during
		// rendering.
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);// OpenGL docs.
		// Specifies the location and data format of an array of vertex
		// coordinates to use when rendering.
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, // OpenGL docs
                                 vertexBuffer);

		gl.glDrawElements(GL10.GL_TRIANGLES, indices.length,// OpenGL docs
				  GL10.GL_UNSIGNED_SHORT, indexBuffer);

		// Disable the vertices buffer.
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY); // OpenGL docs
		// Disable face culling.
		gl.glDisable(GL10.GL_CULL_FACE); // OpenGL docs
	}

}