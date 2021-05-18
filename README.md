# AngryBlerch
An Arduino-based inactivity tracker enabling visual feedback. In Blerch-shape. 


## Notes

https://github.com/madewhatnow/AngryBlerch/blob/main/code/ESP32_Strava_API_HTTPS_example.ino contains a test implementation that runs on an ESP32 board and uses HTTPS to access the Strava API. To use the example, update the SSID & password to connect to a local WiFi hotspot, create a web app with Strava (https://developers.strava.com/docs/getting-started/#account) and insert the 'athlete ID' as well the the 'access token' into the code. 

The test script should return the number of recent activities. If you uncomment the 'print(payload)' line, the complete returned data should be printed to the console. Expect these data fields: https://developers.strava.com/playground/#/Athletes/getStats

The time code is primarily there to test network connectivity. 

Advanced API requests (like accessing all activities) will require scopes with higher privileges. 


