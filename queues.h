template <class T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    Node(T val)
    {
        prev = next = NULL;
        data = val;
    }
    Node()
    {
        prev = next = NULL;
    }
};

template <class T>
class Queue
{
    Node<T> *front;

public:
    Queue() : front(NULL) {}

    void enqueue(T val)
    {
        Node<T> *newNode = new Node<T>;

        if (!front)
            front = newNode;
        else
        {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void dequeue()
    {
        if (!front)
            return;

        Node<T> *traverse = front;

        while (traverse->next)
            traverse = traverse->next;

        if (traverse->prev)
            traverse->prev->next = NULL;
        else
            front = NULL;
        delete traverse;
    }

    T *frontVal()
    {
        if (!front)
            return NULL;

        return &(front->data);
    }

    int size()
    {
        if (!front)
            return 0;

        Node<T> *traverse = front;
        int s = 1;

        while (traverse)
        {
            traverse = traverse->next;
            s++;
        }

        return s;
    }
};

template <class T>
// Double queue that can be inserted into and accessed from both sides, the front and the back
class DoubleQueue
{
    Node<T> *front;
    Node<T> *back;

public:
    DoubleQueue() : front(NULL), back(NULL) {}

    void backeq(T val)
    {
        Node<T> *newNode = new Node<T>(val);

        if (!front)
        {
            front = newNode;
            back = newNode;
        }
        else
        {
            Node<T> *node = back;

            node->next = newNode;
            newNode->prev = node;
            back = newNode;
        }
    }

    void fronteq(T val)
    {
        Node<T> *newNode = new Node<T>(val);

        if (!back)
        {
            front = newNode;
            back = newNode;
        }
        else
        {
            Node<T> *node = front;

            node->prev = newNode;
            newNode->next = node;
            front = newNode;
        }
    }

    void frontdq()
    {
        if (!front)
        {
            back = NULL;
            return;
        }

        if (front->next)
            front->next->prev = NULL;
        else
            back = NULL;
        Node<T> *node = front;
        front = front->next;
        delete node;
    }

    void backdq()
    {
        if (!back)
        {
            front = NULL;
            return;
        }

        if (back->prev)
            back->prev->next = NULL;
        else
            front = NULL;
        Node<T> *node = back;
        back = back->prev;
        delete back;
    }

    T *frontVal()
    {
        if (!front)
            return NULL;

        return &(front->data);
    }

    T *backVal()
    {
        if (!back)
            return NULL;

        return &(back->data);
    }

    bool empty()
    {
        if (!front)
            return true;

        return false;
    }
};

template <class T>
// Priority queue used as a min queue to make the huffman tree
class PriorityQueue
{
    Node<T> *front;

public:
    PriorityQueue() : front(NULL) {}

    void enqueue(T val)
    {
        Node<T> *newNode = new Node<T>(val);

        if (!front)
            front = newNode;
        else if (front->data->freq >= val->freq)
        {
            // cout << 'a' << endl;
            front->prev = newNode;
            newNode->next = front;
            front = newNode;
        }
        else
        {
            Node<T> *traverse = front;

            while (traverse->next)
            {
                if (traverse->next->data->freq >= val->freq)
                    break;
                traverse = traverse->next;
            }

            Node<T> *temp = traverse->next;
            traverse->next = newNode;
            newNode->prev = traverse;
            if (temp)
            {
                temp->prev = newNode;
                newNode->next = temp;
            }
        }
    }

    void dequeue()
    {
        if (!front)
            return;

        Node<T> *node = front;
        front = front->next;
        if (front->next != NULL)
            front->next->prev = NULL;
        delete node;
    }

    T getMin()
    {
        if (!front)
            return NULL;
        return front->data;
    }

    T getMax()
    {
        if (!front)
            return -1;

        Node<T> *traverse = front;

        do
        {
            traverse = traverse->next;
        } while (traverse->next);

        return traverse->data;
    }

    int size()
    {
        Node<T> *traverse = front;
        int size = 1;

        while (traverse->next)
        {
            traverse = traverse->next;
            size++;
        }

        return size;
    }
};