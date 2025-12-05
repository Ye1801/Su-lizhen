package com.baidu.location.demo.mqtt;

import android.app.Service;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MyMqttService extends Service {

    public static final String TAG = "hello";
    private static String action = "com.android.mqtt_msg";
    private static MqttClient mqttClient;//客户端
    static MqttConnectOptions mqttConnectOptions;
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        init();
        return super.onStartCommand(intent, flags, startId);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    /**
     * 初始化
     */
    private void init() {

        String host = "tcp://" + Constants.host + ":" + Constants.port;//服务器地址（协议+地址+端口号）

        mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setUserName(Constants.username);
        mqttConnectOptions.setPassword(Constants.password.toCharArray());

        try {
            //(1)主机地址(2)客户端ID,一般以客户端唯一标识符(不能够和其它客户端重名)(3)最后一个参数是指数据保存在内存(具体保存什么数据,以后再说,其实现在我也不是很确定)
            mqttClient = new MqttClient(host, Constants.client_id, new MemoryPersistence());
        } catch (MqttException e) {
            e.printStackTrace();
        }

        mqttClient.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {
                Log.i(TAG, "connection lost");
            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {

                Intent intent = new Intent(action);
                Bundle bundle = new Bundle();
                bundle.putString("MQTT_MSG",  new String(message.getPayload()));
                intent.putExtras(bundle);
                sendBroadcast(intent);

                Log.d(TAG,"mqtt服务接收数据:"+new String(message.getPayload()));
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {
                Log.i(TAG, "msg delivered");
            }
        });

        /* Mqtt建连 */
        try {
            if (mqttClient.isConnected() == false) {
                mqttClient.connect(mqttConnectOptions);//连接服务器,连接不上会阻塞在这
            }
            Log.d(TAG,"连接成功");
            subscribe_message(Constants.sub_topic);

        } catch (MqttException e) {
            Log.d(TAG,"连接失败");
            e.printStackTrace();
        }
    }
    /**
     * 订阅特定的主题
     * @param topic mqtt主题
     */
    public void subscribe_message(String topic) {
        try {
            mqttClient.subscribe(topic,0);

        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    /**
     * 发布数据
     * @param payload 消息载荷
     */
    public static void publish_message(String payload) {
        try {
            if (mqttClient.isConnected() == false) {
                mqttClient.connect(mqttConnectOptions);//连接服务器,连接不上会阻塞在这
            }
            MqttMessage message = new MqttMessage();
            message.setPayload(payload.getBytes());
            message.setQos(0);
            mqttClient.publish(Constants.pub_topic,message);
        } catch (MqttException e) {
            Log.e(TAG, e.toString());
            e.printStackTrace();
        }
    }

    @Override
    public void onDestroy () {
        try {
            mqttClient.disconnect(); //断开连接
            Log.d(TAG, "断开MQTT连接！！！");
        } catch (MqttException e) {
            e.printStackTrace();
        }
        super.onDestroy();
    }
}