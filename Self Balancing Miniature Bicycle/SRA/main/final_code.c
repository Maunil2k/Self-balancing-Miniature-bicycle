#include "SRA18.h"
#include "MPU.h"
#include "TUNING.h"
#include "SERVO.h"
#define MAX_CONE_ANGLE 35 /*it's still unknown */
#define GPIO_NUM0 25
#define GPIO_NUM1 26
#define GPIO_PWM0A_OUT 27
int setpoint = 0;
int initial_acce_angle = 0;
float pitch_angle = 0,roll_angle = 0;
float kp =5;
float kd =5;
float roll_error = 0  ,roll_difference =0 , prevroll_error =0 , pitch_feed =0 ,abs_pitch_feed=0;

void mcpwm_initialize()
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 20000;    //frequency = 500Hz,
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    gpio_set_direction(GPIO_NUM0, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM1, GPIO_MODE_OUTPUT);
}
void bot_forward(mcpwm_unit_t mcpwm_num, mcpwm_timer_t timer_num , float duty_cycle1)
{
	mcpwm_initialize();
    mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, duty_cycle1);
    gpio_set_level(GPIO_NUM0,0);
    gpio_set_level(GPIO_NUM1,1);
}

void calculate_roll_angle()
{
	roll_error = roll_angle ;
	roll_difference = prevroll_error - roll_angle;
	pitch_feed = kp*roll_error + kd*roll_difference;
	prevroll_error = roll_error;
	if(pitch_feed<0)
	{
	abs_pitch_feed = constrain(abs_pitch_feed,0,-MAX_CONE_ANGLE);
	abs_pitch_feed = absolute(abs_pitch_feed);
	abs_pitch_feed = 45 - abs_pitch_feed;
	}
	else
	{
	abs_pitch_feed = constrain(abs_pitch_feed,0,MAX_CONE_ANGLE);
	abs_pitch_feed = absolute(abs_pitch_feed);
	abs_pitch_feed = 45 - abs_pitch_feed;
	}
}
void balance_task(void *arg)

{
    
		uint8_t* acce_rd = (uint8_t*) malloc(BUFF_SIZE);

    	uint8_t* gyro_rd = (uint8_t*) malloc(BUFF_SIZE);

    	int16_t* acce_raw_value = (int16_t*) malloc(BUFF_SIZE/2);

        int16_t* gyro_raw_value = (int16_t*) malloc(BUFF_SIZE/2);

    
    	i2c_master_init();  
		//Initialise the I2C interface
    
		start_mpu();        
		//Intialise the MPU 
       	while (1) 
    
	{
   		initial_acce_angle = setpoint;
        calculate_angle(acce_rd,gyro_rd,acce_raw_value,gyro_raw_value,initial_acce_angle,&roll_angle,&pitch_angle);  //Function to calculate pitch angle based on intial accelerometer angle     
	    calculate_roll_angle();   
		mcpwm_example_gpio_initialize();   		
		mcpwm_example_servo_control(abs_pitch_feed,abs_pitch_feed,abs_pitch_feed);
		/*now set servo again to 0 */
		mcpwm_example_servo_control(45,45,45);
	} 
}
void app_main()

	{
	bot_forward(MCPWM_UNIT_0, MCPWM_TIMER_0 , 25.00);
    
	printf("initiation of self-balancing....\n");
    
	xTaskCreate(balance_task, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);

	}
