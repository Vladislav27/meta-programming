#include <iostream>


/*      Typelist        */
class NullType {};

template <class T=NullType, class U=NullType>
struct Typelist
{
    typedef T head;
    typedef U Tail;
};


/*      Length      */
template <class TList>
struct Length;

template <>
struct Length<NullType>
{
    enum { value = 0 };
};

template <class T, class U>
struct Length< Typelist<T, U> >
{
    enum { value = 1 + Length<U>::value };
};

template <>
struct Length<Typelist<> >
{
    enum { value = 0 };
};

/*      TypeAt      */
template <class TList, unsigned int index>
struct TypeAt;

template <class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0>
{
    typedef Head Result;
};

template <class Head, class Tail, unsigned int index>
struct TypeAt<Typelist<Head, Tail>, index>
{
    typedef typename TypeAt<Tail, index - 1>::Result Result;
};


/*      Print       */
template <typename TypeList>
void Print() {
    std::cout << typeid(typename TypeList::head).name() << " ";
    Print<typename TypeList::Tail>();
};

template <>
void Print<NullType>() {
    return;
}


/*      Append       */
template <class TList, class T>
struct Append;

template <>
struct Append<NullType, NullType>
{
    typedef NullType Result;
};

template <class T>
struct Append<NullType, T>
{
    typedef Typelist<T, NullType> Result;
};

template <class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail> >
{
    typedef Typelist<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};


/*      Remove      */
template <class TList, class T>
struct Remove;

template <class T>
struct Remove<NullType, T>
{
    typedef NullType Result;
};

template <class T, class Tail>
struct Remove<Typelist<T, Tail>, T>
{
    typedef Tail Result;
};

template <class Head, class Tail, class T >
struct Remove<Typelist<Head, Tail>, T>
{
    typedef Typelist<Head, typename Remove<Tail, T>::Result> Result;
};


/*      Добавление элемента по индексу      */
template <typename TList, typename Type, unsigned int index>
struct AppendByIndex;

template <typename Head, typename Tail, typename Type>
struct AppendByIndex<Typelist<Head, Tail>, Type, 0> {
    typedef Typelist<Typelist<Type, Head>, Tail> Result;
};

template <typename Head, typename Tail, typename Type, unsigned int index>
struct AppendByIndex<Typelist<Head, Tail>, Type, index> {
    typedef typename AppendByIndex<typename AppendByIndex<Typelist<Tail>, Type, index - 1>::Result, Head, 0>::Result Result;
};


/*      Удаление элемента по индексу        */
template <typename TList, unsigned int index>
struct RemoveByIndex;

template <typename Head, typename Tail>
struct RemoveByIndex<Typelist<Head, Tail>, 0> {
    typedef Typelist<Tail> Result;
};

template <typename Head, typename Tail, unsigned int index>
struct RemoveByIndex<Typelist<Head, Tail>, index> {
    typedef typename AppendByIndex<typename RemoveByIndex<Typelist<Tail>, index - 1>::Result, Head, 0>::Result Result;
};



/*      Замена элемента по индексу      */
template <typename TList, typename Type, unsigned int index>
struct Replacement;

template <typename Head, typename Tail, typename Type>
struct Replacement<Typelist<Head, Tail>, Type, 0> {
    typedef typename AppendByIndex<Typelist<Tail>, Type, 0>::Result Result;
};

template <typename Head, typename Tail, typename Type, unsigned int index>
struct Replacement<Typelist<Head, Tail>, Type, index> {
    typedef typename AppendByIndex<typename Replacement<Typelist<Tail>, Type, index - 1>::Result, Head, 0>::Result Result;
};


int main() {
    return 0;
}