#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Adafruit_NeoPixel.h>

#define PINLED        25
#define NUMPIXELS  18   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

Adafruit_NeoPixel pixels(NUMPIXELS, PINLED, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

// Set these to your desired credentials.
const char *ssid = "ESP32";
const char *password = "11111111";

WiFiServer server(80);
String key = "000"; // Variable to store the value sent by the computer

void setup() {
  pinMode(PINLED, OUTPUT);
  digitalWrite(PINLED, LOW);
  // Turn off all pixels
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
        for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /?key=000")) {
         pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("0");               
        }
        else if (currentLine.endsWith("GET /?key=001")) {
          pixels.setPixelColor(1, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("1");             
        }
        else if (currentLine.endsWith("GET /?key=002")) {
          pixels.setPixelColor(2, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("2");             
        }
        else if (currentLine.endsWith("GET /?key=003")) {
          pixels.setPixelColor(3, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("3");             
        }
        else if (currentLine.endsWith("GET /?key=004")) {
          pixels.setPixelColor(4, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("4");             
        }
        else if (currentLine.endsWith("GET /?key=005")) {
          pixels.setPixelColor(5, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("5");             
        }
        else if (currentLine.endsWith("GET /?key=006")) {
          pixels.setPixelColor(6, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("6");             
        }
        else if (currentLine.endsWith("GET /?key=007")) {
          pixels.setPixelColor(7, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println("7");             
        }

    }
    // close the connection:
    //client.stop();
    //Serial.println("Client Disconnected.");
  }
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

  // Extract the key from the request
  int keyStart = request.indexOf("=") + 1;
  int keyEnd = request.indexOf(" ", keyStart);
  key = request.substring(keyStart, keyEnd);

  Serial.print("Received: ");
  Serial.println(key); // Print the received value in the Serial Monitor

  // Turn off all pixels
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }

  if (key.length() == 3 && key >= "000" && key <= "018") {
    int pixelIndex = key.toInt();
    pixels.setPixelColor(pixelIndex, pixels.Color(186, 255, 255));
    pixels.show();
    delay(DELAYVAL); // Add a delay after setting the pixel color
    Serial.println(key);
  }

  // Send the HTTP response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println();
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("<style>");
client.println("body {");
client.println("  display: flex;");
client.println("  justify-content: center;");
client.println("  align-items: center;");
client.println("  height: 100vh;");
client.println("  font-family: Arial, sans-serif;");
client.println("  background-color: #f2f2f2;");
client.println("}");

client.println("h1 {");
client.println("  color: #333333;");
client.println("}");

client.println("p {");
client.println("  color: #666666;");
client.println("}");

client.println("form {");
client.println("  margin-top: 20px;");
client.println("}");

client.println("input[type=\"text\"] {");
client.println("  padding: 5px;");
client.println("  font-size: 14px;");
client.println("}");

client.println("input[type=\"submit\"] {");
client.println("  padding: 8px 15px;");
client.println("  font-size: 16px;");
client.println("  background-color: #4CAF50;");
client.println("  color: #ffffff;");
client.println("  border: none;");
client.println("}");

client.println("@media (max-width: 600px) {");
client.println("  body {");
client.println("    flex-direction: column;");
client.println("    padding: 20px;");
client.println("  }");
client.println("}");

client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<h1>ESP32 Web Server</h1>");
client.println("<p>Enter a key value (000-018):</p>");
client.println("<form>");
client.println("<input type=\"text\" name=\"key\">");
client.println("<input type=\"submit\" value=\"Submit\">");
client.println("</form>");
client.println("</body>");
client.println("</html>");

  delay(1);
  client.stop();
}
