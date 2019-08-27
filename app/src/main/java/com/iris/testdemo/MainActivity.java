package com.iris.testdemo;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;


public class MainActivity extends Activity {

    private final static String TAG = "GLTest MainActivity";

    private SurfaceView mSurfaceView;

    private Sensor mSensor;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        int flag = WindowManager.LayoutParams.FLAG_FULLSCREEN;
        Window window = getWindow();
        window.setFlags(flag, flag);

        setContentView(R.layout.activity_main);

        mSurfaceView = findViewById(R.id.surfaceView);
        mSensor = new Sensor(this);

        mSurfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                startRenderThread(holder.getSurface());
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {

            }
        });
    }

    private void processTouchEvent(MotionEvent event){

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                break;
            case MotionEvent.ACTION_UP:
                break;
            case MotionEvent.ACTION_MOVE:
                break;
                default:
                break;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        switch (event.getActionButton()) {
            case 0:
                processTouchEvent(event);
                break;
                default:
                    break;
        }

        return true;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void startRenderThread(Surface surface);
}
