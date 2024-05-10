Virker udelukkende i UBUNTO
BOOST skal være installeret
- sudo apt-get install libboost-all-dev

Selve ur_rtde kan instaleres med:
- sudo add-apt-repository ppa:sdurobotics/ur-rtde
- sudo apt-get update
- sudo apt install librtde librtde-dev

Tiføj bruger til dialout group så man kan sende signaler til USB porte
sudo usermod -a -G dialout <username>

Sqlite skal sættes op:
- sudo apt install libqt5sql5-sqlite

Hvis en virtuel maskine bruges skal netværkskorttet sætte til kun at være lan kortet

Der skal laves en manuel ipv 4 address som er 192.168.1.100 og 255.255.255.0



