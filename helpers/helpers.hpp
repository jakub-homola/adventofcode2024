#pragma once

#include <cstdio>
#include <cstdlib>
#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <deque>
#include <numeric>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <regex>



std::vector<std::string> read_lines()
{
    std::vector<std::string> ret;
    constexpr size_t max_line_len = 100000;
    char line[max_line_len];
    while(true)
    {
        char * s = fgets(line, max_line_len, stdin);
        if(feof(stdin)) break;
        size_t len = strlen(line);
        line[len-1] = '\0';
        if(line[len-2] == '\r') line[len-2] = '\0';
        ret.emplace_back(line);
    }
    return ret;
}



void read_lines(std::vector<std::string> & ret)
{
    constexpr size_t max_line_len = 100000;
    char line[max_line_len];
    while(true)
    {
        char * s = fgets(line, max_line_len, stdin);
        if(feof(stdin)) break;
        size_t len = strlen(line);
        line[len-1] = '\0';
        if(line[len-2] == '\r') line[len-2] = '\0';
        ret.emplace_back(line);
    }
}



void read_lines(std::vector<std::vector<char>> & ret)
{
    constexpr size_t max_line_len = 100000;
    char line[max_line_len];
    while(true)
    {
        char * s = fgets(line, max_line_len, stdin);
        if(feof(stdin)) break;
        size_t len = strlen(line);
        line[len-1] = '\0';
        if(line[len-2] == '\r') line[len-2] = '\0';
        ret.emplace_back(line, line + len);
    }
}



template<typename I>
std::vector<I> read_ints()
{
    std::vector<I> ret;
    while(true)
    {
        I num;
        int r;
        if constexpr(std::is_same_v<I,int>)                r = scanf("%d", &num);
        if constexpr(std::is_same_v<I,unsigned int>)       r = scanf("%u", &num);
        if constexpr(std::is_same_v<I,long long>)          r = scanf("%lld", &num);
        if constexpr(std::is_same_v<I,unsigned long long>) r = scanf("%llu", &num);
        if(feof(stdin)) break;
        ret.push_back(num);
    }
    return ret;
}



void read_until_char(char ch)
{
    while(getchar() != ch) ;
}



enum struct order
{
    row,
    col
};

template<typename T>
struct arrayview_1d
{
    T * data;
    size_t size;
    arrayview_1d(T * d, size_t s) : data{d}, size{s} {}
    T & operator[](size_t i) { return data[i]; }
    const T & operator[](size_t i) const { return data[i]; }
};

template<typename T, order O = order::row>
struct arrayview_2d
{
    T * data;
    size_t nrows, ncols;
    arrayview_2d(T * d, size_t nr, size_t nc) : data{d}, nrows{nr}, ncols{nc} {}
    arrayview_1d<T> operator[](size_t i)
    {
        if constexpr(O == order::row) return arrayview_1d<T>(data + i * ncols, nrows);
        if constexpr(O == order::col) return arrayview_1d<T>(data + i * nrows, ncols);
    }
    const arrayview_1d<T> operator[](size_t i) const
    {
        if constexpr(O == order::row) return arrayview_1d<T>(data + i * ncols, nrows);
        if constexpr(O == order::col) return arrayview_1d<T>(data + i * nrows, ncols);
    }
};

template<typename T, size_t N>
struct arrayview_nd
{
    T * data;
    size_t * sizes;
    arrayview_nd(T * d, size_t * s) : data{d}, sizes(s) {}
    arrayview_nd<T,N-1> operator[](size_t i)
    {
        int offset = 1;
        #pragma unroll
        for(int j = 1; j < N; j++) offset *= sizes[j];
        return arrayview_nd<T,N-1>(data + i * offset, sizes + 1);
    }
    const arrayview_nd<T,N-1> operator[](size_t i) const
    {
        int offset = 1;
        #pragma unroll
        for(int j = 1; j < N; j++) offset *= sizes[j];
        return arrayview_nd<T,N-1>(data + i * offset, sizes + 1);
    }
};

template<typename T>
struct arrayview_nd<T,1>
{
    T * data;
    size_t * sizes;
    arrayview_nd(T * d, size_t * s) : data{d}, sizes(s) {}
    T & operator[](size_t i)
    {
        return data[i];
    }
    const T & operator[](size_t i) const
    {
        return data[i];
    }
};




struct direction
{
    int val;
    constexpr direction() : val(-1) {}
    constexpr direction(int v) : val{v} {}
    constexpr operator int() const { return val; }
    constexpr bool operator==(const direction & other) const { return other.val == val; }
};

struct directions
{
    constexpr static direction none = direction(-1);
    constexpr static direction north = direction(0);
    constexpr static direction east  = direction(1);
    constexpr static direction south = direction(2);
    constexpr static direction west  = direction(3);
    
    constexpr static char to_char(direction d)
    {
        switch(d)
        {
            case directions::north: return 'N';
            case directions::west:  return 'W';
            case directions::south: return 'S';
            case directions::east:  return 'E';
            default: return 'O';
        }
    }
    constexpr static direction turn_left(direction d)
    {
        switch(d)
        {
            case directions::north: return directions::west;
            case directions::west:  return directions::south;
            case directions::south: return directions::east;
            case directions::east:  return directions::north;
            default: return directions::none;
        }
    }
    constexpr static direction turn_right(direction d)
    {
        switch(d)
        {
            case directions::north: return directions::east;
            case directions::east:  return directions::south;
            case directions::south: return directions::west;
            case directions::west:  return directions::north;
            default: return directions::none;
        }
    }
    constexpr static direction turn_around(direction d)
    {
        switch(d)
        {
            case directions::north: return directions::south;
            case directions::south: return directions::north;
            case directions::east:  return directions::west;
            case directions::west:  return directions::east;
            default: return directions::none;
        }
    }
    constexpr static bool is_horizontal(direction dir)
    {
        switch(dir)
        {
            case directions::east:
            case directions::west:
                return true;
            default:
                return false;
        }
    }
    constexpr static bool is_vertical(direction dir)
    {
        switch(dir)
        {
            case directions::north:
            case directions::south:
                return true;
            default:
                return false;
        }
    }
};



std::vector<char *> split_string(char * str, char sep)
{
    std::vector<char *> ret;
    while(true)
    {
        ret.push_back(str);
        str = strchr(str, sep);
        if(str == nullptr) break;
        *str = '\0';
        str++;
    }
    return ret;
}




template<typename T = int>
struct Point2
{
    T x;
    T y;
    Point2() {}
    Point2(T x_, T y_) : x(x_), y(y_) {}
    Point2(const Point2<T> & p) : Point2(p.x, p.y) {}
    Point2(Point2<T> && p) : Point2(p.x, p.y) {}
    Point2<T> & operator=(const Point2<T> & p) { x = p.x; y = p.y; return *this; }
    Point2<T> & operator=(Point2<T> && p) { x = p.x; y = p.y; return *this; }
    std::vector<Point2<T>> get_orthogonal()
    {
        std::vector<Point2<T>> ret;
        ret.push_back(Point2<T>(-y,  x));
        ret.push_back(Point2<T>( y, -x));
        return ret;
    }
};

template<typename T>
Point2<T> operator+(Point2<T> p1, Point2<T> p2)
{
    return Point2(p1.x + p2.x, p1.y + p2.y);
}
template<typename T>
Point2<T> operator-(Point2<T> p1, Point2<T> p2)
{
    return Point2(p1.x - p2.x, p1.y - p2.y);
}
template<typename T>
Point2<T> operator-(Point2<T> p)
{
    return Point2(-p.x, -p.y);
}
template<typename T>
Point2<T> operator*(int a, Point2<T> p)
{
    return Point2(a * p.x, a * p.y);
}
template<typename T>
bool operator<(const Point2<T> & l, const Point2<T> & r)
{
    if(l.y < r.y) return true;
    return l.x < r.x;
}
template<typename T>
bool operator==(const Point2<T> & l, const Point2<T> & r)
{
    return (l.x == r.x) && (l.y == r.y);
}
template<typename T>
bool operator!=(const Point2<T> & l, const Point2<T> & r)
{
    return (l.x != r.x) || (l.y != r.y);
}



template<typename T = int>
struct Loc2
{
    T r;
    T c;
    Loc2() {}
    Loc2(T r_, T c_) : r(r_), c(c_) {}
    Loc2(const Loc2<T> & p) : Loc2(p.r, p.c) {}
    Loc2(Loc2<T> && p) : Loc2(p.r, p.c) {}
    Loc2<T> & operator=(const Loc2<T> & p) { r = p.r; c = p.c; return *this; }
    Loc2<T> & operator=(Loc2<T> && p) { r = p.r; c = p.c; return *this; }
};
template<typename T>
Loc2<T> operator+(Loc2<T> p1, Loc2<T> p2)
{
    return Loc2(p1.r + p2.r, p1.c + p2.c);
}
template<typename T>
Loc2<T> operator-(Loc2<T> p1, Loc2<T> p2)
{
    return Loc2(p1.r - p2.r, p1.c - p2.c);
}
template<typename T>
Loc2<T> operator-(Loc2<T> p)
{
    return Loc2(-p.r, -p.c);
}
template<typename T>
Loc2<T> operator*(T s, Loc2<T> p)
{
    return Loc2(s * p.r, s * p.c);
}
template<typename T>
bool operator<(const Loc2<T> & l, const Loc2<T> & r)
{
    if(l.r < r.r) return true;
    return l.c < r.c;
}
template<typename T>
bool operator==(const Loc2<T> & l, const Loc2<T> & r)
{
    return (l.r == r.r) && (l.c == r.c);
}
template<typename T>
bool operator!=(const Loc2<T> & l, const Loc2<T> & r)
{
    return (l.r != r.r) || (l.c != r.c);
}



Point2<int> dir_to_point_int(direction dir)
{
    switch(dir.val)
    {
        case directions::north: return Point2<int>(0,-1);
        case directions::east:  return Point2<int>(1,0);
        case directions::south: return Point2<int>(0,1);
        case directions::west:  return Point2<int>(-1,0);
        default: return Point2<int>(0,0);
    }
}

Loc2<int> dir_to_loc_int(direction dir)
{
    switch(dir.val)
    {
        case directions::north: return Loc2<int>(-1,0);
        case directions::east:  return Loc2<int>(0,1);
        case directions::south: return Loc2<int>(1,0);
        case directions::west:  return Loc2<int>(0,-1);
        default: return Loc2<int>(0,0);
    }
}

char dir_to_char(direction dir)
{
    switch(dir.val)
    {
        case directions::north: return '^';
        case directions::east:  return '>';
        case directions::south: return 'V';
        case directions::west:  return '<';
        default: return '_';
    }
}

class timer
{
private:
    static constexpr double ticks_to_sec = ((double)std::chrono::steady_clock::period::num) / std::chrono::steady_clock::period::den; // duration of one tick
    std::chrono::steady_clock::time_point start_point;
    long long ticks = 0;
public:
    void start()
    {
        start_point = std::chrono::steady_clock::now();
    }
    void stop()
    {
        ticks = (std::chrono::steady_clock::now() - start_point).count();
    }
    double get_time_s()
    {
        return ticks * ticks_to_sec;
    }
    double get_time_ms()
    {
        return get_time_s() * 1000.0;
    }
};

std::vector<std::string> grid_pad(std::vector<std::string> & in, char c, int ps = 1)
{
    std::vector<std::string> ret(in.size() + 2 * ps, std::string(in[0].size() + 2 * ps, c));
    for(int r = 0; r < in.size(); r++)
    {
        for(int c = 0; c < in[r].size(); c++)
        {
            ret[r+ps][c+ps] = in[r][c];
        }
    }
    return ret;
}
