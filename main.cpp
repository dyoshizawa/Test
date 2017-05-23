
#include <iostream>
#include <memory>

//#include <mmintrin.h>  //MMX
//#include <xmmintrin.h> //SSE
//#include <emmintrin.h> //SSE2
//#include <pmmintrin.h> //SSE3
//#include <tmmintrin.h> //SSSE3
//#include <smmintrin.h> //SSE4.1
//#include <nmmintrin.h> //SSE4.2
//#include <ammintrin.h> //SSE4A
//#include <wmmintrin.h> //AES
#include <immintrin.h> //AVX

#include <chrono>

using namespace::std;

template<typename T>
struct SrcPtr
{
    
    SrcPtr()
    : buff_pt(nullptr)
    , m_buf_size(0)
    {
    }
    SrcPtr(int count, int alliment = 16)
    {
        m_buf_size = (sizeof(T)*count + alliment - 1) & - alliment;
        m_buffer.reset(reinterpret_cast<T*>(_mm_malloc(count, alliment)));
        
        buff_pt = m_buffer.get();
    }
    
    //template<typename U>
    SrcPtr(SrcPtr<T>& src)
    {
        m_buffer = src.m_buffer;
        buff_pt = m_buffer.get();
        m_buf_size = src.m_buf_size;
    }
    
    ~SrcPtr()
    {

    }
    
    SrcPtr<T> operator++(int)
    {
        SrcPtr<T> old;
        old.m_buffer = m_buffer;
        buff_pt++;
        return old;
    }
    
    T* get_pointer()
    {
        return buff_pt;
    }
    
    T& operator[](int n)
    {
        return *(buff_pt + n);
    }
    
    SrcPtr& operator = (SrcPtr& temp)
    {
        m_buffer = temp.m_buffer;
        
        return this;
    }
    
    int32_t get_bufSize()
    {
        return m_buf_size;
    }

    //T* m_buffer;
    shared_ptr<T> m_buffer;
    T* buff_pt;
    int32_t m_buf_size;

   // std::shared_ptr<T> m_buffer;
};

int main(int argc, const char * argv[])
{
    int size = 128;
    int alline = 16;
    /*
    SrcPtr<unsigned short> pointer(size, alline);
    unsigned short* buf = pointer.get_pointer();
    
    memset(buf, 0, size);
    memset(buf, 10, 4);

    for(int i = 0; i < size; i++)
    {
        cout<<"data "<<i<<" : "<<(*pointer.get_pointer())<<endl;
        pointer++;
    }
     */
////////////////////////////////////////////////////////////////
    SrcPtr<unsigned short> buf_A(size, alline);
    SrcPtr<unsigned short> buf_B(size, alline);
    
    for(int i = 0; i < size; i++)
    {
        buf_A[i] = static_cast<unsigned short>(i);
    }
    
    for(int i = 0 ; i < size; i++)
        cout<<buf_A[i]<<endl;

    return 0;
}

