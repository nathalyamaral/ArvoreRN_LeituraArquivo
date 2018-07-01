#include <stdio.h>
#include "RBTree.h"

//Implementações da classe Node
Node::Node(){
    left = right = parent = 0;
    color = BLACK;
}

Node::Node(int value){
    this->value = value;
}

//Implementações da classe RBTree
RBTree::RBTree(){
	nil = new Node();
	root = nil;
	numberOfNodes = 0;
}

RBTree::~RBTree() {
	numberOfNodes = 0;
	deleteTree(root);
	delete nil;
}

void RBTree::print(){
    print(root);
}

int RBTree::size() const{
    return numberOfNodes;
}

bool RBTree::isEmpty() const{
    return numberOfNodes == 0;
}

void RBTree::insert(int value){
    Node *z = new Node(value);
    Node *x = this->root; 
    Node *y = nil;

    while(x != nil){
        y = x;
        if(z->value < x->value){
            x = x->left;

        }else{
            x = x->right;
        }
    }
  
    if(y == nil){
        this->root = z;

    }else{ 

        if(z->value < y->value){
            y->left = z;
        }else{
                y->right = z;
        }   
    }

    z->parent = y;
    z->left = nil;
    z->right = nil;
    z->color = RED;

    insertFixUp(z);
}

bool RBTree::insertFixUp(Node*& z){
    Node *y;
    
    if(root == nil){
    	root = z;
    	root->color = BLACK;
    	return true;
   }

    while(z->parent != nil && z->parent->color == RED){
        if(z == this->root){
            this->root->color = BLACK;
            return true;
        }

        if(z->parent == z->parent->parent->left){
        	y = z->parent->parent->right;

	        if(y->color == RED){
	            z->parent->color = BLACK;
	            y->color = BLACK;
	            z->parent->parent->color = RED;
	            z = z->parent->parent;
	        }else{
	            if(z == z->parent->right){
		            z = z->parent;
		            leftRotation(z);
	            }
	            z->parent->color = BLACK;
	            z->parent->parent->color = RED;
	            rightRotation(z->parent->parent);
	        
	        
	        }

        }else{
           y = z->parent->parent->left;
           if (y->color == RED){
	            z->parent->color = RED;
	            y->color = RED;
	            z->parent->color = BLACK;
	            z = z->parent->parent;
            
            }else{
                if(z == z->parent->left){
                z = z->parent;
                rightRotation(z);
            	}
	            z->parent->color = RED;
	            z->parent->parent->color = BLACK;
	            leftRotation(z);
				//x = root;
            }
        } 
    }

   	root->color = BLACK;
    return true;
}

void RBTree::RBTransplant(Node* u, Node* v){
       if(u->parent == NULL){
           root = v;
       } else if(u == u->parent->left){
        	u->parent->left = v;
        }else {
        	u->parent->right = v;
        }
        if(v != NULL){
        	v->parent = u->parent;
        }
}


bool RBTree::remove(int value){    
    Node* z = root;
    Node* x;
    Node* y;

    //Busca pelo elemento
    while(z != nil && z->value != value){
       if (value < z->value){
           z = z->left;
       }else{
           z = z->right;
       }
    }
    
    //Se não encontrou o elemento
    if (z == nil){
        return false;
    }
    
    //Z aponta para o elemento a ser removido
    y = z;
    int originalColor = y->color;
    
    if (z->left == nil){
        x = z->right;
        
        //Faz o filho direito assumir o lugar de z
        RBTransplant(z, z->right);

    }else{
        if (z->right == nil){
            x = z->left;
            RBTransplant(z, z->left);
        }else{
            y = sucessor(z);
            originalColor = y->color;
            x = y->right;
            
            if (y->parent == z){
                x->parent = y;
            }else{
                RBTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            RBTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
    }
    
    if (originalColor == BLACK){
        removeFixUp(x);
    }
    
    delete z;
   
    return true;
}

void RBTree::removeFixUp(Node*& x){
    Node* w;
    
    while (x != root && x->color == BLACK){
        //Se x for filho esquerdo
        if (x == x->parent->left){
            w = x->parent->right;
            
            if (w->color == RED){ //Caso 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotation(x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK){ //Caso 2
                w->color = RED;
                x = x->parent;
            }else{
                if (w->right->color == BLACK){ //Caso 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotation(w);
                    w = x->parent->right;
                }
                
                //Caso 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotation(x->parent);
                
                x = root;
            }
        }else{ //x é filho direito
            w = x->parent->left;
            
            if (w->color == RED){ //Caso 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotation(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK){ //Caso 2
                w->color = RED;
                x = x->parent;
            }else{
                if (w->left->color == BLACK){ //Caso 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotation(w);
                    w = x->parent->left;
                }
                
                //Caso 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotation(x->parent);
                
                x = root;
            }
        }
    }
    x->color = BLACK;
}

Node* RBTree::sucessor(Node* node){
    Node* suc = node->right;
    
    while (suc->left != nil){
        suc = suc->left;
    }
    return suc;
}

bool RBTree::contains(int value){
	Node* x = root;

	while(x != nil){
		if(x->value == value){
			return true;
		}

		//x = value < x->value ? x->left : x->right;
       if (value < x->value){
           x = x->left;
       }else{
           x = x->right;
       }
	}
	return false;
}

void RBTree::leftRotation(Node* node){
	Node* y = node->right;
	node->right = y->left;

	if(y->left != nil){
		y->left->parent = node;
	}

	y->parent = node->parent;
	if(node->parent == nil){
		root = y;
	}else{
		if(node == node->parent->left){
			node->parent->left = y;
		}else{
			node->parent->right = y;
		}
	}

	y->left = node;
	node->parent = y;
}

void RBTree::rightRotation(Node* node){
	Node* y = node->left;
	node->left = y->right;

	if(y->right != nil){
		y->right->parent = node;
	}

	y->parent = node->parent;
	if(node->parent == nil){
		root = y;
	}else{
		if(node == node->parent->right){
			node->parent->right = y;
		}else{
			node->parent->left = y;
		}
	}

	y->right = node;
	node->parent = y;
}

void RBTree::deleteTree(Node* node){
	if(node != nil){
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

void RBTree::print(Node* node){
	static int offset = 0;

	for (int i = 0; i < offset; ++i){
		printf(" ");
	}

	if (node == nil){
		printf("-[B]\n");
		return;
	}
	
	if(node->color == BLACK){
		printf("%d[B]\n", node->value);
	}else{
		printf("%d[R]\n", node->value);
	}

	offset += 3;
	print(node->left);
	print(node->right);
	offset -= 3;
}
