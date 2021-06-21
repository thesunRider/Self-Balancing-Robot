import csv  

header = ['time', 'input', 'output']

with open('pid_val.csv', 'w', encoding='UTF8', newline='') as f:
	writer = csv.writer(f)
	writer.writerow(header)

	with open('pid_data.txt', 'rb') as f:
		buf = f.read()
		
	time_offset = 0
	read = buf.decode('utf-8')

	split_msg = read.split('\r\n')
	for x in range(0,len(split_msg)):
		spl = (split_msg[x])[13:].split(',')
		if x == 0:
			time_offset = int(spl[2])

		writer.writerow([str(round((int(spl[2])-time_offset)/1000,0)) , spl[0] , spl[1]])