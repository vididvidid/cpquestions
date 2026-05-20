int printf(const char*,...);
int usleep(unsigned);
int a,b,c,d;
int main(int C,char**V){
char*v=V[1];if(!v)return 0;
 for(;v[a];a++);for(;a--;)
  for(b=0;b<a;b++){if(v[b]
   >v[b+1])v[b]^=v[b+1],
    v[b+1]^=v[b],v[b]^=
     v[b+1];printf(
      "\033[2J"
       "\033"
        "[H"
         );
       for(c=0;
      v[c];c++,
     printf("\n"
    ))for(d=v[c]-
   32;d>0&&d--;)
  printf("[]");
 usleep(99999);}}
