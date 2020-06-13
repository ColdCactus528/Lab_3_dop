#include "Bnode.cpp"

class BTree 
{ 
	BNode *root; 
	int tree_range;
public: 
	BTree(int t_range) {
		root = NULL;
		tree_range = t_range; 
	} 
  
	void traverse() {
		if (root != NULL) 
		root->traverse(); 
	} 
  
    BNode* search(int ki) {
		return (root == NULL)? NULL : root->search(ki);
	} 
  
    void insert(int ki) {
		if (root == NULL) { 
			root = new BNode(tree_range, true); 
	        root->keys[0] = ki; 
	        root->num_keys = 1; 
	   
	    } else { 

			if (root->num_keys == 2*tree_range-1) { 
	            BNode *s = new BNode(tree_range, false); 
	  
	            s->Ch_ptr[0] = root; 
	  
	            s->splitChild(0, root); 
	  
				int i = 0; 
				if (s->keys[0] < ki) 
					i++; 
	            
	            s->Ch_ptr[i]->insertNonFull(ki); 
	   
				root = s; 
	        } 
	        
	        else
	            root->insertNonFull(ki); 
	    }
	}

	void remove(int ki) { 
		if (!root) { 
			cout << "The tree is empty\n"; 
			return; 
		} 
	  
		root->remove(ki); 
	  
		if (root->num_keys == 0) { 
			BNode *temp = root;

			if (root->leaf) 
				root = NULL; 
			
			else
				root = root->Ch_ptr[0]; 
	  
			delete temp; 
		} 
	return; 
	}
};
