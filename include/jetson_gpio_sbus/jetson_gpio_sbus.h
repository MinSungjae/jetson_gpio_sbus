#ifndef __JETSON_GPIO_SBUS_H__
#define __JETSON_GPIO_SBUS_H__

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>

#include <string>
#include <chrono>
#include <thread>
#include <map>

#include <JetsonGPIO.h>

#define UNKNOWN_PIN -99

#define INPUT_SBUS1 10
#define INPUT_SBUS2 11

#define PWM_FREQ    50

inline void delayMs(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

const std::map<std::string, int> output_pins{
    {"JETSON_XAVIER", 18},    {"JETSON_NANO", 33},   {"JETSON_NX", 33},
    {"CLARA_AGX_XAVIER", 18}, {"JETSON_TX2_NX", 32}, {"JETSON_ORIN", 18}, 
    {"JETSON_ORIN_NX", 33}, {"JETSON_ORIN_NANO", 33}, 
};

inline int get_pwm_pin()
{
    if (output_pins.find(GPIO::model) == output_pins.end())
    {
        ROS_ERROR("PWM not supported on this board");
        return UNKNOWN_PIN;
    }

    return output_pins.at(GPIO::model);
}

inline std::string getJetsonModel()
{
    std::string jetson = GPIO::model;
    return jetson;
}

class GPIO_SBUS
{
private:
    ros::NodeHandle* _nh;

    ros::Publisher model_pub;

protected:
    std::string _jetson_model;
    int _pwm_pin;

    GPIO::PWM pwm;

public:
    GPIO_SBUS(ros::NodeHandle* nh, std::string jetson_model, int pwm_pin);

    bool run();
    // int get_pwm_pin();
    // std::string getJetsonModel();
};

#endif