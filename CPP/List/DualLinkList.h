#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Object.h"
#include "Exception.h"
#include "Iterartor.h"

namespace ds
{

    template <typename T>
    class DualLinkList : public List<T>
    {
    protected:
        struct Node :public Object
        {
            T value;
            Node* next;
            Node* prev;
        };

        mutable struct : public Object
        {
            char reserved[sizeof ( T)];
            Node* next;
            Node* pre;
        }m_header;

        // Node m_header;

        int m_length;
        int m_step;
        Node* m_current;

        Node* position(int i) const
        {
            Node* ret = reinterpret_cast<Node*>(&m_header);

            for(int p =0; p<i; p++)
            {
                ret = ret->next;
            }

            return ret;
        }

        virtual Node* create()
        {
            return new Node();
        }

        virtual void destroy(Node* pn)
        {
            delete pn;
        }

    public:
        DualLinkList()
        {
            m_header.next = NULL;
            m_header.pre = NULL;
            m_length = 0 ;
            m_current =NULL;
            m_step = 0;
        }

        bool insert(const T& e)
        {
            return insert(m_length,e);
        }

        bool insert(int i, const T& e)
        {
            bool ret = (i >= 0) && (i <= m_length);
            if(ret)
            {
                Node* node = create();

                if(node != NULL)
                {
                    Node* currect = position(i);
                    Node* next = currect->next;
                    node->value = e;
                    node->next = next;
                    currect->next = node;
                    if(currect != reinterpret_cast<Node*>(&m_header))
                    {
                        node->prev = currect;
                    }
                    else
                    {
                        node->prev = NULL;
                    }
                    if(next != NULL)
                    {
                        next->prev = node;
                    }
                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughtMemoryException,"No memory to insert new element ...");
                }
            }
            return ret;
        }

        bool remove(int i)
        {
            bool ret = (i<=m_length)&&(i>=0);
            if(ret)
            {
                Node* currect = position(i);
                Node* toDel = currect->next;
                Node* next = toDel->next;
                if(m_current == toDel)
                {
                    m_current = next;
                }
                currect->next = next;
                if(next != NULL)
                {
                    next->prev = currect;
                }

                m_length--;
                destroy(toDel);
            }
            return ret;
        }

        bool set(int i, const T& e)
        {
            bool ret = (i<=m_length)&&(i>=0);
            if(ret)
            {
                position(i)->next->value = e;
            }
            return ret;
        }

        virtual  T get(int i) const
        {
            T ret;
            if(get(i,ret))
            {
                return ret;
            }
            else
            {
                THROW_EXCEPTION(IndexOutOfBoundsException,"Invalid parameter i to get element ...");
            }
        }

        bool get(int i, T& e)const
        {
            bool ret = (i<=m_length)&&(i>=0);
            if(ret)
            {
                e = position(i)->next->value;
            }
            return ret;
        }

        int find(const T& e) const
        {
            int ret = -1;
            int i =0;
            Node * node = m_header.next;

            while(node)
            {
                if(node->value == e)
                {
                    ret = i;
                    break;
                }
                else
                {
                    node = node->next;
                    i++;
                }
            }
            return ret;
        }

        int length()const
        {
            return m_length;
        }
        void clear()
        {
            while(m_header.next)
            {
                Node* toDel = m_header.next;
                m_header.next = toDel->next;
                m_length--;
                destroy(toDel);
            }
        }

        virtual bool move(int i, int step = 1)
        {
            bool ret = (i >= 0) && (i < m_length) && (step >0);
            if(ret)
            {
                m_current = position(i)->next;
                m_step = step;
            }
            else
            {

            }
            return ret;
        }

        virtual bool next()
        {
            int i = 0;
            while ((i < m_step) && (!isEnd()))
            {
                m_current = m_current->next;
                i++;
            }
            return (i == m_step);
        }

        virtual bool pre()
        {
            int i = 0;
            while ((i < m_step) && (!isEnd()))
            {
                m_current = m_current->prev;
                i++;
            }
            return (i == m_step);
        }

        virtual T current()
        {
            if( !isEnd() )
            {
                return m_current->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException,"No value at current position ...");
            }
        }

        virtual bool isEnd()
        {
            return  (m_length ==0) || (m_current == NULL);
        }


        ~DualLinkList()
        {
            clear();
        }

    public:

        typedef lbidirectionalIterator<T,constTraits<T>,Node >       const_iterator;
        typedef lbidirectionalIterator<T,nonConstTraits<T>,Node >    iterator;

        iterator begin()
        { return m_header.next; }

        const_iterator begin() const
        { return m_header.next; }

        iterator end()
        { return NULL; }

        const_iterator end() const
        { return NULL; }

    };

}
#endif // DUALLINKLIST_H
