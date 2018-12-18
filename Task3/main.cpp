#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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

template <class TL>
class ReaderOneType {
public:
    static void ReadOneType(unsigned char* block, std::istream &fin) {
        auto *tmp = (typename TL::head*)block;

        fin >> *tmp;

        auto block_with_offset = block + sizeof(*tmp);
        ReaderOneType<typename TL::Tail>::ReadOneType(block_with_offset, fin);
    }
};

template <>
void ReaderOneType<NullType>::ReadOneType(unsigned char* block, std::istream &fin) {

}

template <class TL>
class Reader {
    ReaderOneType<TL> readerOneType;
public:
    void *readNextLine(std::istream &fin) {
        auto block = (unsigned char*)malloc(Length<TL>::value);

        readerOneType.ReadOneType(block, fin);
        return block;
    }
};

typedef Typelist<int, Typelist<char, Typelist<char, NullType> > > TL;

int main() {
    std::cout << "Typelist: ";
    Print<TL>();
    std::cout << std::endl;

    std::ifstream fin;
    fin.open("input.txt");

    Reader<TL> R;
    R.readNextLine(fin);
    fin.close();
    return 0;
}