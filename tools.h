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

#endif
