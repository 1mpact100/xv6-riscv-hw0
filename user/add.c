#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int BUF_SIZE = 50;
  char buf[BUF_SIZE]; 
  char c;
  int i, cc;

  for (i = 0; i < BUF_SIZE + 1; ++i)
  {
    cc = read(0, &c, 1);
    if (cc == 0)
      break;

    if (cc < 0)
    {
      fprintf(2, "Read error\n");
      exit(1);
    }

    if (c == '\n')
      break;

    if (i == BUF_SIZE)
    {
      fprintf(2, "End of buffer\n");
      exit(1);
    }

    buf[i] = c;
  }
  buf[i] = '\0';

  char first[i + 1];
  char second[i + 1];
  int sign_first = 1;
  int sign_second = 1;

  i = 0;
  int pos = 0;

  if (buf[i] == '\0')
  {
    fprintf(2, "Empty input\n");
    exit(1);
  }

  if (buf[i] == '-')
  {
    sign_first = -1;
    i++;
  }

  if (buf[i] == ' ')
  {
    fprintf(2, "Incorrect input\n");
    exit(1);
  }

  while (buf[i] != ' ')
  {
    if (buf[i] == '\0')
    {
      fprintf(2, "No space here\n");
      exit(1);
    }

    c = buf[i];

    if (c < '0' || c > '9')
    {
      fprintf(2, "Incorrect input\n");
      exit(1);
    }

    first[pos] = c;
    i++;
    pos++;
  }
  first[pos] = '\0';
  i++;

  if (buf[i] == '-')
  {
    sign_second = -1;
    i++;
  }

  if (buf[i] == '\0')
  {
    fprintf(2, "Only one number\n");
    exit(1);
  }

  pos = 0;
  while (buf[i] != '\0')
  {
    c = buf[i];

    if (c < '0' || c > '9')
    {
      fprintf(2, "Incorrect input\n");
      exit(1);
    }

    second[pos] = c;
    pos++;
    i++;
  }
  second[pos] = '\0';

  int a = atoi(first);
  int b = atoi(second);

  a *= sign_first;
  b *= sign_second;

  int r = a + b; 

  i = 0;
  char input_str[BUF_SIZE +2];
  input_str[0] = '|';
  while (buf[i] != '\0')
  {
    input_str[i + 1] = buf[i];
    i++;
  }
  input_str[i + 1] = '|';
  input_str[i + 2] = '\0';
  
  printf("%d\n", r);
  printf("%s\n", input_str);
  exit(0);
}
