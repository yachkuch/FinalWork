#ifndef __PROTOCOL_H_4B0R92JY44T1__
#define __PROTOCOL_H_4B0R92JY44T1__

#include <cstdint>
#include <string>
#include <iostream>

#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/mpl.hpp>

#include <boost/type_index.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

enum e_MessageType
{
    e_MessageType_commnication, //<  Новый пользователь
    e_MessageType_message,      //<  Сообщение о взаимодействии с автомобилем
};

enum e_DataType
{
    e_DataNone,
    e_DataType_AboutCars,
    e_DataType_GetCars,
};

struct HeadMessage
{
    int32_t typeMes;
    int32_t sizeMes;
};

struct CarStateMes
{
    int32_t dataType;
    int32_t id;
    std::string brand;
    int32_t distance;
    int32_t fuel;
    std::string state;
    std::string name;
    std::string time;

    std::string toString() const
    {
        return std::to_string(dataType) + " " + 
        std::to_string(id) + " " + brand + " " + std::to_string(distance) + " " + 
        std::to_string(fuel) + " " + state + " " + name + " " + time;
    }
};
BOOST_FUSION_ADAPT_STRUCT(CarStateMes, dataType, id, name,distance,fuel,state,name,time);

template <typename Sequence>
struct Struct_member_printer
{
    Struct_member_printer(const Sequence& seq):seq_(seq){}
    const Sequence& seq_;
    template <typename Index>
    void operator() (Index) const
    {

        std::string member_type = boost::typeindex::type_id<typename fusion::result_of::value_at<Sequence,Index>::type >().pretty_name() ;
        std::string member_name = fusion::extension::struct_member_name<Sequence,Index::value>::call();

        std::cout << member_type << " " << member_name << "; ";
    }
};

template<typename Sequence>
void print_struct(Sequence const& v)
{
    typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Sequence>::value > Indices; 
    std::cout << "{ ";
    fusion::for_each(Indices(), Struct_member_printer<Sequence>(v));
    std::cout << "}\n";
}

#endif
