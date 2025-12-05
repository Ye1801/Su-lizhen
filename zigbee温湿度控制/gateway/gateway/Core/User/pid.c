#include "pid.h"

#include <stdio.h>
 
// PID参数设置
float Kp = 0.5; // Proportional gain (比例系数)
float Ki = 1.2; // Integral gain (积分系数)
float Kd = 0.8; // Derivative gain (微分系数)
 
// 上次读取到的输入值
float prev_input = 0;



// 定义模糊集
typedef struct {
    double a; // 隶属度函数的参数a
    double b; // 隶属度函数的参数b
} FuzzySet;

 
// 计算PID控制量
float calculatePid(float input, float setpoint){
    static float integral = 0;
    
    // 计算当前时间点的误差
    float error = setpoint - input;
  
    // 更新累加项
    integral += error * Ki;
  
    // 计算微分项
    float derivative = (error - prev_input);
  
    // 根据PID公式计算控制量
    float control = Kp*error + integral + Kd*derivative;
  
    // 保存本次输入值作为下次计算的基准
    prev_input = input;
  
    return control;
}
 
//


// 计算隶属度函数值
double membership_function(FuzzySet *set, double x) {
    if (x <= set->a || x >= set->b) {
        return 0;
    } else if (x > set->a && x <= (set->a + set->b) / 2) {
        return 2 * (x - set->a) / (set->b - set->a);
    } else {
        return 2 * (set->b - x) / (set->b - set->a);
    }
}

// 模糊PID控制器
double fuzzy_pid(double error, double kp, double ki, double kd, FuzzySet *fuzzy_sets) {
    static double integral = 0;
    double derivative = error - fuzzy_sets[0].a;
    integral += error;

    double p = kp * membership_function(&fuzzy_sets[0], error);
    double i = ki * membership_function(&fuzzy_sets[1], integral);
    double d = kd * membership_function(&fuzzy_sets[2], derivative);

    return p + i + d;
}

//int main() {
//    FuzzySet fuzzy_sets[] = {
//        {-1, 0}, // 负大
//        {-0.5, 0.5}, // 负小
//        {0, 1} // 正小
//    };

//    double kp = 1, ki = 1, kd = 1;
//    double error = -0.8;

//    double output = fuzzy_pid(error, kp, ki, kd, fuzzy_sets);
//    printf("Output: %f", output);

//    return 0;
//}

//int main(){
//    // 测试样例
//    float currentInput = 34.67;
//    float targetSetpoint = 35.0;
//  
//    printf("Control value: %f\n", calculatePid(currentInput, targetSetpoint));
//  
//    return 0;
//}