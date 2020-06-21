#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/module.h>

#include <rtdm/driver.h>

// Input on Raspberry Pi pin #16, GPIO 23
#define GPIO_IN  23

// Output on Raspberry Pi pin #15 GPIO 22
#define GPIO_OUT 22

static rtdm_irq_t irq_rtdm;


static int irq_handler(rtdm_irq_t *irq)
{
	static int value = 0;

	gpio_set_value(GPIO_OUT, value);
	value = 1 - value;

	return RTDM_IRQ_HANDLED;
}



static int __init example_init (void)
{
	int err;

	int irq_num = gpio_to_irq(GPIO_IN);

	if ((err = gpio_request(GPIO_IN, THIS_MODULE->name)) != 0) {
		return err;
	}
	if ((err = gpio_direction_input(GPIO_IN)) != 0) {
		gpio_free(GPIO_IN);
		return err;
	}
	if ((err = gpio_request(GPIO_OUT, THIS_MODULE->name)) != 0) {
		gpio_free(GPIO_IN);
		return err;
	}
	if ((err = gpio_direction_output(GPIO_OUT, 1)) != 0) {
		gpio_free(GPIO_OUT);
		gpio_free(GPIO_IN);
		return err;
	}

	irq_set_irq_type(irq_num,  IRQF_TRIGGER_RISING);

	if ((err = rtdm_irq_request(&irq_rtdm,
	                 irs_num, irs_handler,
	                 RTDM_IRQTYPE_EDGE,
	                 THIS_MODULE->name, NULL)) != 0) {
		gpio_free(GPIO_OUT);
		gpio_free(GPIO_IN);
		return err;
	}

	return 0;
}



static void __exit example_exit (void)
{
	rtdm_irq_free(&irq_rtdm);
	gpio_free(GPIO_OUT);
	gpio_free(GPIO_IN);
}


module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL");

