#include "jetson_gpio_sbus/jetson_gpio_sbus.h"

GPIO_SBUS::GPIO_SBUS(ros::NodeHandle* nh, std::string jetson_model, int pwm_pin): _nh(nh), _jetson_model(jetson_model), _pwm_pin(pwm_pin),
                    pwm(GPIO::PWM(_pwm_pin, PWM_FREQ))
{
    if(_pwm_pin != UNKNOWN_PIN)
        ROS_INFO_STREAM("Output SBUS pin setted on pin: " << _pwm_pin);
    else
        ROS_ERROR("Jetson board does not support PWM OUTPUT!");    

    // Settup output pin to default zero PWM
    // GPIO::setup(_pwm_pin, GPIO::OUT, GPIO::HIGH);
    GPIO::setup(29, GPIO::OUT);

    // pwm = GPIO::PWM(15, 50);
    pwm.start(50);

    //In order to prevent multiple calls to the callback functions by collapsing multiple events in to a single one, a debounce time can be optionally set
    //GPIO::add_event_detect(but_pin, GPIO::Edge::RISING, blink, 10);

    model_pub = _nh->advertise<std_msgs::String>("jetson_model", 1, this);
}

bool GPIO_SBUS::run()
{
    std_msgs::String model_string;
    model_string.data = _jetson_model;
    model_pub.publish(model_string);

    // ROS_INFO("HIGH");
    // GPIO::output(29, GPIO::HIGH);
    // delayMs(50);
    // ROS_INFO("LOW");
    // GPIO::output(29, GPIO::LOW);
    // delayMs(50);

    return true;
}