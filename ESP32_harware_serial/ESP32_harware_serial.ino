#define TXD2 17  // TX pin
#define RXD2 16  // RX pin

HardwareSerial mySerial(2); // Use UART2 (Serial2)

void setup() {
  Serial.begin(115200); // USB debug
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2 initialization
  Serial.println("Device 1 ready for two-way communication");
}

void loop() {
  // Sending data to Device 2
  mySerial.println("Hello from Device 1!");
  Serial.println("Device 1 sent: Hello from Device 1!");

  // Check for incoming data
  if (mySerial.available()) {
    String message = mySerial.readStringUntil('\n');
    Serial.println("Device 1 received: " + message);
  }

  delay(1000); // Wait 1 second before the next message
}


#define TXD2 17  // TX pin
#define RXD2 16  // RX pin

HardwareSerial mySerial(2); // Use UART2 (Serial2)

void setup() {
  Serial.begin(115200); // USB debug
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2); // UART2 initialization
  Serial.println("Device 2 ready for two-way communication");
}

void loop() {
  // Sending data to Device 1
  mySerial.println("Hello from Device 2!");
  Serial.println("Device 2 sent: Hello from Device 2!");

  // Check for incoming data
  if (mySerial.available()) {
    String message = mySerial.readStringUntil('\n');
    Serial.println("Device 2 received: " + message);
  }

  delay(1000); // Wait 1 second before the next message
}
//G.M.SABBIR AHAMED