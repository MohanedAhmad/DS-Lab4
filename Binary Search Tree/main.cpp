#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int _data) : data(_data), left(NULL), right(NULL) { }
};

class binarySearchTree
{
private:
    Node *root;

    Node* getNodeByData(int _data)
    {
        Node* current = root;

        while(current != NULL)
        {
            if(current->data == _data)
            {
                return current;
            }
            else
            {
                if(_data > current->data)
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }
            }
        }
        return NULL;
    }

    Node* getParentByNode(Node *node)
    {
        Node* parent = root;

        if(node == root)
        {
            return root;
        }
        else
        {
            while(parent != NULL)
            {
                if( (parent->left == node) || (parent->right == node) )
                {
                    return parent;
                }
                else
                {
                    if(node->data > parent->data)
                    {
                        parent = parent->right;
                    }
                    else
                    {
                        parent = parent->left;
                    }
                }
            }
        }
        return NULL;
    }

    Node* getMaxRightNode(Node *node)
    {
        Node *current = node;

        while(current->right != NULL)
        {
            current = current->right;
        }
        return current;
    }

    Node* getMaxLeftNode(Node *node)
    {
        Node *current = node;

        while(current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    void display(Node *node)
    {
        if(node != NULL)
        {
            display(node->left);
            cout << node->data << "  ";
            display(node->right);
        }
    }

public:
    binarySearchTree() : root(NULL) { }

    void addNode(int _data)
    {
        Node *newNode = new Node(_data);

        if(root == NULL)
        {
            root = newNode;
        }
        else
        {
            Node *current = root;
            Node *parrent = NULL;

            while(current != NULL)
            {
                parrent = current;

                if(newNode->data > current->data)
                {
                    current = current->right;
                }
                else
                {
                    current = current->left;
                }
            }

            if(newNode->data > parrent->data)
            {
                parrent->right = newNode;
            }
            else
            {
                parrent->left = newNode;
            }
        }
    }

    void removeNode(int _data)
    {
        Node *node = getNodeByData(_data);
        Node *maxChild = NULL;

        if(node == NULL)
        {
            cout << "\nNo node found with value " << _data << endl;
        }
        else if(node == root)
        {
            if(root->left == NULL && root->right == NULL)
            {
                root = NULL;
            }
            else if(root->left == NULL)
            {
                root = root->right;
            }
            else if(root->right == NULL)
            {
                root = root->left;
            }
            else
            {
                maxChild = getMaxRightNode(root->left);
                maxChild->right = root->right;
                root = root->left;
            }
        }
        else
        {
            Node *parent = getParentByNode(node);
            Node *newChild = NULL;

            if(node->left == NULL && node->right == NULL)
            {
                newChild = NULL;
            }
            else if(node->left == NULL)
            {
                newChild = node->right;
            }
            else if(node->right == NULL)
            {
                newChild = node->left;
            }
            else
            {
                    newChild = node->left;
                    maxChild = getMaxRightNode(newChild);
                    maxChild->right = node->right;
            }

            if(parent->left == node)
            {
                parent->left = newChild;
            }
            else
            {
                parent->right = newChild;
            }
        }

        delete node;
    }

    int getParentDataByNodeData(int _data)
    {
        return getParentByNode(getNodeByData(_data))->data;
    }

    int getMaxValue()
    {
        return this->getMaxRightNode(root)->data;
    }

    int getMinValue()
    {
        return this->getMaxLeftNode(root)->data;
    }

    void displayTree()
    {
        cout << "[ ";
        this->display(root);
        cout << "\b]";
    }
};

int main()
{
    binarySearchTree t;
    t.addNode(50);
    t.addNode(60);
    t.addNode(70);
    t.addNode(65);
    t.addNode(30);
    t.addNode(20);
    t.addNode(25);
    t.addNode(35);
    cout << "The tree now is :\n";
    t.displayTree();

    cout << "\n--------------------------------------------------------------------------------------------------------\n";

    cout << "\nThe maximum value of the tree is : " << t.getMaxValue() << endl;
    cout << "\nThe minimum value of the tree is : " << t.getMinValue() << endl;

    cout << "\n--------------------------------------------------------------------------------------------------------\n";

    cout << "\nThe parent of 70 is : " << t.getParentDataByNodeData(70) << endl;

    cout << "\n--------------------------------------------------------------------------------------------------------\n";

    cout << "\nThe tree after removing 60 is : \n";
    t.removeNode(60);
    t.displayTree();

    cout << "\n\nThe tree after removing 70 is : \n";
    t.removeNode(70);
    t.displayTree();

    cout << "\n\nThe tree after removing 25 is : \n";
    t.removeNode(25);
    t.displayTree();

    return 0;
}
