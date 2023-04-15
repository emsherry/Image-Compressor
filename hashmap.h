#include <iostream>
#include <string>
using namespace std;

template <class T>
struct listNode
{
    int pix[3];
    T code;
    listNode *next;
    listNode *prev;
    listNode(int val[], T c)
    {
        for (int i = 0; i < 3; i++)
            pix[i] = val[i];
        code = c;
        next = prev = NULL;
    }
    listNode(listNode *node)
    {
        for (int i = 0; i < 3; i++)
            this->pix[i] = node->pix[i];
        this->code = node->code;
        next = prev = NULL;
    }
};

template <class T>
class HashMap;

template <class T>

// Linked List that stores pixel RGB values in its nodes
class list
{
    listNode<T> *head;
    friend class HashMap<T>;

public:
    list() : head(NULL) {}

    void insert(int val[], T c)
    {
        listNode<T> *newNode = new listNode<T>(val, c);

        if (!head)
            head = newNode;
        else
        {
            listNode<T> *traverse = head;

            while (traverse->next)
            {
                if (traverse->pix[0] == val[0] && traverse->pix[1] == val[1] && traverse->pix[2] == val[2])
                {
                    traverse->code = c;
                    return;
                }
                traverse = traverse->next;
            }

            traverse->next = newNode;
            newNode->prev = traverse;
        }
    }

    T *search(int val[])
    {
        if (!head)
            return NULL;

        listNode<T> *traverse = head;

        while (traverse)
        {
            if (traverse->pix[0] == val[0] && traverse->pix[1] == val[1] && traverse->pix[2] == val[2])
                return &(traverse->code);
        }

        return NULL;
    }
};

template <class T>

// HashMap that is both used for frequencies and the binary codes of pixel RGB values
class HashMap
{
    int size;
    list<T> *table;
    listNode<T> *root;

public:
    HashMap(int s = 1511)
    {
        size = s;
        table = new list<T>[size];
        root = NULL;
    }

    int hashFunc(int val[])
    {
        int res = 0;
        for (int i = 0; i < 3; i++)
        {
            res += val[i] * (i + 1);
        }
        return res % size;
    }

    void insert(int val[], T code)
    {
        int index = hashFunc(val);
        table[index].insert(val, code);
    }

    T *search(int val[])
    {
        int index = hashFunc(val);
        T *temp = table[index].search(val);
        return temp;
    }

    listNode<T> *traverse()
    {
        listNode<T> *root = NULL;

        for (int i = 0; i < size; i++)
        {
            if (table[i].head == NULL)
                continue;
            else
            {
                listNode<T> *traverse = table[i].head;

                while (traverse)
                {
                    if (!root)
                    {
                        // cout << "a ";
                        root = new listNode<T>(traverse);
                        traverse = traverse->next;
                    }
                    else
                    {
                        root->next = new listNode<T>(traverse);
                        root->next->prev = root;
                        traverse = traverse->next;
                        root = root->next;
                        // cout << root->pix[1] << ' ';
                    }
                }
            }
        }
        return root;
    }
};