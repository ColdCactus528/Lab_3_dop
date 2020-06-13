#include <iostream>
using namespace std;

struct BNode 
{ 
	int *keys; 
	int trange; 
	BNode **Ch_ptr; 
	int num_keys; 
	bool leaf;

	BNode(int range, bool leaf_1) {
		trange = range;
		leaf = leaf_1;
		keys = new int[2*trange-1];
		Ch_ptr = new BNode *[2*trange];
		num_keys = 0;
	} 
  
	void insertNonFull(int ki) {
		int i = num_keys - 1;

		if (leaf == true) {
			while (i >= 0 && keys[i] > ki) {
				keys[i+1] = keys[i];
				i--;
			}

			keys[i+1] = ki;
			num_keys = num_keys + 1;

		} else {

			while (i >= 0 && keys[i] > ki) {
				i--;
			}

			if (Ch_ptr[i+1]->num_keys == 2*trange - 1) {
				splitChild(i+1, Ch_ptr[i+1]);

				if (keys[i+1] < ki) {
					i++;
				} 
			}

			Ch_ptr[i+1]->insertNonFull(ki);
		} 
	}

  
	void splitChild(int i, BNode* node) {
		BNode* node_1 = new BNode(node->trange, node->leaf);
		node_1->num_keys = trange - 1;

		for (int j = 0; j < trange - 1; j++) 
			node_1->keys[j] = node->keys[j+trange];

		if (node->leaf == false) 
	    { 
			for (int j = 0; j < trange; j++) 
				node_1->Ch_ptr[j] = node->Ch_ptr[j+trange]; 
	    } 
	  
		node->num_keys = trange - 1; 
	  
	    for (int j = num_keys; j >= i+1; j--) 
			Ch_ptr[j+1] = Ch_ptr[j]; 
	  
		Ch_ptr[i+1] = node_1; 
	  
		for (int j = num_keys-1; j >= i; j--) 
			keys[j+1] = keys[j]; 
	  
		keys[i] = node->keys[trange-1]; 
	  
		num_keys = num_keys + 1; 
	}
  
	void traverse() {
		int i;
		for (i = 0; i < num_keys; i++) {

			if (leaf == false) {
				Ch_ptr[i]->traverse();
			}

			cout << keys[i] << " ||| ";
		}

		if (leaf == false) {
			Ch_ptr[i]->traverse();
		}
	}
  
	BNode *search(int ki) {
		int i = 0;
		while (i < num_keys && ki > keys[i]) {
			i++;
		}

		if (keys[i] == ki) {
			return this;
		}

		if (leaf ==  true) {
			return NULL;
		}

		return Ch_ptr[i]->search(ki);
	}

	int findKey(int ki) {
		int i = 0; 

	    while (i < num_keys && keys[i] < ki) 
	        ++i; 
	    
	    return i; 
	}

	void remove(int ki) { 
		int i = findKey(ki); 
  
		if (i < num_keys && keys[i] == ki) { 
			if (leaf) 
				removeFromLeaf(i); 
			
			else
				removeFromNonLeaf(i); 
	    } else { 
	  
	        if (leaf) { 
	            cout << "The key "<< ki <<" is does not exist in the tree\n"; 
	            return; 
	        }

	        bool flag = ((i == num_keys)? true : false); 
	  
			if (Ch_ptr[i]->num_keys < trange) 
	            fill(i); 
	  
	        if (flag && i > num_keys) 
	            Ch_ptr[i-1]->remove(ki); 
	        
	        else
	            Ch_ptr[i]->remove(ki); 
	    } 
	    return; 
	}

	void removeFromLeaf (int index) { 
		for (int i = index + 1; i < num_keys; ++i) 
			keys[i-1] = keys[i]; 
	  
		num_keys--; 
	  
		return; 
	}

	void removeFromNonLeaf(int index) { 
	    int k = keys[index];

	    if (Ch_ptr[index]->num_keys >= trange) { 
	        int pred = getPred(index); 
	        keys[index] = pred; 
	        Ch_ptr[index]->remove(pred); 
	    
	    } else if (Ch_ptr[index + 1]->num_keys >= trange) { 
	        int succ = getSucc(index); 
	        keys[index] = succ; 
	        Ch_ptr[index + 1]->remove(succ); 
	    
	    } else { 
	        merge(index); 
	        Ch_ptr[index]->remove(k); 
	    }

	    return; 
	}

	int getPred(int index) {
		BNode *cur = Ch_ptr[index]; 
		while (!cur->leaf) 
			cur = cur->Ch_ptr[cur->num_keys]; 
	  
		return cur->keys[cur->num_keys-1]; 
	}

	int getSucc(int index) {
		BNode *cur = Ch_ptr[index+1]; 
		while (!cur->leaf) 
			cur = cur->Ch_ptr[0]; 
	  
		return cur->keys[0]; 
	}

	void fill(int index) { 
		if (index!=0 && Ch_ptr[index-1]->num_keys >= trange) 
			borrowFromPrev(index); 
	  
		else if (index != num_keys && Ch_ptr[index+1]->num_keys >= trange) 
			borrowFromNext(index); 
	  
		else { 
			if (index != num_keys) 
				merge(index); 
			
			else
				merge(index-1); 
		}

	    return; 
	}

	void borrowFromPrev(int index) { 
	    BNode* child = Ch_ptr[index]; 
	    BNode* sibling = Ch_ptr[index-1]; 
	  
		for (int i = child->num_keys-1; i >= 0; --i) 
			child->keys[i+1] = child->keys[i]; 
	  
		if (!child->leaf) { 
	        for(int i = child->num_keys; i>=0; --i) 
	            child->Ch_ptr[i+1] = child->Ch_ptr[i]; 
	    } 
	  
		child->keys[0] = keys[index-1]; 
	  
	    if(!child->leaf) 
			child->Ch_ptr[0] = sibling->Ch_ptr[sibling->num_keys]; 
	  
	    keys[index-1] = sibling->keys[sibling->num_keys-1];
	    
	    child->num_keys += 1; 
	    sibling->num_keys -= 1;

	    return; 
	}

	void borrowFromNext(int index) { 
	    BNode* child = Ch_ptr[index]; 
	    BNode* sibling = Ch_ptr[index+1]; 
	  
	    child->keys[(child->num_keys)] = keys[index]; 
	  
		if (!(child->leaf)) 
			child->Ch_ptr[(child->num_keys)+1] = sibling->Ch_ptr[0]; 
	  
		keys[index] = sibling->keys[0];
	  
		for (int i = 1; i < sibling->num_keys; ++i) 
			sibling->keys[i-1] = sibling->keys[i]; 
	  
		if (!sibling->leaf) { 
			for(int i = 1; i <= sibling->num_keys; ++i) 
				sibling->Ch_ptr[i-1] = sibling->Ch_ptr[i]; 
		}
	  
		child->num_keys += 1; 
		sibling->num_keys -= 1;

	    return; 
	}

	void merge(int index) { 
	    BNode* child = Ch_ptr[index]; 
		BNode* sibling = Ch_ptr[index+1]; 
	  
		child->keys[trange-1] = keys[index]; 
	  
		for (int i = 0; i < sibling->num_keys; ++i) 
			child->keys[i+trange] = sibling->keys[i]; 
	  
		if (!child->leaf) { 
			for(int i = 0; i <= sibling->num_keys; ++i) 
				child->Ch_ptr[i+trange] = sibling->Ch_ptr[i]; 
	    } 
	  
	    for (int i = index + 1; i < num_keys; ++i) 
			keys[i-1] = keys[i]; 
	  
		for (int i = index + 2; i <= num_keys; ++i) 
			Ch_ptr[i-1] = Ch_ptr[i]; 
	  
		child->num_keys += sibling->num_keys + 1; 
	    num_keys--; 
	  
	    delete(sibling); 
	    return; 
	}
};
