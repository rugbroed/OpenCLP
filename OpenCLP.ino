/*
  OpenCLP [0.1b] - A CommandLineParser for Arduino (https://github.com/rugbroed/OpenCLP)
  
  This code will accept chars from Serial by polling every <pollingInterval> millisecond, and build a buffer <s> 
  with the chars. It will strip the incoming chars of \r and use \n as split point between commands.
  
  author: Kasper Hansen - September 2012 (https://github.com/rugbroed)
*/

const long pollingInterval = 1000;

String s = "";

// Buffers chars in <s> for <pollingInterval> milliseconds. 
String readString() {
  String readString = "";

  long startTime = millis();
  long stopTime = startTime + pollingInterval;

  long now = millis();
  
  boolean wasNewLine = false;

  while (now < stopTime) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      
      if (c != '\r') {
        readString += c;
      }
    }
    
    now = millis();
  }

  return readString;
}

// Substrings and removes until \n in <s> and returns the string
String popCommand(String s) {
  if (s.length() == 0) return "";
  
  String command = "";

  int pos = s.indexOf("\n");

  if (s.length() > 0) {
    if (pos > 0) {
      command = s.substring(0, pos);
    }
    else {
      command = s;
    }
  }

  return command;
}

void setup() {
  Serial.begin(19200);
}

void loop() {
  String newLine = readString();
  
  if (newLine.length() > 0) {
    s.concat(newLine);
  }
  
  /*
  Serial.print("S: ");
  Serial.println(s);
  */

  String command = "";
  
  do {
    command = popCommand(s);
    
    if (command.length() > 0) {
      s = s.substring(command.length() + 1);
      s.trim();
      command.trim();
      if (command.length() > 0) {
        /*
        Serial.print("Command: ");
        Serial.print(command);
        Serial.print(" (L:");
        Serial.print(command.length());
        Serial.println(")");
        */
        
        //IMPLEMENT: Do something with your <command>
      }
    }
    
  } while (command.length() > 0);
}
