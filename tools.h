#include <ezTime.h>

#ifndef Included_Tools

#define Included_Tools
char* string2char(String str){
  int len = str.length();
  char* opChar = new char[len + 1];
  memset(opChar, 0, len + 1);

  for (int i = 0; i < len; i++) {
    opChar[i] = str.charAt(i);
  }

  return opChar;
} 

void setClock() {
  Serial.print("Waiting for NTP time sync: ");
  configTime(3600, 3600, "pool.ntp.org", "time.nist.gov");

  time_t now = time(nullptr);
  
  while (now < 8 * 3600 * 2) {
    delay(20);
    now = time(nullptr);
  }

  setTime(now);

  Timezone myTZ;
  myTZ.setLocation("Europe/London");
  Serial.print("London: " + myTZ.dateTime());
  Serial.println();
}
#endif
