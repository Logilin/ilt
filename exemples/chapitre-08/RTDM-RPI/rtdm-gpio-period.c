#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>

#include <asm/uaccess.h>

#include <rtdm/driver.h>
#include <rtdm/gpio.h>

static int period_us = 1000;
module_param(period_us, int, 0644);

static void timer_func(rtdm_timer_t *);
static rtdm_timer_t rtimer;

// Output on Raspberry Pi pin #15, GPIO 22
#define GPIO_TIMER 22

static int __init init_timer(void)
{
	int err;

	if ((err = gpio_request(GPIO_TIMER, THIS_MODULE->name)) != 0) {
		return err;
	}
	if ((err = gpio_direction_output(GPIO_TIMER, 1)) != 0) {
		gpio_free(GPIO_TIMER);
		return err;
	}

	if ((err = rtdm_timer_init(&rtimer, timer_func, "My-timer")) != 0) {
		gpio_free(GPIO_TIMER);
		return err;
	}

	if ((err = rtdm_timer_start(&rtimer, period_us*1000, period_us*1000, RTDM_TIMERMODE_RELATIVE)) != 0) {
		rtdm_timer_destroy(&rtimer);
		gpio_free(GPIO_TIMER);
		return err;
	}
	return 0;
}


static void __exit exit_timer (void)
{
	rtdm_timer_stop(&rtimer);
	rtdm_timer_destroy(&rtimer);
	gpio_free(GPIO_TIMER);
}


static void timer_func(rtdm_timer_t *unused)
{
	static int value = 0;

	gpio_set_value(GPIO_TIMER, value);
	value = 1 - value;
}


module_init(init_timer);
module_exit(exit_timer);
MODULE_LICENSE("GPL");

