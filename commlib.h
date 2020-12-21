#ifndef __COMMLIB_H__
#define __COMMLIB_H__

#define CHAR_LF 0xc
#define CHAR_CR 0xd

#define USLEEPINTERVAL 600

#include <iostream>

class Communication {

 public:
  Communication() 
    {
      status =0;
      connected = 0;
    }

  virtual ~Communication() {};

  // ----- utility functions ------

 
  virtual int Connect()=0; 
  virtual int Disconnect()=0; 

  // reads one character with timeout in milliseconds. 0 means no timeout.
  virtual int readChar( char *c, const int timeout =12000)=0; 

  // flushes the serial line
  virtual int flush()=0;


  virtual int readLine ( char * string, const int length)=0;

  virtual int print ( const char * string, const int timeout = 0)=0;
  virtual int print ( const int value)=0;

  virtual int getStatus() const { return status;};

  virtual void identify(std::ostream& os = std::cout) const = 0;


 protected:


  int connected;
  int status;


}; 

#endif /* __COMMLIB_H__ */
