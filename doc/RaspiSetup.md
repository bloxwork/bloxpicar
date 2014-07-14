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
## Login
root
root
## Network setup
### Static ip for eth0
192.168.178.60
### wlan0 Access Point
#### Static ip for wlan0
192.168.1.1
/etc/systemd/system/network-wireless@.service
#### hostapd
##### Install hostapd
##### Patch hostapd for Edimaxx wlan dongle
##### config hostapd
/etc/hostapd/hostapd.conf
ssid=blockworx
wpa_passphrase=raspi-wlan
#### dhcp for wlan
/etc/dhcpd.conf
##### install dhcpd
##### config dhcpd

##History
    1  shutdown now
    2  ls /usr/share/zoneinfo/Europe/Berlin 
    3  rm /etc/localtime 
    4  ln -sf /usr/share/zoneinfo/Europe/Berlin  /etc/localtime
    5  vi /etc/hostname 
    6  vi /etc/hosts
    7  cat /etc/hosts
    8  /opt/vc/bin/raspistill 
    9  vi /boot/config.txt 
   10  reboot
   11  /opt/vc/bin/raspistill 
   12  /opt/vc/bin/raspistill /d
   13  /opt/vc/bin/raspistill -d
   14  /opt/vc/bin/raspistill -d
   15  /opt/vc/bin/raspistill -d
   16  /opt/vc/bin/raspistill -d
   17  /opt/vc/bin/raspistill -/help
   18  /opt/vc/bin/raspistill --help
   19  /opt/vc/bin/raspistill -fp
   20  /opt/vc/bin/raspistill -f
   21  /opt/vc/bin/raspistill |more
   22  /opt/vc/bin/raspistill |head
   23  /opt/vc/bin/raspistill >help.txt
   24  /opt/vc/bin/raspistill &>help.txt
   25  cat help.txt 
   26  more help.txt 
   27  /opt/vc/bin/raspistill -k
   28  ls
   29  shutdown now
   30  /opt/vc/bin/raspistill -k
   31  echo LANG=de_DE.UTF-8 > /etc/locale.conf
   32  echo KEYMAP=de-latin1-nodeadkeys > /etc/vconsole.conf
   33  vi /etc/locale.gen 
   34  locale-gen 
   35  reboot
   36  shutdown now
   37  time
   38  date
   39  vi /etc/conf.d/network
   40  vi /etc/systemd/system/network.service
   41  systemctl enable network.service
   42  vi /etc/resolv.conf 
   43  reboot
   44  lsusb
   45  pacman -S iw
   46  iw list
   47  pacman -S hostapd
   48  pacman -S udhcpd
   49  cd /tmp
   50  wget -c http://dl.dropbox.com/u/1663660/hostapd/hostapd.zip
   51  unzip hostapd.zip 
   52  pacman -S unzip
   53  unzip hostapd.zip 
   54  ls
   55  cd /usr/sbin/hostapd
   56  mv /usr/sbin/hostapd /usr/sbin/hostapd_org
   57  cp hostapd /usr/sbin/
   58  chmod +x /usr/sbin/hostapd
   59  cd -
   60  vi /etc/hostapd/hostapd.conf 
   61  /usr/sbin/hostapd -dd /etc/hostapd/hostapd.conf
   62  shutdown now
   63  systemctl enable hostapd
   64  systemctl status hostapd
   65  vi /etc/hostapd/hostapd.conf 
   66  cat /etc/hostapd/hostapd.conf |grep driver
   67  pacman -S isc-dhcp-server
   68  systemctl start hostapd
   69  vi /etc/hostapd/hostapd.conf 
   70  /usr/sbin/hostapd -dd /etc/hostapd/hostapd.conf
   71  systemctl status hostapd
   72  systemctl restart hostapd
   73  pacman -S dhcp
   74  vi /etc/dhcpd.conf 
   75  shutdown now
   76  ifconfig
   77  vi /etc/conf.d/network-wireless@wlan0
   78  vi /etc/systemd/system/network-wireless@.service
   79  systemctl enable network-wireless@wlan0
   80  systemctl start network-wireless@wlan0
   81  systemctl status network-wireless@wlan0
   82  ip link set dev wlan0 down
   83  systemctl start network-wireless@wlan0
   84  systemctl status network-wireless@wlan0
   85  ifconfig
   86  ip link set dev wlan0 down
   87  ifconfig
   88  ip link set dev wlan0 down
   89  vi /etc/conf.d/network-wireless@wlan0
   90  systemctl start network-wireless@wlan0
   91  systemctl status network-wireless@wlan0
   92  ifconfig
   93  vi /etc/systemd/system/network-wireless@.service
   94  systemctl start network-wireless@wlan0
   95  systemctl daemon-reload
   96  systemctl start network-wireless@wlan0
   97  ifconfig
   98  vi /etc/dhcpd.conf 
   99  cp /etc/dhcpd.conf /etc/dhcpd.conf.org
  100  vi /etc/dhcpd.conf 
  101  rm /etc/dhcpd.conf
  102  vi /etc/dhcpd.conf 
  103  systemctl start dhcpd4
  104  vi /etc/hostapd/hostapd.conf 
  105  /usr/sbin/hostapd -dd /etc/hostapd/hostapd.conf
  106  systemctl restart hostapd
  107  git --version
  108  shutdown now
  109  echo $PWD'>'
  110  chmod +x /tmp/block-box;exit
  111  echo $PWD'>'
  112  gdbserver :2345 /tmp/block-box;exit
  113  echo $PWD'>'
  114  chmod +x /tmp/bloxpicar;exit
  115  echo $PWD'>'
  116  gdbserver :2345 /tmp/bloxpicar;exit
  117  pacman -S gdbserver
  118  pacman -S gdb
  119  pacman -S gdb-server
  120  pacman -S gdb
  121  ifconfig
  122  pacman -S gdb
  123  if down wlan0
  124  ifconfig wlan0 down
  125  ifconfig
  126  pacman -S gdb
  127  pacman -S gdb
  128  pacman -S gdb
  129  pacman -S gdb
  130  pacman -S gdb
  131  cd /tmp/
  132  ./bloxpicar 
  133  pacman -S wiringPi
  134  pacman -S wiringpi
  135  pacman -S gdb
  136  ./bloxpicar 
  137  ifconfig wlan0 up
  138  ifconfig
  139  cat /etc/hostapd/hostapd.conf |raspi
  140  cat /etc/hostapd/hostapd.conf |grep raspi
  141  ./bloxpicar 
  142  pacman -S gdb
  143  shutdown now
  144  pacman -S gdb
  145  pacman -S sqlite
  146  ps -a
  147  ps -aux
  148  systemctl start dhcpd4
  149  systemctl enable dhcpd4
  150  ifconfig


## WiringPi
pacman -S wiringpi

## Debugging
pacman -S gdb
