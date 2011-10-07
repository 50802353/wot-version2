package bkit.wot;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.view.KeyEvent;

public class WOTActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.main);
        super.onCreate(savedInstanceState);
       	this.requestWindowFeature(Window.FEATURE_NO_TITLE); 
		this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN);
        GameGLSurfaceView view = new GameGLSurfaceView(getApplication());
   		setContentView(view);
   		view.setFocusable(true);
   		view.setFocusableInTouchMode(true);
    }
}