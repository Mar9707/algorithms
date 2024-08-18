#include <iostream>
#include <queue>


class Node {
    public:

    int val;
    Node* left;
    Node* right;

    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int key) : val(key), left(nullptr), right(nullptr) {}

};


class AVL {
    private:

        Node* root;

    
    public:

        AVL () : root(nullptr) {}

        Node* getRoot(){
            return root;
        }

        bool search (Node* node, int key){
            if(!node) return false;

            
            if(node->val == key){
                return true;
            } else if(key > node->val){
                return search(node->right, key);
            } else {
                return search(node->left, key);
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


        void preOrder (Node* node){
            if(!node) return;

            std::cout << node->val << " ";
            preOrder(node->left);
            preOrder(node->right);
        }


        void inOrder(Node* node){
            if(!node) return;

            inOrder(node->left);
            std::cout << node->val << " ";
            inOrder(node->right);
        }


        void postOrder(Node* node){
            if(!node) return;

            postOrder(node->left);
            postOrder(node->right);
            std::cout << node->val << " ";
        }

        void levelOrder (Node* node){
            if(!node) return;

            std::queue<Node*> que;
            que.push(node);

            while(!que.empty()){
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


        Node* predecessor (Node* node){
            if(!node) return nullptr;

            if(node-> left){
                return getMax(node->left);
            }

            Node* predecess = nullptr;
            Node* ancestor = root;

            while(node != ancestor){
                if(node->val < ancestor->val){
                    ancestor = ancestor -> left;
                } else if(node-> val > ancestor->val){
                    predecess = ancestor;
                    ancestor = ancestor -> right;
                }
            }

            return predecess;
        }


        Node* successor (Node* node){
            if(!node) return nullptr;

            if(node->right){
                return getMin(node->right);
            }

            Node* succes = nullptr;
            Node* ancestor = root;

            while(node != ancestor){
                if(node->val > ancestor->val){
                    ancestor = ancestor->right;
                } else if (node->val < ancestor->val){
                    succes = ancestor;
                    ancestor = ancestor->left;
                }
            }

            return succes;
        }

        int getBF (Node* node){
            if(!node) return 0;

            return getHeight(node->left) - getHeight(node->right);
        }


        void clear (Node* node){
            if(!node) return;

            clear(node->left);
            clear(node->right);

            delete node;
        }

        void clear(){
            clear(root);
            root = nullptr;
        }


        Node* rightRotate(Node* node){
            if(!node) return nullptr;
            Node* y = node->left;
            Node* T3 = y->right;
            y->right = node;
            node->left = T3;

            return y;
        }

        Node* leftRotate(Node* node){
            if(!node) return nullptr;

            Node* y = node->right;
            Node* T2 = y->left;
            y->left = node;
            node->right = T2;
            return y;
        }


        Node* insert (Node* node, int key){
            if(!node) return new Node(key);

            if(node->val > key){
                node->left = insert(node->left, key);
            } else if(node->val < key){
                node->right = insert(node->right, key);
            }

            int bf = getBF(node);

            if(bf > 1 && node->left->val > key){
                return rightRotate(node);
            } else if( bf > 1 && node->left->val < key){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            } else if(bf < -1 && node->right->val < key){
                return leftRotate(node);
            } else if(bf < -1 && node->right->val > key){
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }


        void insert (int key){
            root = insert(root, key);   
        }


        Node* deleteNode(Node* node, int key){
            if(!node) return node;

            if(node->val > key){
                node->left = deleteNode(node->left, key);
            } else if(node->val < key){
                node->right = deleteNode(node->right, key);
            } else {
                if(!node->left){
                    Node* tmp = node->right;
                    delete node;
                    return tmp;
                } else if (!node->right){
                    Node* tmp = node->left;
                    delete node;
                    return tmp;
                } else {
                    Node* tmp = getMin(node->right);
                    node->val = tmp->val;
                    node->right = deleteNode(node->right, tmp->val);
                }
            }

            int bf = getBF(node);
            if(bf > 1 && getBF(node->left) >= 0){
                return rightRotate(node);
            } else if(bf > 1 && getBF(node->left) < 0){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            } else if(bf < -1 && getBF(node->right) <= 0){
                return leftRotate(node);
            } else if (bf < -1 && getBF(node->right) > 0){
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }
};


int main (){
    AVL tree;
    std::cout << "is empty? = " << tree.empty() << std::endl;

    int c =  0;

    tree.insert(15);
    Node* root = tree.getRoot();

    
    for(int i = 0; i < 7; ++i){
        std::cin >> c;
        tree.insert(c);
        std::cout << "level" << std::endl;
         tree.levelOrder(root);
        std::cout << std::endl;
    }



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