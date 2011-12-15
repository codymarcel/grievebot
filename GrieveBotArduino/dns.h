// Just a utility function to nicely format an IP address.
char* ip_to_str(IPAddress ipAddr)
{

/*
   for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ipAddr[thisByte], DEC);
    Serial.print("."); 
  }
*/

  static char buf[16];
  sprintf(buf, "%d.%d.%d.%d\n\0", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
  return buf;


}

