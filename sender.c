#include <arpa/inet.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
static constexpr int P=160,K=4,N=6;
static unsigned char m(unsigned char a,unsigned char b){unsigned char r=0;while(b){if(b&1)r^=a;a=(a&128)?(unsigned char)((a<<1)^29):(unsigned char)(a<<1);b>>=1;}return r;}
static unsigned char c(int r,int col){if(r<K)return r==col;unsigned char v=1,b=1u<<(r-K);for(int i=0;i<col;i++)v=m(v,b);return v;}
int main(){int in=socket(AF_INET,SOCK_DGRAM,0),out=socket(AF_INET,SOCK_DGRAM,0);sockaddr_in a{};a.sin_family=AF_INET;a.sin_port=htons(47010);a.sin_addr.s_addr=htonl(INADDR_LOOPBACK);if(bind(in,(sockaddr*)&a,sizeof a)<0){perror("bind 47010");return 1;}sockaddr_in relay{};relay.sin_family=AF_INET;relay.sin_port=htons(47001);relay.sin_addr.s_addr=htonl(INADDR_LOOPBACK);unsigned char input[164],g[K][P],have[K]{};uint32_t current=UINT32_MAX;for(;;){if(recvfrom(in,input,sizeof input,0,nullptr,nullptr)!=164)continue;uint32_t x;memcpy(&x,input,4);uint32_t seq=ntohl(x),base=seq-seq%K;if(base!=current){memset(have,0,sizeof have);current=base;}int row=seq%K;memcpy(g[row],input+4,P);have[row]=1;unsigned char p[165];p[0]=row;uint32_t nb=htonl(base);memcpy(p+1,&nb,4);memcpy(p+5,g[row],P);sendto(out,p,sizeof p,0,(sockaddr*)&relay,sizeof relay);bool done=true;for(int i=0;i<K;i++)done&=have[i];if(!done)continue;for(int r=K;r<N;r++){memset(p+5,0,P);for(int col=0;col<K;col++)for(int b=0;b<P;b++)p[5+b]^=m(c(r,col),g[col][b]);p[0]=r;sendto(out,p,sizeof p,0,(sockaddr*)&relay,sizeof relay);}memset(have,0,sizeof have);current=UINT32_MAX;}}
