
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#include "serialComm.h"

using namespace std;

int main( int argc, char *argv[])
{

  if ( argc < 2)
    {
      cout << " Usage " << argv[0] << " <serialport>" << endl;
      cout << "   e.g " << argv[0] << " /dev/ttyUSB0" << endl;
      return 1;
    }

  char axis ='X';

  char c;
  while ((c = getopt(argc, argv, "xyzXYZ")) != EOF)
    {
      switch (c) 
	{
	case 'x':
	case 'X':
	  axis='X';
	  ;
	  break;

	case 'y':
	case 'Y':
	  axis='Y';
	  ;
	  break;

	case 'z':
	case 'Z':
	  axis='Z';
	  ;
	  break;

	}
    }


  Communication *tn = new serialComm ( argv[optind]);

  tn->Connect();
  tn->print(axis);
  char string[128];
  int i;
  int status;

  for ( i = 0; i < 12; i++)
    {
      if ( ( status = tn->readChar(&string[i], 10) < 0) )
	{
	  //	  cout << "timeout at char " << i << endl;
	  continue;
	}
    }
  //  if (status) return 1;

  string[i] = 0;
  int val = atoi (string);
  cout << val << endl;
  return 0;

}

