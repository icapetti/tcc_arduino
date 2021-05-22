# tcc_arduino
A BPM280 pressure sensor reads and an Arduino MKR board sends this data to another Arduino MKR board via LoRa connection. 
This MKR acts as a central and sends this data via serial connection to an ESP board. 
ESP sends data via wi-fi connection to a database hosted on a server. 
