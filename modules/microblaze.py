def i2c_open_device(device_id):
	return native rtl_i2c_open_device(device_id)

def i2c_open(sda, sc1):
	return native rtl_i2c_open(sda, sc1)

def i2c_write(device, address, data, length):
	native rtl_i2c_write(device, address, data, length)

def i2c_read(device, address, read_data, length):
	native rtl_i2c_read(device, address, read_data, length)

def i2c_close(device_id):
	native rtl_i2c_close()

def i2c_get_num_devices():
	return native rtl_i2c_get_num_devices()

def spi_open_device(device_id):
	return native rtl_spi_open_device(device_id)

def spi_open(spiclk, miso, mosi, ss):
	return native rtl_spi_open(spiclk, miso, mosi, ss)

def spi_configure(dev_id, clk_phase, clk_polarity):
	return native rtl_spi_configure(dev_id, clk_phase, clk_polarity)

def spi_transfer(dev_id, write_data, read_data, length):
	native rtl_spi_transfer(dev_id, write_data, read_data, length)

def spi_close(dev_id):
	native rtl_spi_close(dev_id)

def gpio_open_device(dev_id):
	return native rtl_gpio_open_device(dev_id)

def gpio_open(pin):
	return native rtl_gpio_open(pin)

def gpio_configure(parent, low, hi, channel):
	return native rtl_gpio_configure(parent, low, hi, channel)

def gpio_set_direction(device, direction):
	native rtl_gpio_set_direction(device, direction)

def gpio_write(device, value):
	native rtl_gpio_write(device, value)

def gpio_read(device):
	return native rtl_gpio_read(device)

def gpio_close(device):
	native rtl_gpio_close(device)

def timer_open(pin):
	return native rtl_timer_open(pin)

def timer_open_device(device):
	return native rtl_timer_open_device(device)

def timer_delay(device, cycles):
	native rtl_timer_delay(device, cycles)

def timer_pwm_generate(device, period, pulse):
	native rtl_timer_pwm_generate(device, period, pulse)

def timer_pwm_stop(device):
	native rtl_timer_pwm_stop(device)

def timer_close(device):
	native rtl_timer_close(device)

def delay_us(us):
	native rtl_delay_us(us)

def delay_ms(ms):
	native rtl_delay_ms(ms)

def uart_open(tx, rx):
	return native rtl_uart_open(tx, rx)

def uart_open_device(device):
	return native rtl_uart_open_device(device)

def uart_write(device, data, length):
	native rtl_uart_write(device, data, length)

def uart_read(device, read_data, length):
	native rtl_uart_read(device, read_data, length)

def uart_close(device):
	native rtl_uart_close(device)