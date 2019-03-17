/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/


#include <linux/interrupt.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/gpio.h>


#define RPI_IRQ_GPIO_IN  23
#define RPI_IRQ_GPIO_OUT 24


static irqreturn_t my_irq_handler(int irq, void * ident)
{
	if (gpio_get_value(RPI_IRQ_GPIO_IN) == 0)
		return IRQ_NONE;
	return IRQ_WAKE_THREAD;
}



static irqreturn_t my_irq_thread(int irq, void * ident)
{
	static int out_value = 0;

	gpio_set_value(RPI_IRQ_GPIO_OUT, out_value);
	out_value = 1 - out_value;

	return IRQ_HANDLED;
}



static int __init my_module_init (void)
{
	int err;

	if ((err = gpio_request(RPI_IRQ_GPIO_OUT, THIS_MODULE->name)) != 0)
		return err;

	// Demander l'acces au GPIO d'entree.
	if ((err = gpio_request(RPI_IRQ_GPIO_IN, THIS_MODULE->name)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		return err;
	}

	// Configurer la direction du GPIO de sortie.
	if ((err = gpio_direction_output(RPI_IRQ_GPIO_OUT,1)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return err;
	}

	// Configurer la direction du GPIO d'entree.
	if ((err = gpio_direction_input(RPI_IRQ_GPIO_IN)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return err;
	}

	// Installer le handler d'interruption.
	if ((err = request_threaded_irq(gpio_to_irq(RPI_IRQ_GPIO_IN),
	                       my_irq_handler,
	                       my_irq_thread,
	                       IRQF_SHARED | IRQF_TRIGGER_RISING,
	                       THIS_MODULE->name,
	                       THIS_MODULE->name)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return err;
	}

	return 0;
}



static void __exit my_module_exit (void)
{
	// Retrait du handler d'interruption.
	free_irq(gpio_to_irq(RPI_IRQ_GPIO_IN), THIS_MODULE->name);
	// Liberation des GPIO.
	gpio_free(RPI_IRQ_GPIO_OUT);
	gpio_free(RPI_IRQ_GPIO_IN);
}



module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
