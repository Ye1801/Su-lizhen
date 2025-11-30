#include "dht11.h"

// 初始化GPIO引脚为输入模式
void dht11_gpio_in(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // 设置引脚模式为输入模式
    GPIO_InitStruct.Pin = DHT11_Pin;
    // 设置GPIO模式为输入模式
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    // 启用上拉电阻
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    // 设置GPIO速度为高频率
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    // 初始化GPIO端口
    HAL_GPIO_Init(DHT11_Port, &GPIO_InitStruct);
}

// 初始化GPIO引脚为输出模式
void dht11_gpio_out(void)  
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // 设置引脚模式为输出模式
    GPIO_InitStruct.Pin = DHT11_Pin;
    // 设置GPIO模式为推挽输出模式
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // 不启用上拉或下拉电阻
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    // 设置GPIO速度为高频率
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    // 初始化GPIO端口
    HAL_GPIO_Init(DHT11_Port, &GPIO_InitStruct);
}

// 写入高低电平值到DHT11引脚
void dht11_write(uint8_t level)  
{
    if(level == 0) {
        // 将引脚设置为低电平
        HAL_GPIO_WritePin(DHT11_Port, DHT11_Pin, GPIO_PIN_RESET);
    } else {
        // 将引脚设置为高电平
        HAL_GPIO_WritePin(DHT11_Port, DHT11_Pin, GPIO_PIN_SET);
    }
}

// 读取DHT11引脚的电平状态，并返回结果（高电平或低电平）
uint16_t dht11_read()  
{
    uint16_t value = HAL_GPIO_ReadPin(DHT11_Port, DHT11_Pin);
    return value;  // 返回引脚的电平状态
}

// 延时函数，延时指定微秒数
void delay_us(uint16_t time)  
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * time);  // 计算延时时间，单位：微秒
    while (delay--)  // 延时，直到delay减到0为止
    {
        ;  // 什么也不做，等待时间过去
    }
}

// 重置DHT11传感器，包括设置引脚为输出模式，发送复位信号等操作
void dht11_rst(void)  
{
    dht11_gpio_out();  // 设置引脚为输出模式
    dht11_write(0);  // 将引脚设置为低电平，发送复位信号（持续20毫秒）
    HAL_Delay(20);  // 等待20毫秒，让DHT11完成复位操作
    dht11_write(1);  // 将引脚设置为高电平，结束复位信号发送（再等待30微秒）
    delay_us(30);  // 延时30微秒，确保DHT11完成初始化并准备好发送数据（数据准备信号）
}

// 检查DHT11是否响应，若未响应则返回值为1，否则返回值为0（需要进一步判断是否是DHT11导致的未响应）
uint8_t dht11_check(void) 
{
    uint8_t retry = 0; // 重试次数初始化为0

    dht11_gpio_in(); // 设置引脚为输入模式

    while (dht11_read() && retry < 100) // 当引脚为高电平并且重试次数小于100时，循环继续
    {
        retry++; // 重试次数加1
        delay_us(1); // 延时1微秒
    }

    if (retry >= 100) return 1; // 如果重试次数达到或超过100次，返回值为1，表示DHT11未响应
    else retry = 0; // 重置重试次数为0

    while (!dht11_read() && retry < 100) // 当引脚为低电平并且重试次数小于100时，循环继续
    {
        retry++; // 重试次数加1
        delay_us(1); // 延时1微秒
    }

    if (retry >= 100) return 1; // 如果重试次数达到或超过100次，返回值为1，表示DHT11未响应
    return 0; // 返回值为0，表示DHT11响应正常
}

// 读取DHT11的一个位数据
uint8_t dht11_read_bit(void) 
{
    uint8_t retry = 0; // 重试次数初始化为0
    while (dht11_read() && retry < 100) // 当引脚为高电平并且重试次数小于100时，循环继续
    {
        retry++; // 重试次数加1
        delay_us(1); // 延时1微秒
    }
    retry = 0; // 重置重试次数为0
    while (!dht11_read() && retry < 100) // 当引脚为低电平并且重试次数小于100时，循环继续
    {
        retry++; // 重试次数加1
        delay_us(1); // 延时1微秒
    }
    delay_us(40); // 延时40微秒，等待DHT11发送完一个位的数据
    if (dht11_read()) return 1; // 如果引脚为高电平，返回值为1，表示读取到的数据为高电平
    else return 0; // 如果引脚为低电平，返回值为0，表示读取到的数据为低电平
}

// 读取DHT11的一个字节数据（8位）
uint8_t dht11_read_byte(void) 
{
    uint8_t i, dat = 0; // 定义一个字节变量dat用于存储读取结果，初始值为0
    for (i = 0; i < 8; i++) // 循环8次，每次读取一个位的数据并存储到dat中
    {
        dat <<= 1; // 将dat左移一位，腾出空位存储新读取的位
        dat |= dht11_read_bit(); // 调用函数dht11_read_bit()读取一个位的数据并存储到dat中
    }
    return dat; // 返回读取到的字节数据
}

// 读取DHT11的温度和湿度数据，并将数据存储在temp和humi指向的数组中（5个字节，分别为整数部分和小数部分）
uint8_t dht11_read_data(uint8_t *temp, uint8_t *humi) 
{
    uint8_t buf[5]; // 定义一个5个字节的数组buf用于存储读取到的温度和湿度数据（整数部分和小数部分）
    uint8_t i; // 定义一个循环计数器i用于循环读取5个字节的数据
    
    dht11_rst(); // 重置DHT11传感器，发送复位信号等操作（确保DHT11准备好发送数据）
	
    if(dht11_check()==0) 
		{
        for (i = 0; i < 5; i++) // 循环5次，每次读取一个字节的数据并存储到buf数组中
        {
            buf[i] = dht11_read_byte(); // 调用函数dht11_read_byte()读取一个字节的数据并存储到buf数组中
        }
    
        // 检查校验和是否正确（前四个字节是整数部分，最后一个字节是小数部分）
        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) 
        {
            *humi = buf[0]; // 将湿度整数部分存储到humi指向的变量中
            *temp = buf[2]; // 将温度整数部分存储到temp指向的变量中
            return 0; // 返回值为0，表示读取数据成功
        } else {
            return 1; // 如果校验和不正确，返回值为1，表示读取数据失败
        }
    } else 
		{
			return 1; // 如果校验和不正确，返回值为1，表示读取数据失败
		}
}

// 初始化DHT11传感器并检查其响应状态
uint8_t dht11_init(void)
{    
	dht11_rst(); // 重置DHT11传感器，发送复位信号等操作（确保DHT11准备好发送数据
	return dht11_check();
}








