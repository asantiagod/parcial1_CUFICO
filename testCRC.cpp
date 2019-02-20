
#include<iostream>
#include"ucrc_t.h"
#include<cstdint>

using namespace std;

const char msg[] = "abcdefghijklmnopqrstuvwxyz";
const char numb[]= "123456789";
const char numb2[]="012345678";

int main()
{
    uCRC_t ucrc;
    uint64_t crc;
    crc = ucrc.get_crc_init();
    crc = ucrc.get_raw_crc(msg,sizeof(msg), crc);
    crc = ucrc.get_raw_crc(numb,sizeof(msg), crc);
    crc = ucrc.get_final_crc(crc);
    cout<<"CRC: "<<crc<<endl;
}
