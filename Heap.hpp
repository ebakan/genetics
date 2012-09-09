/*
 *  Heap.hpp
 *  Copyright (C) 2012 Eric Bakan
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

struct minHeap
{
    template<typename T>
    short operator() (const T& l, const T& r)
    {
        if (l < r)
        {
            return -1;
        }
    
        if (l > r)
        {
            return 1;
        }
    
        return 0;
    }
};

struct maxHeap
{
    template<typename T>
    short operator() (const T& l, const T& r)
    {
        if (l < r)
        {
            return 1;
        }
    
        if (l > r)
        {
            return -1;
        }
    
        return 0;
    }
};

/**
 * Basic vector-based templated binary heap
 */
template<typename T, typename C = minHeap>
class Heap
{
    public:
        Heap(int size=0, int cap=0)
            : m_cap(cap)
        {
            if (m_cap > 0)
            {
                size = m_cap;
            }

            m_data.reserve(size);
        }

        void Insert(const T& t)
        {
            if (Size() > 0 && m_cap > 0 && Size() >= m_cap)
            {
                if (m_c(t, m_data[0]) < 0)
                {
                    Replace(t);
                }
            }
            else
            {
                m_data.push_back(t);
                int child = Size()-1;
                int parent = Parent(child);
                while (parent >= 0 && m_c(m_data[parent], m_data[child]) < 0)
                {
                    Swap(parent, child);
                    child = parent;
                    parent = Parent(child);
                }
            }

        }

        const T& Peek() const
        {
            return m_data[0];
        }

        T Pop()
        {
            int size = Size();
            if (size == 0)
            {
                return T();
            }
            T ret = m_data[0];
            if (size == 1)
            {
                m_data.clear();
                return ret;
            }
            m_data[0] = m_data[Size()-1];
            m_data.pop_back();
            HeapDown();
            return ret;
        
        }

        void Replace(const T& t, int pos=0)
        {
            if (pos < Size())
            {
                m_data[pos] = t;
                HeapDown();
            }
        }

        int Size() const
        {
            return m_data.size();
        }

        void Flush()
        {
            m_data.clear();
        }


    private:
        int Parent(int i)
        {
            return (i-1)/2;
        }

        int LChild(int i)
        {
            return i*2+1;
        }

        int RChild(int i)
        {
            return i*2+2;
        }

        void Swap(int l, int r)
        {
            T t = m_data[l];
            m_data[l] = m_data[r];
            m_data[r] = t;
        }

        void HeapDown()
        {
            int parent = 0;
            while (true)
            {
                int left = LChild(parent);
                int right = RChild(parent);
                int size = Size();
                if (left >= size)
                {
                    break;
                }
                int max = left;
                if (right < size && m_c(m_data[left], m_data[right]) < 0)
                {
                    max = right;
                }
                if (m_c(m_data[parent], m_data[max]) < 0)
                {
                    Swap(parent, max);
                    parent = max;
                }
                else
                {
                    break;
                }
            }
        
        }


        int m_cap;
        C m_c;
        std::vector<T> m_data;
};
#endif //HEAP_HPP
