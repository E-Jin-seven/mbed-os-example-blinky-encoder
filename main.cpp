#include "mbed.h"
#include "platform/mbed_thread.h"
#define BLINKING_RATE_MS1   500
#define VCC (3.3)

class Counter {
public:
    Counter(PinName pin) : _interrupt(A1) {        // create the InterruptIn on the pin specified to Counter
        _interrupt.rise(callback(this, &Counter::increment)); // attach increment function of this counter instance
    }

    void increment() {
        _count++;
    }

    int read() {
        _count_pre = _count;
        _count = 0;
        return _count_pre;
    }

private:
    InterruptIn _interrupt;
    volatile int _count;
    volatile int _count_pre;
};

Counter counter(D13);

DigitalOut Digt1_R_AIN1(D2); //AIN1
PwmOut Pwr_R_AIN2(D1); //AIN2


/*
DigitalOut Digt1_L_BIN1(D5); //BIN1
PwmOut mypwm_L_BIN2"(D3); //BIN2
*/

AnalogIn Ain1_R(A0);
//AnalogIn Ain1_L(A5);

int main()
{
    Pwr_R_AIN2.period(0.01f);

    int i=0;

    printf("\n\n------Test Start------\n");

    while(1){

        Digt1_R_AIN1 = 1;
        //Digt2_R_AIN2 = 1;

        float norm_R = Ain1_R.read();
        float perc_R = norm_R * 100;
        float volt_R = norm_R * VCC;

        Pwr_R_AIN2.write(1.0);
        i++;

        printf("Volt_R[%d] = %3.2f  ||  ", i ,volt_R);
       //printf("Analog = %3.1f, %3.2f, %3.2f\n",perc_L,norm_L,volt_L);
        
        printf("Count per %dms: %d\n", BLINKING_RATE_MS1,  counter.read());

        thread_sleep_for(BLINKING_RATE_MS1);

    }
}