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
  unsigned int rgbmax = 0;
  
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

        //printf("tmpgray 01: %u : %u, %u, %u\n", tmpgray, r, g, b);

        tmpgray = (gray*1000) - (r*RV + g*GV + b*BV);

        //printf("tmpgray 02: %u : %u, %u, %u\n", tmpgray, r, g, b);

        if(r > g)
        { rgbmax = r; }
        else
        { rgbmax = g; }

        if(rgbmax > b)
        {}
        else
        { rgbmax = b; }

// increases equally 
        tmp = tmpgray/1000;
        if(rgbmax+tmp > 255)
        { tmp = 255 - rgbmax; }
        r += tmp;
        g += tmp;
        b += tmp;
        tmpgray = tmpgray - (tmp*1000);

        tmp = tmpgray/GV;

/////// tmp +g > 255 -> g = 255d
        if((tmp > 0))
        { 
          if(g + tmp > 255)
          { tmp = 255 - g;  }

          tmpgray -= tmp*GV;
          g += tmp;
        }
        //printf("tmpgray 03: %u : %u, %u, %u\n", tmpgray, r, g, b);
        tmp = tmpgray/RV;
        if((tmp > 0))
        { 
          if(r + tmp > 255)
          { tmp = 255 - r;  }
          tmpgray -= tmp*RV;
          r += tmp;
        }
        //printf("tmpgray 04: %u : %u, %u, %u\n", tmpgray, r, g, b);
        tmp = tmpgray/BV;
        if((tmp > 0))
        { 
          if(b + tmp > 255)
          { tmp = 255 - b;  }
          tmpgray -= tmp*BV;
          b += tmp;
        }
      }
        //printf("tmpgray 05: %u : %u, %u, %u\n", tmpgray, r, g, b);
      printf("%d: r %4u, g %4u, b %4u, gray %4u : end\n", i, r,g,b, r*RV + g*GV + b*BV);
      ++i;
    }
  }
  else
  { printf(" a.out X.  X=1~255\n"); }

  

  return 0;
}


