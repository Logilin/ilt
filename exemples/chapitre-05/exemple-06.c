#include <linux/interrupt.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/gpio.h>

// L'entree se fait depuis la broche 16 (GPIO 23).
#define RPI_IRQ_GPIO_IN  23


// La sortie va sur la broche 18 (GPIO 24).
#define RPI_IRQ_GPIO_OUT 24

static irqreturn_t exemple_handler(int irq, void * ident)
{
	if (gpio_get_value(RPI_IRQ_GPIO_IN) == 0)
		return IRQ_NONE;
	return IRQ_WAKE_THREAD;
}


static irqreturn_t exemple_thread(int irq, void * ident)
{
	static int out_value = 0;

	gpio_set_value(RPI_IRQ_GPIO_OUT, out_value);
	out_value = 1 - out_value;

	return IRQ_HANDLED;
}


static int __init exemple_init (void)
{
	int erreur;
	
	if ((erreur = gpio_request(RPI_IRQ_GPIO_OUT, THIS_MODULE->name)) != 0)
		return erreur;

	// Demander l'acces au GPIO d'entree.
	if ((erreur = gpio_request(RPI_IRQ_GPIO_IN, THIS_MODULE->name)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		return erreur;
	}

	// Configurer la direction du GPIO de sortie.
	if ((erreur = gpio_direction_output(RPI_IRQ_GPIO_OUT,1)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return erreur;
	}

	// Configurer la direction du GPIO d'entree.
	if ((erreur = gpio_direction_input(RPI_IRQ_GPIO_IN)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return erreur;
	}

	// Installer le handler d'interruption.
	if ((erreur = request_threaded_irq(gpio_to_irq(RPI_IRQ_GPIO_IN),
	                       exemple_handler,
	                       exemple_thread,
	                       IRQF_SHARED | IRQF_TRIGGER_RISING,
	                       THIS_MODULE->name,
	                       THIS_MODULE->name)) != 0) {
		gpio_free(RPI_IRQ_GPIO_OUT);
		gpio_free(RPI_IRQ_GPIO_IN);
		return erreur;
	}

	return 0; 
}



static void __exit exemple_exit (void)
{
	// Retrait du handler d'interruption.
	free_irq(gpio_to_irq(RPI_IRQ_GPIO_IN), THIS_MODULE->name);
	// Liberation des GPIO.
	gpio_free(RPI_IRQ_GPIO_OUT);
	gpio_free(RPI_IRQ_GPIO_IN);
}



module_init(exemple_init);
module_exit(exemple_exit);
MODULE_LICENSE("GPL");

