#include <cstdint>
#ifndef __PROTOCOL_H_4B0R92JY44T1__
#define __PROTOCOL_H_4B0R92JY44T1__

enum e_MessageType
{
    e_MessageType_commnication, //<  Новый пользователь
    e_MessageType_message,      //<  Сообщение о взаимодействии с автомобилем
};

struct HeadMessage
{
    int32_t typeMes;
    int32_t sizeMes;
};


#endif
