# ECE362-Project
Title : Snake Arcade Game 

IDE :
- ECLIPSE

Project Description :
-For this project, our team decided to built the retro arcade game called
Snake. An STM32 used peripherals such as ADC, DAC, DMA, SPI, and GPIO to
interact with the LED matrix, joystick, speaker, and the amplifier. The 
peripheral ADC was used to interact with the joystick. ADC retrieved values
from the outputs of the joystick which helped determine which direction
that the snake will travel. The peripheral DMA and DAC where used with the
speaker. It helped output different frequencies through the speaker to make
the music for the Tetris theme song. The peripheral SPI was used to control
the lcd screen which displayed the players score. Finally, GPIO was used to
control the LED matrix which was used to display the snake game. 

Materials :
- LED MATRIX (64 x 32) - https://www.adafruit.com/product/2277
- Mini Analog Joystick (10K Potentiometers) - https://www.adafruit.com/product/3102
- 16mm Illuminated Pushbutton (Red Latching On/Off Switch) - https://www.adafruit.com/product/1442
- Speaker - 3" Diameter (4 Ohm 3 Watt) - https://www.adafruit.com/product/1314
- STM32F0DISCOVERY - https://www.digikey.com/product-detail/en/stmicro/STM32F0DISCOVERY/497-12876-ND/3045359?utm_adgroup=Evaluation%20Boards%20-%20Embedded%20-%20MCU%2C%20DSP&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&utm_content=Evaluation%20Boards%20-%20Embedded%20-%20MCU%2C%20DSP&gclid=CjwKCAiA1L_xBRA2EiwAgcLKA-_V2DshVG3Q5Xx4i8hMrJA7IGJk2NtsuHBiux7XHcL5YETy2_aADRoCZTkQAvD_BwE
