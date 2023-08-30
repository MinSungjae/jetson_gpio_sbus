#include "jetson_gpio_sbus/jetson_gpio_sbus.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "gpio_sbus");
    ros::NodeHandle nh;

    ros::Rate rate(10);

    std::string jetson_model = getJetsonModel();
    int pwm_pin = get_pwm_pin();
    ROS_INFO_STREAM("Jetson model: " << jetson_model << " and pin : " << pwm_pin);

    // Pin Setup.
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(pwm_pin, GPIO::OUT, GPIO::HIGH);

    GPIO_SBUS gpio_sbus(&nh, jetson_model, pwm_pin);

    while(ros::ok())
    {
        gpio_sbus.run();
        ros::spinOnce();
        rate.sleep();
    }

    GPIO::cleanup();

    return 0;
}