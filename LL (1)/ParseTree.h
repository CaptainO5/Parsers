class Node{
    public:
        char t;
        Node* children[25];
        Node(char);
};

class Tree{
    private:
        Node* top;
    public:
        Tree();
        int insert();
        void print();
};