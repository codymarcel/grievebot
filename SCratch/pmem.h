#define PROGMEM_BUFFER_SIZE 30
prog_char remoteServer[] PROGMEM = "grievebot.heroku.com";
prog_char xml_message[] PROGMEM = "";
prog_char last_message[] PROGMEM = "";
prog_char last_post_url[] PROGMEM = "";
prog_char author[] PROGMEM = "";


// Then set up a table to refer to your strings.

PROGMEM const char *string_table[] = 	   // change "string_table" name to suit
{   
  remoteServer,
  xml_message,
  last_message,
  last_post_url,
  author
};

char buffer[PROGMEM_BUFFER_SIZE];    // make sure this is large enough for the largest string it must hold

void zeroBuffer(char * message, int len){
  for (int i=0; i<len; i++) {
    message[i] = '\0';
  }
}

String get_prog_mem(int index){
  zeroBuffer(buffer, PROGMEM_BUFFER_SIZE);  
  String s =  String(strcpy_P(buffer, (char*)pgm_read_word(&(string_table[index]))));
}

char * stringToCharArray(String s){
  char arr [s.length()];
  s.toCharArray(arr, s.length());
  return arr;
}

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    int i;
    for (i = 0; i < sizeof(value); i++)
	  *p++ = EEPROM.read(ee++);
    return i;
}



