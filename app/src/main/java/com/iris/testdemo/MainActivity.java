package com.iris.testdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;


public class MainActivity extends AppCompatActivity {

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
        // 隐藏标题栏
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        // 隐藏状态栏
        // 定义全屏参数
        int flag = WindowManager.LayoutParams.FLAG_FULLSCREEN;
        // 获得当前窗体对象
        Window window = getWindow();
        // 设置当前窗体为全屏显示
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

    private float xDown, yDown;
    private void processTouchEvent(MotionEvent event){

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                break;
            case MotionEvent.ACTION_UP:
                break;
            case MotionEvent.ACTION_MOVE:
                xDown = event.getX();
                yDown = event.getY();
                setCameraDir(xDown, yDown, 0);
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
    public native void setCameraDir(float x, float y, float z);
}
