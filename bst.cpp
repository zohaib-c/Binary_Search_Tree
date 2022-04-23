#include <iostream>
#include <vector>

class node{
    public:
        node();
        ~node();
        int data;
        node *left;
        node *right;
        node (int data){
            this->data = data;
            left = NULL;
            right = NULL;
        }
};

node::~node(){
    delete left;
    delete right;
}

class BST{
    public:
        BST();
        ~BST();
        void insertKey(int newKey);
        bool hasKey(int searchKey);
        std::vector<int> inOrder();
        int getHeight();
    private:
        node *root; 
        void insert(int data, node *&root){
            if(root==NULL){
                root = new node(data);
            }
            else if(data < root->data){
                if(root->left!=NULL){
                    insert(data,root->left);
                }
                else{
                    root->left = new node(data);
                }
            }
            else if(data > root->data){
                if(root->right!=NULL){
                    insert(data,root->right);
                }
                else{
                    root->right = new node(data);
                }
            }
        }
        bool search(int searchKey, node *root){
            while (root != NULL) {
                if (searchKey > root->data){
                    root = root->right;
                }
                else if (searchKey < root->data){
                    root = root->left;
                }
                else
                    return true;
            }
            return false;
        }
        void setOrder(node *root, std::vector<int> &inOrder){

            if(root!=NULL){
                setOrder(root->left, inOrder);
                inOrder.push_back(root->data);
                setOrder(root->right, inOrder);
            }
        }

        int height(node* root){
        if (root == NULL){
            return 0;
        }
        else{
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);
        
            if (leftHeight > rightHeight){
                return(leftHeight + 1);
            }
            else{
                return(rightHeight + 1);
            }
        }
    }

};

BST::BST(){
    root = NULL;
}

BST::~BST(){
    delete root;
}


void BST::insertKey(int newKey){
    insert(newKey, root);
}

bool BST::hasKey(int searchKey){
    return search(searchKey, root);
}

std::vector<int> BST::inOrder(){
    std::vector<int> sortedBST;
    setOrder(root, sortedBST);
    return sortedBST;
}

int BST::getHeight(){
    return height(root);
}

int main(){

    int num;
    BST bst;

    std::cout << "Enter the numbers to be stored (end with a letter): ";
    std::cin >> num;
    while (!std::cin.fail()){
        bst.insertKey(num);
        std::cin >> num;
    }
    
    std::cin.clear();
    std::cin.ignore(9999999999,'\n');

    int searchNum;
    std::cout << "Which number do you want to look up? ";
    std::cin >> searchNum;

    if (bst.hasKey(searchNum)){
        std::cout << searchNum << " is in the tree: yes\n";
    }
    else{
        std::cout << searchNum << " is in the tree: no\n";
    }
    
    std::cout << "The numbers in sorted order: ";
    std::vector <int> sorted = bst.inOrder();

    for (int i=0; i < sorted.size(); i++){
        std::cout << sorted.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Height of the tree: " << bst.getHeight();

    return 0;
}