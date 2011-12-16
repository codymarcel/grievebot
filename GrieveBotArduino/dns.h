// Just a utility function to nicely format an IP address.
char* ip_to_str(IPAddress ipAddr)
{

  static char buf[16];
  sprintf(buf, "%d.%d.%d.%d\n\0", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
  return buf;
}

