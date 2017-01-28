---------------------------
Phillips Hue State Reader:
---------------------------

This is a Phillips Hue 'Hello World' project to gather and print the status of a Hue system to terminal output in JSON format. On startup this program will print off all found lights and their states. During run-time only parameter updates to these lights will be printed. The parameters watched by this program are: id, name, light state, and brightness.


To compile this application on Mac OSX:

	1. Install rapidjson - 'brew install rapidjson'
	2. Install curlpp - 'brew install curlpp'
	3. Enter command - 'curlpp-config --cflags --libs'
	4. Ensure that the Eclipse project settings hold the proper paths to your include and lib 
	   folders, which contain curl and curlpp


Note:

When I ran this application I was only able to test it with a Phillips Hue Bridge Simulator, so a real implementation remains to be tested. This implementation also leaves out the matter of creating a user with the Link-Button as I did not have a physical device to test this with.


To test it like I did:

	1. Install hue-simulator - https://www.npmjs.com/package/hue-simulator
	2. Run hue-simulator - 'sudo /path/to/hue-simulator/bin/hue-simulator (Optional Port#)'
		i. By default hue-simulator runs on port 80, which will require sudo
		ii. If you do not wish to run on port 80, enter a value for Optional Port# and remove sudo
	3. Check that simulator is running - Navigate to localhost on your web browser
	4. Run PhillipsHueStateReader 
	5. When prompted, enter the IP address where hue-simulator is active
		i. In my case that would be 'localhost:80' or just 'localhost'
	6. Let 'er rip - if you followed the steps correctly you should see the bootup light states
	   as well as any changes made via the browser simulator