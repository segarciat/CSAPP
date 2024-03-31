def cb(n: int) -> int:
	'''Count minimum number of bytes to represent n as a 32-bit two's complement integer'''
	if (type(n) is not int or n < -2**31 or n >= 2**31 )
		raise ValueError("n must be reprentable as a 32-bit two's complement number")
		
	# add 1 if 0, subtract 1 if negative 1
	normalize = int(not(n ^ 0)) -  int(not(n ^ -1))
	n = n + normalize
	m = n
	count = 0
	mask = -1 if n < 0 else 0
	for i in range(0,8):
		count = count + int(not not (m^mask))
		m = m >> 4
	count = count << 2 # Multiply by 4
	m = (n >> (count - 4))
	count = count - 4

	count = count + int(not not(m^mask))
	m = m >> 1
	count = count + int(not not(m^mask))
	m = m >> 1
	count = count + int(not not(m^mask))
	m = m >> 1
	count = count + int(not not(m^mask))
	m = m >> 1
	
	return count + int(not(normalize))
