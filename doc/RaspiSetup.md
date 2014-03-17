# Setup the Raspberry with Arch Linux
## Installation
<http://archlinuxarm.org/platforms/armv6/raspberry-pi>
## locale config
Set language and some country specific number formats

- edit /etc/locale.gen
    - remove # for
		- de_DE.UTF-8
		- en_DK.UTF-8 
- edit /etc/locale.conf
    - export LC_DATE=en_DK.utf8
    - export LC_NUMERIC=en_DK.utf8
    - export LC_TIME=en_DK.utf8
    - export LANG=de_DE.utf8
- locale-gen

Set the keyboard layout

- echo KEYMAP=de-latin1-nodeadkeys > /etc/vconsole.conf

Set the timezone

- ln -s /usr/share/zoneinfo/Europe/Berlin /etc/localtime

Set the name for your Pi, you need to edit the file /etc/hostname and /etc/hosts 

- edit /etc/hostname 
	- change "alarmpi" to the name chosen for your Pi. 
- edit /etc/hosts
	- modify:
		- 127.0.0.1 localhost.localdomain localhost *yourhostname*
		- replacing *yourhostname* with the name you put in /etc/hostname

<https://wiki.archlinux.de/title/Arch_Linux_auf_Deutsch_stellen>
<http://elinux.org/ArchLinux_Install_Guide>
## Network setup
### Static ip for eth0
### wlan0 Access Point
#### Static ip for wlan0
#### hostapd
##### Install hostapd
##### Patch hostapd for Edimaxx wlan dongle
##### config hostapd
#### dhcp for wlan
##### install dhcpd
##### config dhcpd

## WiringPi
pacman -S wiringpi

## Debugging
pacman -S gdb
