#include <iostream>
#include <queue>

class Node {
    public:

    int val;
    Node* left;
    Node* right;

    Node(int val) : val{val}, left{nullptr}, right{nullptr} {}
};

class BST {
    private:
        Node* root;


    public:
        BST() : root(nullptr){}

        Node* getRoot() {
            return root;
        }

        bool search (Node* node, int val){
            if(!node) return false;

            
            if(node->val==val){
                return true;
            } else if(node->val > val){
                return search (node->left, val);
            } else {
                return search(node->right, val);
            }

            return false;
        }


        Node* getMin(Node* node){
            if(!node) return nullptr;

            while(node->left){
                node = node->left;
            }

            return node;
        }


        Node* getMax(Node* node){
            if(!node) return nullptr;

            while(node->right){
                node = node->right;
            }
            
            return node;
        }

        void preOrder(Node* node){
            if(!node) return;
            std::cout << node->val << ' ';
            preOrder(node->left);
            preOrder(node->right);
        }

         void postOrder(Node* node){
            if(!node) return;
            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->val << ' ';
        }

        void inOrder(Node* node){
            if(!node) return;
            inOrder(node->left);
            std::cout << node->val << ' ';
            inOrder(node->right);
        }

        void levelOrder (Node* node){
            if(!node) return;

            std::queue<Node*> que;
            que.push(node);

            while(que.empty() == false){
                Node* curr = que.front();
                que.pop();
                std::cout << curr->val << " ";

                if(curr->left){
                    que.push(curr->left);
                }

                if(curr->right){
                    que.push(curr->right);
                }
            }
        }

        void insert(int val) {
            root = insert(root, val);
        }

        Node* insert (Node* node, int val){
            if(!node) return new Node (val);

            if(node->val >= val){
                node->left = insert(node->left, val);
            } else {
                node->right = insert(node->right, val);
            }

            return node;
        }

        Node* deleteNode (Node* node, int val){
            if(!node) return nullptr;

            if(node->val > val){
                node->left = deleteNode(node->left, val);
            } else if(node->val < val){
                node->right = deleteNode(node->right, val);
            } else {
                if(!node->left) {
                    Node* tmp = node->right;
                    delete node;
                    return tmp; 
                } else if(!node->right) { 
                    Node* tmp = node->left; 
                    delete node;
                    return tmp; 
                } else {
                    Node* tmp = getMin(node->right);
                    node->val = tmp->val;
                    node->right = deleteNode(node->right, tmp->val);
                }
            }
            return node;
        }

        bool empty(){
            return root == nullptr;
        }

        int getHeight (Node* node){
            if(!node) return -1;

            return std::max(getHeight(node->left), getHeight(node->right)) + 1;
        }

        int count (Node* node){
            if(!node) return 0;
            
            return count(node->left) + count(node->right) + 1;
        }

        void clear (Node* node){
            if(!node) return;

            clear(node->left);
            clear(node->right);

            delete node;
        }

        void clear() {
            clear(root);
            root = nullptr;
        }


        Node* predecessor (Node* node){
            if(!node) return nullptr;

            if(node->left){
                return getMax(node->left);
            }

            Node* pred = nullptr;
            Node* ancestor = root;

            while(node != ancestor){
                if(node->val > ancestor->val){
                    pred = ancestor;
                    ancestor = ancestor->right;
                } else {
                    ancestor = ancestor->left;
                }
            }
            return pred;
        }


        Node* successor (Node* node){
            if(!node) return nullptr;

            if(node->right){
                return getMin(node->right);
            }

            Node* succes = nullptr;
            Node* ancestor = root;

            while(ancestor != node){
                if(node->val > ancestor-> val){
                    ancestor  = ancestor -> right;
                } else {
                    succes = ancestor;
                    ancestor = ancestor -> left;
                }
            }

            return succes;
        }
};




int main (){
    BST tree;
    std::cout << "is empty? = " << tree.empty() << std::endl;


    int c =  0;
    
    for(int i = 0; i < 7; ++i){
        std::cin >> c;
        tree.insert(c);
    }

    Node* root = tree.getRoot();

    std::cout << "Inorder: ";
    tree.inOrder(root);
    std::cout << "\nPreorder: ";
    tree.preOrder(root);
    std::cout << "\nPostorder: ";
    tree.postOrder(root);
    std::cout << "\nLevelorder: ";
    tree.levelOrder(root);
    std::cout << std::endl;

    std::cout << "search 50 = " << tree.search(root, 50) << std::endl;
    std::cout << "height = " << tree.getHeight(root) << std::endl;
    std::cout << "is empty? = " << tree.empty() << std::endl;
    tree.deleteNode(root, 50);
    std::cout << "search 50 = " << tree.search(root, 50) << std::endl;
    tree.levelOrder(root);
    std::cout << "count = " << tree.count(root) << std::endl;
    tree.insert(14);
    tree.levelOrder(root);
    std::cout << "min = " << tree.getMin(root)->val << std::endl;
    std::cout << "max = " << tree.getMax(root)->val << std::endl;
    std::cout << "count = " << tree.count(root) << std::endl;
    std::cout << "predecessor = " << tree.predecessor(root)->val << std::endl;
    std::cout << "successor = " << tree.successor(root)->val << std::endl;

    
    return 0;
}