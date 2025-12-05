package com.baidu.location.demo;


import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;


import com.baidu.location.demo.R;
import com.baidu.location.demo.mqtt.MyMqttService;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * 定位图标指示方向示例demo
 */
public class MainActivity extends AppCompatActivity {

    private static String action = "com.android.mqtt_msg";
    private String TAG = "hello";
    private Handler handler = new Handler(Looper.getMainLooper());
    private Runnable runnable;
    private Intent mIntent;
    private int first_msg = 0;
    /*************************项目使用变量*************************/

    private TextView tv_temp;
    private TextView tv_humi;
    private TextView tv_smoke;
    private TextView tv_air;

/***********************************/
    private TextView tv_temp2;
    private TextView tv_humi2;
    private TextView tv_smoke2;
    private TextView tv_air2;


    private TextView tv_temp_th;
    private TextView tv_humi_th;
    private TextView tv_mq2_th;
    private TextView tv_mq135_th;


    private int temp_value =0;
    private int humi_value =0;
    private int smoke_value =0;
    private int air_value =0;

    private int dev_id =0;
    private int beep_state =0;
    private int fan_state =0;
    private int auto_mode =0;

    private int temp_th =38;
    private int humi_th =60;
    private int mq2_th =60;
    private int mq135_th =20;
    /*************************项目使用变量*************************/



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        timer_send_init();  //定时器初始化
        /*************************控件初始化*************************/

        tv_temp = findViewById(R.id.tv_temp);
        tv_humi = findViewById(R.id.tv_humi);
        tv_smoke = findViewById(R.id.tv_smoke);
        tv_air = findViewById(R.id.tv_air);

        tv_temp2 = findViewById(R.id.tv_temp2);
        tv_humi2 = findViewById(R.id.tv_humi2);
        tv_smoke2 = findViewById(R.id.tv_smoke2);
        tv_air2 = findViewById(R.id.tv_air2);


        tv_temp_th = findViewById(R.id.tv_temp_th);
        tv_humi_th = findViewById(R.id.tv_humi_th);
        tv_mq2_th = findViewById(R.id.tv_mq2_th);
        tv_mq135_th = findViewById(R.id.tv_mq135_th);

        findViewById(R.id.btn_temp_jia).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                temp_th++;
                tv_temp_th.setText(temp_th + "");
            }
        });

        findViewById(R.id.btn_temp_jian).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                temp_th--;
                tv_temp_th.setText(temp_th + "");
            }
        });

        findViewById(R.id.btn_humi_jia).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                humi_th++;
                tv_humi_th.setText(humi_th + "");
            }
        });

        findViewById(R.id.btn_humi_jian).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                humi_th--;
                tv_humi_th.setText(humi_th + "");
            }
        });

        findViewById(R.id.btn_mq2_jia).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mq2_th++;
                tv_mq2_th.setText(mq2_th + "");
            }
        });

        findViewById(R.id.btn_mq2_jian).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mq2_th--;
                tv_mq2_th.setText(mq2_th + "");
            }
        });

        findViewById(R.id.btn_mq135_jia).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mq135_th++;
                tv_mq135_th.setText(mq135_th + "");
            }
        });

        findViewById(R.id.btn_mq135_jian).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mq135_th--;
                tv_mq135_th.setText(mq135_th + "");
            }
        });

        Switch btn_auto = findViewById(R.id.btn_auto);
        btn_auto.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    auto_mode=1;
                    dev_id=1;
                } else {
                    auto_mode=0;
                    dev_id=1;
                }
            }
        });

        Switch btn_beep = findViewById(R.id.btn_beep);
        btn_beep.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    beep_state=1;
                    dev_id=1;
                } else {
                    beep_state=0;
                    dev_id=1;
                }
            }
        });

        Switch btn_fan = findViewById(R.id.btn_fan);
        btn_fan.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    fan_state=70;
                    dev_id=1;
                } else {
                    fan_state=0;
                    dev_id=1;
                }
            }
        });



        Switch btn_auto2 = findViewById(R.id.btn_auto2);
        btn_auto2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    auto_mode=1;
                    dev_id=2;
                } else {
                    auto_mode=0;
                    dev_id=2;
                }
            }
        });

        Switch btn_beep2 = findViewById(R.id.btn_beep2);
        btn_beep2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    beep_state=1;
                    dev_id=2;
                } else {
                    beep_state=0;
                    dev_id=2;
                }
            }
        });

        Switch btn_fan2 = findViewById(R.id.btn_fan2);
        btn_fan2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) {
                    fan_state=70;
                    dev_id=2;
                } else {
                    fan_state=0;
                    dev_id=2;
                }
            }
        });

        /*************************控件初始化*************************/

        /*************************开启服务*************************/
        mIntent = new Intent(MainActivity.this, MyMqttService.class);
        startService(mIntent);
        /*************************开启服务*************************/

        /*************************通过广播接收的方式从MqttService中接收数据*************************/
        IntentFilter filter = new IntentFilter(MainActivity.action);
        getApplicationContext().registerReceiver(MainActivity_broadcastReceiver, filter);
        Log.d(TAG,"MainActivity start");
        /*************************通过广播接收的方式从MqttService中接收数据*************************/
    }

    /**
     * 广播消息接收器
     */
    public BroadcastReceiver MainActivity_broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent msgintent) {
            // TODO Auto-generated method stub
            String ReceiverStr = msgintent.getExtras().getString("MQTT_MSG");
            if(ReceiverStr==null) {
                return;
            }

            if(first_msg == 0) {
                handler.post(runnable); // 开始定时器
                first_msg = 1;
            }
            int id =0;
            JSONObject jsonObjectALL = null;
            try {
                jsonObjectALL = new JSONObject(ReceiverStr);
                temp_value = jsonObjectALL.getInt("temp");
                humi_value  = jsonObjectALL.getInt("humi");
                smoke_value = jsonObjectALL.getInt("mq2");
                air_value = jsonObjectALL.getInt("mq135");
                id = jsonObjectALL.getInt("id");
            } catch (JSONException e) {
                throw new RuntimeException(e);
            }
            /**************************************组件内容更新*******************************************/
            if(id==1) {
                tv_temp.setText(temp_value + "℃");
                tv_humi.setText(humi_value + "%");
                tv_smoke.setText(smoke_value + "ppm");
                tv_air.setText(air_value + "ml");
            } else {
                tv_temp2.setText(temp_value + "℃");
                tv_humi2.setText(humi_value + "%");
                tv_smoke2.setText(smoke_value + "ppm");
                tv_air2.setText(air_value + "ml");
            }


//            if(auto_mode==1) {
//                if ((temp_value > temp_h) || (temp_value < temp_l) ||
//                        (humi_value > humi_h) || (humi_value < humi_l) ||
//                        (rain_value > rain_h) || (rain_value < rain_l) ||
//                        (smoke_value > smoke_h) || (smoke_value < smoke_l) ||
//                        (lux_value > lux_h) || (lux_value < lux_l)) {
//                    beep_state = 1;
//                } else {
//                    beep_state = 0;
//                }
//            }

            /**************************************组件内容更新*******************************************/

            Log.d(TAG, "MQTT接收消息:<<<<<<"+ReceiverStr);

        }
    };

    /**
     * 定时发送数据的定时器初始化
     */
    private void timer_send_init() {
        runnable = new Runnable() {
            @Override
            public void run() {
                timer_send_task();
                handler.postDelayed(this, 1000); // 1000毫秒 = 1秒
            }
        };
    }
    /**
     * 定时发送数据
     */
    private void timer_send_task() {
        JSONObject data_obj = new JSONObject();
        try {
            data_obj.put("fan",fan_state);
            data_obj.put("beep",beep_state);
            data_obj.put("id",dev_id);
            data_obj.put("auto",auto_mode);
            data_obj.put("temp",temp_th);
            data_obj.put("humi",humi_th);
            data_obj.put("mq2",mq2_th);
            data_obj.put("mq135",mq135_th);
        } catch (JSONException e) {
            throw new RuntimeException(e);
        }
        Log.d(TAG,"MQTT发送消息:>>>>>>" + data_obj.toString());
        MyMqttService.publish_message(data_obj.toString());
    }
}