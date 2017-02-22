#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>



// Getopt (#include <unistd.h> from the POSIX C Library), which can solve simple argument parsing tasks. If you're a bit familiar with bash, the getopt built-in of bash is based on Getopt from the GNU libc.

// Argp (#include <argp.h> from the GNU C Library), which can solve more complex tasks and takes care of stuff like, for example:
    // -?, --help for help message, including email address
    // -V, --version for version information
    // --usage for usage message
// Doing it yourself, which I don't recommend for programs that would be given to somebody else, as there is too much that could go wrong or lower quality. The popular mistake of forgetting about '--' to stop option parsing is just one example.

//printf("Gray = R*0.299 + G*0.587 + B*0.114 \n");
enum {RV=299, GV=587, BV=114};

int main(int argc, char* argv[])
{
  unsigned int i = 0;
  unsigned int tmp = 0;
  unsigned int gray = 0;
  unsigned int tmpgray = 0;
  unsigned int tmprgb = 0;
  unsigned int r = 0;
  unsigned int g = 0;
  unsigned int b = 0;
  
  unsigned int tc = (unsigned int)time(NULL);
  //unsigned int cc = (unsigned int)clock_gettime( CLOCK_REALTIME, NULL);
  //printf("tc %u : cc %u\n", tc, cc);

  srandom(tc);
  
  if(argc > 1)
  {
    gray = atoi(argv[1])%256;
  }

  i = 0;

  printf("Gray = R*0.299 + G*0.587 + B*0.114 \n");
  printf("gray = %u\n", gray);
  
  if(gray > 0)
  {
    while(i < 10)
    {
      r = random()%256;
      g = random()%256;
      b = random()%256;
            
      tmprgb = r*RV + g*GV + b*BV;
      printf("%d: r %4u, g %4u, b %4u, tmprgb %u \n", i, r,g,b, tmprgb);
      tmpgray = gray*1000;
      if(tmprgb != tmpgray)
      {
        r = r *tmpgray/tmprgb;
        g = g *tmpgray/tmprgb;
        b = b *tmpgray/tmprgb;

        r = r&0xff; //  max 255
        g = g&0xff; //  max 255
        b = b&0xff; //  max 255

        tmpgray = (gray*1000) - (r*RV + g*GV + b*BV);

        tmp = tmpgray/GV;
        if((tmp > 0) && (g+tmp<=255))
        { 
          tmpgray -= tmp*GV;
          g += tmp;
        }

        tmp = tmpgray/RV;
        if((tmp > 0) && (r+tmp<=255))
        { 
          tmpgray -= tmp*RV;
          r += tmp;
        }

        tmp = tmpgray/BV;
        if((tmp > 0) && (b+tmp<=255))
        { 
          tmpgray -= tmp*BV;
          b += tmp;
        }
      }

      printf("%d: r %4u, g %4u, b %4u, gray %4u\n", i, r,g,b, r*RV + g*GV + b*BV);
      ++i;
    }
  }
  else
  { printf(" a.out X.  X=1~255\n"); }

  

  return 0;
}


