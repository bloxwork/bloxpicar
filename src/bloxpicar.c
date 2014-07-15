/**
 \file
 bloxpicar.c
 \brief
 Mainfile for the bloxpicar

 \par Description:

 \par Module-History (last 10 changes):
 \verbatim
 Date            Author              Reason
 Mar 12, 2014    Alexander Block     - Creation

 \endverbatim

 \par Copyright Notice:
 \verbatim
 Copyright (C) 2013  Alexander Block

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 \endverbatim
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wiringPi.h>

#define BLOX_CAR_VERSION "0.0.1"

#define SERVO_CONNECTED_TO_RASPI 1
#define SERVO_GPIO              1   /**< GPIO output to control the Servo */

#define PWM_RANGE               100
#define H_BRIDGE_USE_SW_PWM     1
#if H_BRIDGE_USE_SW_PWM
    #define H_BRIDGE_ENABLE_GPIO 4
#else
#if defined SERVO_CONNECTED_TO_RASPI
    #error HW PWM already in use
#else
    #define H_BRIDGE_ENABLE_GPIO 1
#endif
#endif
#define H_BRIDGE_IN1_FORWARD    2
#define H_BRIDGE_IN2_REVERSE    3

typedef struct rxmsg_s_
{
    int len;
    int version;
    int speed;
    int direction;
} rxmsg_s;

static void msSleep(int dwSleepMS);
/**
 * setSpeed
 * @param speed: -100 ... 100 ( minus = reverse )
 */
static void setSpeed( signed int speed );
static void setDirection( int iDirection );
static void socket_communication(void);


static void msSleep(int dwSleepMS) {
    struct timespec sTimeSpec;

    sTimeSpec.tv_sec = (time_t) (dwSleepMS / 1000);
    sTimeSpec.tv_nsec = (time_t) ((dwSleepMS % 1000) * 1000 * 1000);

    (void) nanosleep(&sTimeSpec, NULL );
}
int
main( int argc, char *argv[] )
{
    int i;
    printf("BloxCar: V%s %s %s\n", BLOX_CAR_VERSION, __DATE__, __TIME__);


    //Setup the wiring PI Lib
    wiringPiSetup();
#if H_BRIDGE_USE_SW_PWM
    softPwmCreate (H_BRIDGE_ENABLE_GPIO, 0, PWM_RANGE) ;
#else
    pinMode(H_BRIDGE_ENABLE_GPIO, PWM_OUTPUT);
#endif

    pinMode(SERVO_GPIO, PWM_OUTPUT);
    pwmWrite(SERVO_GPIO, 0);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);
    pwmSetRange(1000);

    pinMode(H_BRIDGE_IN1_FORWARD, OUTPUT);
    pinMode(H_BRIDGE_IN2_REVERSE, OUTPUT);

    socket_communication();

#if 0
    digitalWrite(H_BRIDGE_IN1_FORWARD, LOW) ;
    digitalWrite(H_BRIDGE_IN2_REVERSE, HIGH) ;

//HW PWM    for(  i=350; i<1024;i++)
        for(  i=0; i<PWM_RANGE;i++)
    {
        softPwmWrite (4, i) ;
        pwmWrite (1, i);
        msSleep(80);
        printf("i:%i\n",i);
    }
#endif
    return 0;
}

static void socket_communication(void)
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    rxmsg_s readBuff;
    int readlen = 0;
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*) NULL, NULL );

        printf("accepted client");
        ticks = time(NULL );
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff));

        while (readlen >= 0)
        {
            readlen = recv(connfd, &readBuff, sizeof(readBuff),0);
            if (readlen > 0)
            {
                printf("rx len:%i version:%i speed:%i direction:%i\n",
                        readBuff.len, readBuff.version, readBuff.speed,
                        readBuff.direction);
                setSpeed( readBuff.speed );
                setDirection( readBuff.direction );
                write(connfd, &readBuff, readlen);
            }

            if(readlen <= 0)
            {
                printf("read error: %i\n", readlen);
                printf("Socket recv()! %s\n", strerror(errno));
                break;
            }
        }
        close(connfd);
        sleep(1);
    }
}

static void setSpeed( signed int speed )
{
    static signed int iCurrSpeed = 0;

    printf("setSpeed: current:%i new:%i\n", iCurrSpeed, speed);

    if((speed >= ( PWM_RANGE * -1))&&(speed <= PWM_RANGE))
    {
        if( iCurrSpeed != speed )
        {
            if( ( iCurrSpeed <= 0 ) && ( speed > 0 ) )
            {
                digitalWrite(H_BRIDGE_IN2_REVERSE, HIGH) ;
                digitalWrite(H_BRIDGE_IN1_FORWARD, LOW) ;
            }
            else if( ( iCurrSpeed >= 0 ) && ( speed < 0 ) )
            {
                digitalWrite(H_BRIDGE_IN2_REVERSE, LOW) ;
                digitalWrite(H_BRIDGE_IN1_FORWARD, HIGH) ;
            }
            else if ( 0 == speed )
            {
                digitalWrite(H_BRIDGE_IN2_REVERSE, LOW) ;
                digitalWrite(H_BRIDGE_IN1_FORWARD, LOW) ;
            }
    #if H_BRIDGE_USE_SW_PWM
            speed = speed<0?speed*-1:speed;
            softPwmWrite (H_BRIDGE_ENABLE_GPIO, speed) ;
    #else
            pwmWrite (H_BRIDGE_ENABLE_GPIO, speed);
    #endif
            iCurrSpeed = speed;
        }
    }
}

#define SERVO_MAX 110
#define SERVO_MIN 40

#define MAX_DIRECTION 100
#define MIN_DIRECTION -100

static void setDirection( int iDirection )
{
    pwmWrite (SERVO_GPIO, iDirection);
}
