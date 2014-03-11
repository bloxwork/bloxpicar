# Setup the Raspberry with Arch Linux
## Installation
## local config
- echo LANG=de_DE.UTF-8 > /etc/locale.conf
- echo KEYMAP=de-latin1-nodeadkeys > /etc/vconsole.conf
- ln -s /usr/share/zoneinfo/Europe/Berlin /etc/localtime

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
