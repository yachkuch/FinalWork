#ifndef __PROTOCOL_H_4B0R92JY44T1__
#define __PROTOCOL_H_4B0R92JY44T1__

#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/mpl.hpp>

#include <boost/type_index.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

template <typename Sequence>
struct Struct_member_printer
{
    Struct_member_printer(const Sequence& seq,std::vector<std::pair<std::string,std::string>> &names):seq_(seq),names(names){}
    const Sequence& seq_;
    std::vector<std::pair<std::string,std::string>> &names;
    template <typename Index>
    void operator() (Index) const
    {

        std::string member_type = boost::typeindex::type_id<typename fusion::result_of::value_at<Sequence,Index>::type >().pretty_name() ;
        std::string member_name = fusion::extension::struct_member_name<Sequence,Index::value>::call();
        names.push_back({member_name,member_type});
       // std::cout << member_type /*<< " " << member_name*/   << "; ";
    }
};
/**
 * @brief print_struct первое начение поля паре это имя поля второе значение типа поля
*/
template<typename Sequence>
std::vector<std::pair<std::string,std::string>>  print_struct(Sequence const& v)
{
    std::vector<std::pair<std::string,std::string>> names;
    typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Sequence>::value > Indices; 
    //std::cout << "{ ";
    fusion::for_each(Indices(), Struct_member_printer<Sequence>(v,names));
    //std::cout << "}\n";
    return names;
}

enum e_MessageType
{
    e_MessageType_commnication, //<  Основное сообщение от пользователя 
    e_MessageType_message,      //<  Сообщение о взаимодействии с автомобилем
    e_GetFullData,
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
    std::string brand{"-"};
    int32_t distance;
    int32_t fuel;
    std::string state{"-"};
    std::string name{"-"};
    std::string time{"-"};

    std::string toString() const
    {
        auto a = std::to_string(dataType);
        auto b = std::to_string(id);
        auto c = std::to_string(distance);
        auto d = std::to_string(fuel);
        auto clean = [](std::string val)
        {
            return val.erase(val.size()-1);
        };
        auto res =  a + " " + b
         + " " + brand + " " + c + " " + d
         + " " + state + " " + name + " " + time;
         return res;
        
    }

    std::vector<std::string> toVector() const
    {
        using namespace std;
        vector<string> res;
        res.push_back(std::to_string(dataType));
        res.push_back(std::to_string(id));
        res.push_back(brand);
        res.push_back(std::to_string(distance));
        res.push_back(std::to_string(fuel));
        res.push_back(state);
        res.push_back(name);
        res.push_back(time);
        return res;
    }

    void fromString(std::vector<std::string> data)
    {
        try
        {
        dataType = std::stoi(data[0]);
        }
        catch(...){return;}
        try
        {
        id = std::stoi(data[1]);
        }
        catch(...){return;}
        try
        {
        brand = data[2];
        }
        catch(...){return;}
        try
        {
        distance = std::stoi(data[3]);
        }
        catch(...){return;}
        try
        {
        fuel = std::stoi(data[4]);
        }
        catch(...){return;}
        try
        {
        state = data[5];
        }
        catch(...){return;}
        try
        {
        name = data[6];
        }
        catch(...){return;}
        try
        {
        time = data[7];
        }
        catch(...){return;}
    }
    /**
     * первы параметр это имя поля в структуре второй параметр это значение поля
    */
    void writeByName(std::vector<std::pair<std::string,std::string>> data)
    {
        auto names = print_struct(*this); 
        for(const auto &elementData : data)
        {
            if(elementData.first == "dataType")
            {
                dataType = std::stoi(elementData.second);
            }
            else if(elementData.first == "id")
            {
                id = std::stoi(elementData.second);
            }
            else if(elementData.first == "brand")
            {
                brand = elementData.second;
            }
            else if(elementData.first == "distance")
            {
                distance = std::stoi(elementData.second);
            }
            else if(elementData.first == "fuel")
            {
                fuel = std::stoi(elementData.second);
            }
            else if(elementData.first == "state")
            {
                state = elementData.second;
            }
            else if(elementData.first == "name")
            {
                name = elementData.second;
            }
            else if(elementData.first == "time")
            {
                time = elementData.second;
            }
        }
    }
};
BOOST_FUSION_ADAPT_STRUCT(CarStateMes, dataType, id, name,distance,fuel,state,name,time);



#endif
