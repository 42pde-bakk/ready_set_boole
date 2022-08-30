//
// Created by Peer De bakker on 8/30/22.
//

#ifndef READY_SET_BOOLE_SETOPERATIONS_HPP
#define READY_SET_BOOLE_SETOPERATIONS_HPP

#include <set>

template<typename T>
std::set<T> operator!(const std::set<T>& a) {
    (void)a;
    return std::set<T>();
}

template<typename T>
std::set<T> operator&(const std::set<T> &a, const std::set<T> &b) {
    std::set<T> out;
    for (auto& t : a) {
        if (b.find(t) != b.end())
            out.insert(t);
    }
    return (out);
}

template<typename T>
std::set<T> operator|(const std::set<T>& a, const std::set<T>& b) {
    std::set<T> out;
    for (auto& t : a)
        out.insert(t);
    for (auto& t : b)
        out.insert(t);
    return (out);
}

template<typename T>
std::set<T> operator^(const std::set<T>& a, const std::set<T>& b) {
    std::set<T> out;
    for (auto& t : a) {
        if (b.find(t) == b.end())
            out.insert(t);
    }
    for (auto& t : b) {
        if (a.find(t) == a.end())
            out.insert(t);
    }
    return (out);
}

#endif //READY_SET_BOOLE_SETOPERATIONS_HPP
