# AngryBlerch
An IoT inactivity tracker in Blerch-shape, based on the Arduino platform. The blerch is a design by [Mathew Inman of The Oatmeal](https://theoatmeal.com/comics/running). 




## Notes

https://github.com/madewhatnow/AngryBlerch/blob/main/code/ESP32_Strava_API_HTTPS_example.ino contains a test implementation that runs on an ESP32 board and uses HTTPS to access the Strava API via a GET request. To use the example, update the SSID & password to connect to a local WiFi, create a web app with Strava (https://developers.strava.com/docs/getting-started/#account) and insert your 'athlete ID' as well the the 'access token' into the code. 

The test script should return the number of recent activities as an int value. If you uncomment the 'print(payload)' line, the complete returned data should be printed to the console, allowing easy identification of other interesting metrics. Expect these data fields: https://developers.strava.com/playground/#/Athletes/getStats . Parsing is enabled using the excellent Json library. 

The time code is primarily there to test network connectivity. 

Advanced API requests (including accessing all activities) will require scopes with higher privileges. 

While the first example code is straightforward, there is an issue: as of September 2021, the access token expires after 6 hours. It can obviously be updated via your strava app page - but more conveniently the token can be refreshed using the aptly named refresh token in a separate transaction directly by the ESP32. In the more complex implementation found here, the refresh token is stored in the non-volatile memory of the ESP32 using Preferences. In case of power loss or a reset, AngryBlerch will therefor be able to restore both the access and refresh tokens as needed, and will check or update them while running.

Strava limits access via the API to 100 requests every 15 minutes, or 1000 daily - which comes out to an update around every 90 seconds. It is probably sensible to be a bit more conservative than that. 



