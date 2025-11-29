#include <iostream>
#include <cmath>
using namespace std;



struct Node {
    double value;
    Node *up, *down, *left, *right;

    Node(double val = 0) : value(val), up(NULL), down(NULL), left(NULL), right(NULL) {}
};


Node* buildMatrix(int n) {
    Node* head = NULL;
    Node* prevRowHead = NULL;

    for (int i = 0; i < n; i++) {
        Node* rowHead = NULL;
        Node* prev = NULL;

        for (int j = 0; j < n; j++) {
            Node* cur = new Node(0);

            if (!rowHead) rowHead = cur;
            if (!head) head = rowHead;


            if (prev) {
                prev->right = cur;
                cur->left = prev;
            }
            prev = cur;


            if (prevRowHead) {
                Node* upNode = prevRowHead;
                for (int k = 0; k < j; k++) upNode = upNode->right;

                upNode->down = cur;
                cur->up = upNode;
            }
        }
        prevRowHead = rowHead;
    }
    return head;
}

Node* get(Node* head, int i, int j) {
    Node* p = head;
    for (int k = 0; k < i; k++) p = p->down;
    for (int k = 0; k < j; k++) p = p->right;
    return p;
}


void printMatrix(Node* head, int n) {
    Node* row = head;
    for (int i = 0; i < n; i++) {
        Node* col = row;
        for (int j = 0; j < n; j++) {
            cout << col->value << "\t";
            col = col->right;
        }
        cout << endl;
        row = row->down;
    }
}


void LU(Node* L, Node* U, int n) {
    for (int k = 0; k < n; k++) {
        Node* Ukk = get(U, k, k);
        if (fabs(Ukk->value) < 1e-12) {
            cout << "Error: zero pivot!\n";
            exit(1);
        }

        for (int i = k + 1; i < n; i++) {
            Node* Uik = get(U, i, k);
            Node* Lik = get(L, i, k);

            double factor = Uik->value / Ukk->value;
            Lik->value = factor;

            for (int j = k; j < n; j++) {
                Node* Uij = get(U, i, j);
                Node* Ukj = get(U, k, j);

                Uij->value -= factor * Ukj->value;
            }
        }
    }
}


int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;


    Node* A = buildMatrix(n);
    Node* L = buildMatrix(n);
    Node* U = buildMatrix(n);


    cout << "Enter matrix A:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            get(A, i, j)->value = get(U, i, j)->value = ({
                double x; cin >> x; x;
            });

    for (int i = 0; i < n; i++)
        get(L, i, i)->value = 1;

    LU(L, U, n);


    cout << "\nMatrix L:\n";
    printMatrix(L, n);

    cout << "\nMatrix U:\n";
    printMatrix(U, n);

    return 0;
}
