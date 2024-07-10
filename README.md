# Digital_Clock_Project

Write program: The Digital Clock

SRS 1: Clock core 72MHz from clock source crystal 8MHz
SRS 2: Setting for LPUART1. Pin PTC6, Pin PTC7
  SRS 2-1: Baud rate: 38400, 8-bits data, even parity, 1-bit stop.
  SRS 2-2: UART clock is SPLL Div2
SRS 3: Setting for SPI using Pin E0, Pin E1, Pin E2, Pin E6
SRS 4: After power on, display the time: 18-00-00 (date: 01.01.1991), the LED Green status is OFF
SRS 5: Setting date, time, alarm by UART1 serial communication.
SRS 6: Select mode display via the button

  Press Button 1
  SRS 6-1: Auto display mode: Repeat display the time (5s) -> Display the date (3s)
  SRS 6-2: Display the date
  SRS 6-3: Display the time
  SRS 6-4: Display the alarm
  Press Button 2
  Decrease bright of LED 7 SEG which 5 level from maximum to off the LED 7SEG
SRS 7: When alarm occurred, the LED Green blink with period 0.5 (s) in alarm time 10 (s). In alarm time, if pressed any button, the LED Green is OFF immediately.
