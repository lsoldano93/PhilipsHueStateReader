---------------------------
Phillips Hue State Reader:
---------------------------

This is a Phillips Hue 'Hello World' project to gather and print the status of a Hue system to terminal output.


To compile this application on Mac OSX:

	1. Install curlpp - 'brew install curlpp'
	2. Enter command - 'curlpp-config --cflags --libs'
	3. Ensure that the Eclipse project settings hold the proper paths to your include and lib folders, which contain curl and curlpp


Note:

When I ran this application I was only able to test it with a Phillips Hue Bridge Simulator, so a real implementation remains to be tested. This implementation also leaves out the matter of creating a user with the Link-Button as I did not have a physical device to test this with.


To test it like I did:

	1. Install hue-simulator - https://www.npmjs.com/package/hue-simulator
	2. Run hue-simulator on port 80 - 'sudo /path/to/hue-simulator/bin/hue-simulator'
	3. Check that simulator is running - Navigate to localhost on your web browser
