
#include "serialComm.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h> 

#include <iostream>
#include <iomanip>

using namespace std;

serialComm::serialComm( const char * port)
{

  serial_line = port;

}


void serialComm::identify(std::ostream& os) const
{
  os << " port  " << serial_line <<  " via serial line" << endl;
}



int serialComm::Connect()
{

  if (connected) return 0;

  if ( (fd = open(serial_line.c_str(), O_RDWR) ) < 0 )
    {
      cout << "error connecting to serial port" << endl;
      status =-1;
      return status;
    }

  status = 0;
  connected = 1;

  return status;

}  

int serialComm::Disconnect()
{
  close(fd);
  connected = 0;

}


// -------------------------------------------------------------------
int serialComm::readChar( char *c, const int timeout) // in ms
{

  int i;
  fd_set rfds;
  struct timeval tv;
  int retval;
  
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);

  if (timeout) 
    {
      //  cout << __FILE__ << "  " <<  __LINE__ << " timeout is " << timeout << endl;
      int sec = timeout / 1000;
      int us = (timeout%1000) * 1000;
      tv.tv_sec = sec;
      tv.tv_usec = us;
      
      retval = select(fd+1, &rfds, NULL, NULL, &tv);
    }
  else
    {
      retval = select(fd+1, &rfds, NULL, NULL, NULL);
    }

  if (retval)
    {  
      i = read(fd, c, 1);
      if ( i < 0)
	{
	  cout << __LINE__ << "  " << __FILE__ <<endl;
	  return -1;
	}
      return 0;
    }
  else
    {
      return -1;
    }
  
}

 
// -------------------------------------------------------------------

int  serialComm::flush()
{
  
  char c;
  int i = 0;
  while ( readChar( &c, 10 ) == 0 ) i++;
  return i;
}



// -------------------------------------------------------------------

int serialComm::print ( const char * string, const int timeout)
{
  const int  on=1, off=0;
  char cr= CHAR_CR;
  char lf= CHAR_LF;

  int sent = 0;
  int i;

  sent += write (fd, string,strlen(string) );
  //  sent += write (fd, &cr, 1 );

  return sent;
}

// -------------------------------------------------------------------

int serialComm::print ( const int value)
{
  const int  on=1, off=0;
  char cr= value;

  int sent = 0;

  sent += write (fd, &cr, 1 );

  return sent;
}

// -------------------------------------------------------------------



int serialComm::readLine ( char * string, const int length)
{
  int i, status;

  for ( i = 0; i< length; i++)
    {
      status = readChar( &string[i]);

      if (status < 0) 
	{
	  string[i] = 0;
	  return 0;
	}
      if ( string[i] == CHAR_LF || string[i] == CHAR_CR || string[i] ==0)
	{
	  i--;
	}
    }

  return 0;
}





int serialComm::readn (int fd, char *ptr, const unsigned int nbytes)
{
  int nleft, nread;
  nleft = nbytes;
  while ( nleft>0 )
    {
      nread = read (fd, ptr, nleft);
      if ( nread < 0 ) 
	return nread;
      else if (nread == 0) 
	break;
      nleft -= nread;
      ptr += nread;
    }
  return (nbytes-nleft);
}


int serialComm::writen (int fd, const char *ptr, const unsigned int nbytes)
{
  int nleft, nwritten;
  nleft = nbytes;
  while ( nleft>0 )
    {
      nwritten = write (fd, ptr, nleft);
      if ( nwritten < 0 ) 
	return nwritten;

      nleft -= nwritten;
      ptr += nwritten;
    }
  return (nbytes-nleft);
}

