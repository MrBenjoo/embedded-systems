###### Task1501f

## Description
In this mini-project the system handles different things at the same time with the help of an interrupt in the Timer Counter.
The program generates a sinusoidal signal which is to the D/A output. The frequency of the sinusoidal is a result of the frequency of the time interval used.
In parallel to the genereated sinusoidal signal, the built-in LED on the Due card is flashing.

- The LED is flashing with a frequency of 0.67 Hz (i.e. a cycle of toggle -on/off- takes 1.5s). 
- To prevent the program from locking up, there is a watchdog that is handled at regular intervals so that the processor does not reset (To prevent the program from locking up).
- Writes a value on the D/A output using an interrupt with a much higher frequency than the LED cycle.

## Lab Setup
###### Equipment:
- Arduino Due
- Oscilloscope


