#include <string>
#include "queues.h"
#include "hashMap.h"
using namespace std;

template <class T>
// Pixel structure that stores the frequencies of each pixel value so it can be used to build a huffman tree to get binary strings out of
struct TreeNode
{
    T data[3];
    unsigned int freq;
    TreeNode *left;
    TreeNode *right;
    TreeNode(T val[], int f)
    {
        left = right = NULL;
        for (int i = 0; i < 3; i++)
            data[i] = val[i];
        freq = f;
    }
    TreeNode(int f)
    {
        left = right = NULL;
        freq = f;
        for (int i = 0; i < 3; i++)
            data[i] = 0;
    }
};

template <class T>
class HuffmanTree
{
    PriorityQueue<TreeNode<int> *> pq;
    TreeNode<int> *root;
    int len, width;
    HashMap<string> h;

    /**
     * @brief a recursive function used to traverse the huffman tree in-order and make the binary string for each leaf node
     *
     * @param node initially root of the tree, then a recursive next node passed into it
     * @param code makes the binary code of the pixel value and stores it in a hashMap
     */
    void makeHuffcode(TreeNode<int> *node, string code)
    {
        if (node)
        {
            makeHuffcode(node->left, code + '0');
            if (node->left == NULL && node->right == NULL)
                h.insert(node->data, code);
            makeHuffcode(node->right, code + '1');
        }
    }

public:
    HuffmanTree() : root(NULL) {}

    /**
     * @brief function inserts the pixel value with its frequency in the MinQueue
     *
     * @param val RGB value being used in the image
     * @param freq frequency of respective RGB value being used in the image
     */
    void insert(int val[], int freq)
    {
        TreeNode<int> *node = new TreeNode<int>(val, freq);
        pq.enqueue(node);
    }

    /**
     * @brief a function that uses the MinQueue created from all the pixel values with their respective frequencies to make a tree which can be used to calculate the binary codes for all pixel values being used in the image you want to compress
     *
     */
    void buildTree()
    {
        TreeNode<int> *node, *min1, *min2;
        int size = pq.size();

        // We pop from the MinQueue the 2 lowest frequencies add them, 
        // make the two lowest terms used to create it its children and add it back to the MinQueue,
        //  until there is only 1 element left in the Queue which will be our root. 
        /This is the core of our huffman tree
        while (pq.size() - 1 != 1)
        {
            // pop 2 minimum frequencies from MinQueue
            min1 = pq.getMin();
            pq.dequeue();
            min2 = pq.getMin();
            pq.dequeue();

            // create new node from addition of both frequencies and add both of the nodes as its child elements
            node = new TreeNode<int>(min1->freq + min2->freq);
            node->left = min1;
            node->right = min2;

            pq.enqueue(node);
        }

        min1 = pq.getMin();
        pq.dequeue();
        min2 = pq.getMin();
        node = new TreeNode<int>(min1->freq + pq.getMin()->freq);
        node->left = min1;
        node->right = min2;
        root = node;
    }

    void makeHuffcode()
    {
        makeHuffcode(root, "");
    }

    /**
     * @brief Takes RGB value and returns the binary code for it
     *
     * @param val Pixel value for which you need th binary code for
     * @return string binary code of given RGB value
     */
    string search(int val[])
    {
        string *code = h.search(val);
        if (code)
            return *code;
        return "\0";
    }
};