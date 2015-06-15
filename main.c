#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

/*
 * Settings
 */
#define I2C_BUS_NAME "/dev/i2c-0"

/*
 * File descriptors
 */
int fd;

int main(int argc, char *argv[])
{
    int status;
    ssize_t bytes_read;
    char buf[6];
    char *buffer = (char *)malloc(1024 * sizeof(char));
    char *result = (char *)malloc(128 * 6 * sizeof(char));
    memset(result, 0, 128 * 6);

    printf("Starting i2cscan\n");

    /*
     * Open the device.
     */
    fd = open(I2C_BUS_NAME, O_RDWR);
    if(fd < 0)
    {
        printf("Cannot open the IIC device\n");
        return 1;
    }
    printf("/dev/i2c-0 is open\n");

    /*
     * Go through every address from 0 to 127 (0x7f)
     */
    for(int ctr = 0; ctr < 128; ctr++)
    {
        fprintf(stderr, "set address 0x%x...", ctr);
        status = ioctl(fd, I2C_SLAVE_FORCE, ctr);
        if(status < 0)
        {
            fprintf(stderr, "Unable to set address %d\n", ctr);
            return -1;
        }
        else
        {
            fprintf(stderr, " OK! ");
            fprintf(stderr, "Read a byte...");

            bytes_read = read(fd, buffer, 1);
                if(bytes_read < 0){
                    fprintf(stderr, " read error\n");
                }
                else
                {
                    fprintf(stderr, " OK!\n");
                    printf("Device with adr 0x%x detected\n", ctr);
                    sprintf(buf, "0x%x, ",ctr);
                    strcat(result, buf);
                }

        }
    }


    printf("Test done. Found devices with adr: %s\n\n",result);

    /* Release allocations */
    close(fd);

    return 0;
}
