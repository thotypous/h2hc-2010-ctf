import os, time

for i in range(1000):
    os.system('wget -O "captcha%03d.jpg" http://192.168.1.3/one/captcha.php'%i)
