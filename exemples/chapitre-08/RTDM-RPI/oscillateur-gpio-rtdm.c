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

static int periode_us = 1000;
module_param(periode_us, int, 0644);

static void timer_oscillateur(rtdm_timer_t *);
static rtdm_timer_t rtimer;

// Broche 15 du port P1 du Raspberry Pi : GPIO 22
#define GPIO_OSCILLATEUR 22

static int __init init_oscillateur (void)
{
	int err;

	if ((err = gpio_request(GPIO_OSCILLATEUR, THIS_MODULE->name)) != 0) {
		return err;
	}
	if ((err = gpio_direction_output(GPIO_OSCILLATEUR, 1)) != 0) {
		gpio_free(GPIO_OSCILLATEUR);
		return err;
	}

	if ((err = rtdm_timer_init(& rtimer, timer_oscillateur, "Oscillateur")) != 0) {
		gpio_free(GPIO_OSCILLATEUR);
		return err;
	}

	if ((err = rtdm_timer_start(& rtimer, periode_us*1000, periode_us*1000, RTDM_TIMERMODE_RELATIVE)) != 0) {
		rtdm_timer_destroy(& rtimer);
		gpio_free(GPIO_OSCILLATEUR);
		return err;
	}
	return 0;
}


static void __exit exit_oscillateur (void)
{
	rtdm_timer_stop(& rtimer);
	rtdm_timer_destroy(& rtimer);
	gpio_free(GPIO_OSCILLATEUR);
}


static void timer_oscillateur(rtdm_timer_t * unused)
{
	static int value = 0;
	gpio_set_value(GPIO_OSCILLATEUR, value);
	value = 1 - value;
}


module_init(init_oscillateur);
module_exit(exit_oscillateur);
MODULE_LICENSE("GPL");

