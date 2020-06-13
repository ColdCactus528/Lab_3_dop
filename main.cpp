#include "tree.cpp"

int main() {
	int flag_1 = 1;
	int flag_3 = 1;
	int data;
	int degree;

	cout << "Enter integer degree.\n";
	cin >> degree;
	BTree tree (degree);
	cout << "\n";

	while (flag_3 != 0) {
		int flag_0;
		cout << "Choose operation type:\n";
		cout << "1. Insert\n";
		cout << "2. Search\n";
		cout << "3. Remove\n";
		cin >> flag_0;
		cout << "\n";

		if (flag_0 == 1) {
			while (flag_1 != 0) {
				cout << "Enter integer data, that you want to add into the tree.\n";
				cin >> data;
				cout << "\n";
				tree.insert(data);
				cout << "Your tree -> ";
				tree.traverse();
				cout << "\n";

				cout << "If you don't want to add any data, enter 0.\n";
				cout << "If you want to continue add new data into the tree, enter any integer except 0\n";
				cin >> flag_1;
				cout << "\n";
			}
			flag_1 = 1;
		}

		if (flag_0 == 2) {
			while (flag_1 != 0) {
				cout << "Enter integer data, that you want to find in the tree.\n";
				cin >> data;
				cout << "\n";
				
				if (tree.search(data) != NULL)
					cout << "True\n";
				else 
					cout << "False\n";

				cout << "Your tree -> ";
				tree.traverse();
				cout << "\n";

				cout << "If you don't want to find any data, enter 0.\n";
				cout << "If you want to continue searching data in the tree, enter any integer except 0\n";
				cin >> flag_1;
				cout << "\n";
			}
			flag_1 = 1;
		}

		if (flag_0 == 3) {
			while (flag_1 != 0) {
				cout << "Enter integer data, that you want to remove from the tree.\n";
				cin >> data;
				cout << "\n";
				tree.remove(data);
				cout << "Your tree -> ";
				tree.traverse();
				cout << "\n";

				cout << "If you don't want to remove any data, enter 0.\n";
				cout << "If you want to continue remove data into the tree, enter any integer except 0\n";
				cin >> flag_1;
				cout << "\n";
			}
			flag_1 = 1;
		}

	cout << "If you want to exit, enter 0, else enter any integer except 0\n";
	cin >> flag_3;
	}
	return 0;
}
