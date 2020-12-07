/* Convert a hexadecimal character to its value */
uint8_t charToVal(char c) {
  return c >= '0' && c <= '9' ? c - '0' : (c >= 'a' && c <= 'f' ? c - 'a' + 10: (c >= 'A' && c <= 'F' ? c - 'A' + 10: 0));  
}

/* Convert a number between 0-15 to a hexdecimal character */
char valToChar(uint8_t v) {
  return v >= 0 && v <= 9 ? '0' + v : (v >= 10 && v <= 15 ? 'A' + v - 10: 'X');  
}

/* Convert a string of hexdecimal digits into the equivalent bytes */
void hexStringToBytes(char *hexstr, int len, unsigned char *out) {
  while (len >= 2) {
    uint8_t outChar = charToVal(*hexstr) << 4 | charToVal(*(hexstr + 1));
    *out++ = outChar;
    hexstr += 2;
    len -= 2;
  }
  return; 
}

void serialPrintHexChar(char c) {
   if (c < 16) Serial.print("0");
   Serial.print(c, HEX);
}

void serialPrintAsHex(char *buf, int len, char *prompt) {
  Serial.print(prompt ? prompt : "Hex: ");
  for (int i = 0; i < len; i++) 
    serialPrintHexChar(buf[i]);
  Serial.println();
  for (int i = 0; i < len; i++) 
    if (isprint(buf[i]))
      Serial.print(buf[i]);
    else
      Serial.print('.');
  Serial.println();
}

void bytesToHexString(unsigned char *in, int len, char *out) {
  for (int i = 0; i < len; i++) {
    *out = valToChar(*((uint8_t *) in) >> 4);
    out++;
    *out = valToChar(*((uint8_t *) in) & 0xf);
    out++;
    in++;      
  }
}


/* Convert a short (in system endian order) in to a hexadecimal string (big endian) */
void shortToHex(unsigned short num, char *out) {
  unsigned short msb = htons((unsigned short) num);
  out[0] = valToChar(*((uint8_t *) &msb) >> 4);
  out[1] = valToChar(*((uint8_t *) &msb) & 0xf);
  out[2] = valToChar(*((uint8_t *) &msb + 1) >> 4);
  out[3] = valToChar(*((uint8_t *) &msb + 1) & 0xf);
}
