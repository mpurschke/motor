#ifndef __SERIALCOMM_H__
#define __SERIALCOMM_H__

#include "commlib.h"

#include <string>

#define CHAR_LF 0xc
#define CHAR_CR 0xd

#define USLEEPINTERVAL 600

class serialComm : public Communication {

 public:
  serialComm ( const char * port );


  int Connect(); 
  int Disconnect(); 

  // reads one character with timeout in milliseconds. 0 means no timeout.
  int readChar( char *c, const int timeout =12000); 

  // flushes the serial line
  int flush();


  int readLine ( char * string, const int length);

  int print ( const char * string, const int timeout = 0);
  int print ( const int value);

  void identify(std::ostream& os = std::cout) const;


 protected:


  int fd;
  std::string serial_line;

  static int readn (int fd, char *ptr, const unsigned int nbytes);
  static int writen (int fd, const char *ptr, const unsigned int nbytes);

  char buffer[1024];
  int last_position;

  time_t starttime;



}; 

#endif /* __SERIALCOMM_H__ */
