On the 15th of December 2014 students of the study association e.t.s.v. Thor of the University of Technology Eindhoven held their second attempt at the World Record Largest game of Tetris. This is the code used in the controller nodes and the desktop applications.

First run:
https://www.youtube.com/watch?v=KjzhClK_t5Q

TU/e reporters:
https://www.youtube.com/watch?v=qlx7rzFrnhI

Studio 040 report:
https://www.youtube.com/watch?v=3iu0smiywXw

The project consists of two parts. The first being the embedded code for the CANbus nodes, these in turn also have two kinds. One being the entrynodes which have a USB to UART interface. These act as the USB to CAN bridges, their only duty is to litterally bridge the gap between USB and the CAN network. The second type being the LEDnodes, these nodes are hooked up to the RGB LED's.

The second part of the project are the C++ applications which run on a Windows machine. The Tetris game ofcourse must run in the field and allows the user to control the field. The Tetris game communicates with the Fieldcontroller, the Fieldcontroller will receive the current game status from the game and project it onto the big LED field. It will also show networkstatus updates.

The embedded code was writen and compiled against CMSIS using the LPCxpresso IDE, the Windows applications were written and compiled using Embarcadero C++ Builder, extensive use of VCL objects limit portability.

The code might be messy and there is no streamlined way of getting the projects to run. Keep in mind that this was made for a one of a kind student project and was never intended for public release. I am releasing this code so it might benefits others in their own projects.

If you are interested in using the code in your own projects but have a few questions then feel free to contact me. Please do not contact me if you just want to play tetris and can't get it to run or don't know where to start.
