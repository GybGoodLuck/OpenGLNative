package com.iris.testdemo;

import android.content.Context;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class Sensor implements SensorEventListener {

    private final static String TAG = "Sensor";

    private SensorManager mSensorManager;
    private Context mContex;
    private volatile float[] rotQ = new float[4];

    public Sensor(Context context) {
        mContex = context;
        mSensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        mSensorManager.registerListener(this,
                mSensorManager.getDefaultSensor(android.hardware.Sensor.TYPE_GAME_ROTATION_VECTOR),
                SensorManager.SENSOR_DELAY_GAME);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        float[] values = event.values;
        int sensorType = event.sensor.getType();
        switch (sensorType) {
            case android.hardware.Sensor.TYPE_GAME_ROTATION_VECTOR:
                SensorManager.getQuaternionFromVector(rotQ, values);
                break;
                default:
                    break;
        }
        setRotQ(rotQ[0], rotQ[1], rotQ[2], rotQ[3]);
    }

    @Override
    public void onAccuracyChanged(android.hardware.Sensor sensor, int accuracy) {

    }

    public void disableSensor() {
        if (mSensorManager != null) {
            mSensorManager.unregisterListener(this);
            mSensorManager = null;
        }
    }

    public native void setRotQ(float w, float x, float y, float z);
}
