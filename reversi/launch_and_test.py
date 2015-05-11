import shlex
import subprocess

cmd = ['sudo', '/home/pi/Documents/led-go/LED_Go_Board/reversi/Menu_main']
launchAgain = True
count = 0

while launchAgain and count < 100:
	count == count + 1
	print "Launching new instance of Reversi"
	return_code = subprocess.call(cmd)
	if return_code == 0:
		launchAgain = False
