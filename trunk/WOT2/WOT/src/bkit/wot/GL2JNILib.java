package bkit.wot;

// Wrapper for native library

public class GL2JNILib {

     static {
         System.loadLibrary("gl2jni");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     public static native void init(int width, int height);
     public static native void step();
     public static native void KeyDown(int keycode);
     public static native void KeyUp(int keycode);
     public static native void TouchDown(int x, int y);
     public static native void TouchUp(int x, int y);
     public static native void TouchMove(int x, int y);
	 public static native boolean IsListenEvent();
}
