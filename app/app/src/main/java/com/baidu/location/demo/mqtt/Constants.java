package com.baidu.location.demo.mqtt;

/**
 * Created by Administrator on 2018/8/6.
 * 常量类
 */

public class Constants {
    //测试账号:broker.emqx.io,1883
    public static final String client_id = "k12ayd2LfMQ.app_dev|securemode=2,signmethod=hmacsha256,timestamp=1712564343441|";//客户端ID，一般以客户端唯一标识符表示
    public static final String host = "iot-06z00b94ms3z4xb.mqtt.iothub.aliyuncs.com";//服务器地址
    public static final String port = "1883";//服务器端口号
    public static final String username = "app_dev&k12ayd2LfMQ";//用户名
    public static final String password = "4ee1f7c4aa7033d88e872d6e5839f043d40aeb5f16fbec176c57b5bcc9cefacd";//密码
    public static final String pub_topic = "/k12ayd2LfMQ/app_dev/user/update";//发布主题
    public static final String sub_topic = "/k12ayd2LfMQ/app_dev/user/get";//订阅主题
}
