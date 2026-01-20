#pragma once
#ifndef _ECS_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <type_traits>
#include "AEEngine.h"


using namespace std;


namespace SystemPattern
{

    //Work in progress
    class ECS
    {
    private:

        template<typename Tuple, typename New>
        struct tuplePushBack;

        template<typename... Ts, typename New>
        struct tuplePushBack<tuple<Ts...>, New> {
            using type = tuple<Ts..., New>;
        };

        template<typename Tuple, typename New>
        using tuplePushBack_t = typename tuplePushBack<Tuple, New>::type;

        template<typename T, typename Tuple> struct tupleContains;

        template<typename T>
        struct tupleContains<T, tuple<>> : false_type {};

        template<typename T, typename U, typename... Us>
        struct tupleContains<T, tuple<U, Us...>>
            : conditional_t<is_same_v<T, U>, true_type, tupleContains<T, tuple<Us...>>> {
        };

        template<typename Tuple, typename New>
        struct tuplePushBack_unique;

        template<typename... Ts, typename New>
        struct tuplePushBack_unique<tuple<Ts...>, New> {
            using type = conditional_t<tupleContains<New, tuple<Ts...>>::value, tuple<Ts...>, tuple<Ts..., New>>;
        };

    protected:

    public:
    };

    //Personal research into a new novel design philosophy i thought of
    class FTACSystem
    {
    private:

    protected:

    public:
      
    };

}



#endif