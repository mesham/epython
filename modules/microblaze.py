def i2c_open_device(device_id):
	return native rtl_i2c_open_device(device_id)

def i2c_open(sda, sc1):
	return native rtl_i2c_open(sda, sc1)

def i2c_close(device_id):
	native rtl_i2c_close()

def i2c_get_num_devices():
	return native rtl_i2c_get_num_devices()