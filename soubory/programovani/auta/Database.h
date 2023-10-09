#ifndef AUTA_DATABASE_H
#define AUTA_DATABASE_H

#include <tuple>
#include <unordered_map>
#include <string>
#include <initializer_list>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#ifdef _WIN32
#define NEW_LINE "\r\n"
#else
#define NEW_LINE '\n'
#endif

#define BINSEP 0xFF

template<std::size_t...> struct seq{};

template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};

template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};


/*template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_stringstream<Ch,Tr>& os, char s, Tuple const& t, seq<Is...>){
    using swallow = int[];
    (void)swallow{0, (void(os << (Is == 0 ? "" : &s) << std::get<Is>(t)), 0)...};
}*/
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_stringstream<Ch,Tr>& os, char s, Tuple const& t, seq<Is...>){
    using swallow1 = int[];
    swallow1{0, (void(os << (Is == 0 ? "" : &s) << std::get<Is>(t)), 0)...};
}

enum class Sort{
    ASC, DES
};

template<typename ...T>
class Database final {
public:
    constexpr Database(const std::initializer_list<std::string>& namel)
    :m_data({}),m_column(namel),m_index(0){}

    std::string dump(const std::string& c = "id", Sort way = Sort::ASC, char separator = ';') const {
        std::stringstream s;
        //std::vector<std::vector<std::string>> data;

        s << "id" << separator;
        for(auto& c : m_column)
            s << c << separator;
        s << NEW_LINE;

        for(auto&[index, tuple] : m_data) {
            s << std::to_string(index) << separator;
            print_tuple(s, separator,tuple, gen_seq<sizeof...(T)>());
            s << NEW_LINE;
        }

        //data = sort_vecvec(data, c, way);

        //for(auto& r : data){
        //    for(auto& p : r)
        //    {
        //        s << p;
        //        s << separator;
        //    }
        //    s << NEW_LINE;
        //}

        return s.str();
    }

    std::vector<std::vector<std::string>>
    sort_vecvec(const std::vector<std::vector<std::string>>& data, const std::string& col, Sort s) const{
        auto it = std::find(m_column.begin(),m_column.end(), col);
        int id = std::distance(m_column.begin(), it);
        std::cout << "[" << id << "]";

        //std::sort(data.begin(),data.end(),[&](
        //        const std::vector<std::string>& v1,
        //        const std::vector<std::string>& v2){
        //    //std::string s1 = v1[id], s2 = v2[id];
        //    return false;
        //});

        return data;
    }

    constexpr Database& operator+=(const std::tuple<T...>& row) {
        add(row);
        return *this;
    }

    constexpr void add(const std::tuple<T...>& row) {
        m_data[m_index++] = row;
    }

    [[maybe_unused]] void dump_b(const std::string& path) const {
        // ...
    }

    [[maybe_unused]] int read_b(const std::string& path) {
        // ...
        return 0;
    }

private:
    std::vector<std::string> m_column;
    std::unordered_map<size_t,std::tuple<T...>> m_data;
    size_t m_index;
};


#endif //AUTA_DATABASE_H
