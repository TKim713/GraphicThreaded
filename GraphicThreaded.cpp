#include <algorithm>
#include <cstdio>
#include <graphics.h>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

#define NODE_SIZE 17

const int x = 600;
const int y = 200;
const int temp = 30;
int count = 0;

struct NODE {
    bool LTAG, RTAG;
    int INFO;
    int level;
    NODE* LLINK;
    NODE* RLINK;
    int x, y;
}*root;

struct ThreadedBinaryTree {
    void init() {
        root = nullptr;
    }

    // Node info for Graphics
    void NodeInfo(NODE* root, int a, int b, int noderatio, int key, int level, int temp) {
        root->x = a;
        root->y = b;
        root->level = level;
        level++;
        if (root->LLINK != nullptr && root->LTAG == false) {
            if (root->level == 0)
                NodeInfo(root->LLINK, a - temp * noderatio - 45, b + 90, noderatio - 1, key, level, temp - 10);
            else NodeInfo(root->LLINK, a - temp * noderatio + 5, b + 90, noderatio - 1, key, level, temp - 5);
        }
        if (root->RLINK != nullptr && root->RTAG == false) {
            if (root->level == 0)
                NodeInfo(root->RLINK, a + temp * noderatio + 45, b + 90, noderatio - 1, key, level, temp - 10);
            else NodeInfo(root->RLINK, a + temp * noderatio - 5, b + 90, noderatio - 1, key, level, temp - 5);
        }
    }

    // Draw Node with changeable color
    void DrawNodeColor(int a, int b, int key, int color) {
        setcolor(color);
        settextstyle(10, HORIZ_DIR, 2);
        setfillstyle(SOLID_FILL, color);
        bar(a - NODE_SIZE, b - NODE_SIZE, a + NODE_SIZE, b + NODE_SIZE);

        stringstream ss;
        ss << key;
        string s1 = ss.str();
        char arr[10] = "0";
        for (int i = 0; i < s1.length(); i++)
            arr[i] = s1[i];
        arr[s1.length()] = '\0';
        if (key >= 10)
            outtextxy(a - 10, b - 8, arr);
        else outtextxy(a - 5, b - 8, arr);
    }

    // Function to draw THREADED Node
    void DrawSquareNode(NODE* root, int a, int b, int noderatio) {
        setlinestyle(0, 0, 1);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        bar(a - NODE_SIZE, b - NODE_SIZE, a + NODE_SIZE, b + NODE_SIZE);
        
        setcolor(WHITE);
        rectangle(a - NODE_SIZE * 3, b - NODE_SIZE, a - NODE_SIZE, b + NODE_SIZE);
        rectangle(a + NODE_SIZE, b - NODE_SIZE, a + NODE_SIZE * 3, b + NODE_SIZE);

        // Head Node
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        bar(x + 10 - NODE_SIZE, y - 100 - NODE_SIZE, x + 10 + NODE_SIZE, y - 100 + NODE_SIZE);
        
        setcolor(WHITE);
        rectangle(x + 10 - NODE_SIZE * 3, y - 100 - NODE_SIZE, x + 10 - NODE_SIZE, y - 100 + NODE_SIZE);
        rectangle(x + 10 + NODE_SIZE, y - 100 - NODE_SIZE, x + 10 + NODE_SIZE * 3, y - 100 + NODE_SIZE);
        
        setcolor(LIGHTRED);
        setlinestyle(3, 0, 1);
        line(x + 10 + NODE_SIZE * 2, y - 100, x + 10 + NODE_SIZE * 2, y - 150);
        line(x + 10 + NODE_SIZE * 2, y - 150, x + 10, y - 150);
        line(x + 10, y - 150, x + 10, y - 105 - NODE_SIZE);
        line(x + 10, y - 105 - NODE_SIZE, x + 15, y - 110 - NODE_SIZE);
        line(x + 10, y - 105 - NODE_SIZE, x + 5, y - 110 - NODE_SIZE);

        setcolor(LIGHTGREEN);
        setlinestyle(0, 0, 1);
        line(x + 10 - NODE_SIZE * 2, y - 100, x, y - NODE_SIZE);

        setcolor(WHITE);
        stringstream ss;
        ss << root->INFO;
        string s1 = ss.str();
        char arr[10] = "0";
        for (int i = 0; i < s1.length(); i++)
            arr[i] = s1[i];
        arr[s1.length()] = '\0';
        if (root->INFO >= 10)
            outtextxy(a - 10, b - 8, arr);
        else outtextxy(a - 5, b - 8, arr);
        
        // Head Node thread
        if (root->LLINK == nullptr) {
            setcolor(LIGHTRED);
            setlinestyle(3, 0, 1);
            line(a - NODE_SIZE * 2, b, a - NODE_SIZE * 2, y);
            line(a - NODE_SIZE * 2, y, x + 10 - NODE_SIZE * 3, y - 100);
        }
        if (root->RLINK == nullptr) {
            setcolor(LIGHTRED);
            setlinestyle(3, 0, 1);
            line(a + NODE_SIZE * 2, b, a + NODE_SIZE * 2, y);
            line(a + NODE_SIZE * 2, y, x + 15 + NODE_SIZE * 3, y - 100);
        }

        // Draw Thread
        if (root->LLINK != nullptr) {
            if (root->LTAG == false) {
                setlinestyle(0, 0, 1);
                setcolor(LIGHTGREEN);
                line(a - NODE_SIZE * 2, b, root->LLINK->x, root->LLINK->y - NODE_SIZE);
                DrawSquareNode(root->LLINK, root->LLINK->x, root->LLINK->y, noderatio - 2);
            }
            else {
                setcolor(LIGHTRED);
                setlinestyle(3, 0, 1);
                line(a - NODE_SIZE * 2, b, root->LLINK->x, root->LLINK->y + NODE_SIZE);
            }
        }
        if (root->RLINK != nullptr) {
            if (root->RTAG == false) {
                setlinestyle(0, 0, 1);
                setcolor(LIGHTGREEN);
                line(a + NODE_SIZE * 2, b, root->RLINK->x, root->RLINK->y - NODE_SIZE);
                DrawSquareNode(root->RLINK, root->RLINK->x, root->RLINK->y, noderatio - 2);
            }
            else {
                setcolor(LIGHTRED);
                setlinestyle(3, 0, 1);
                line(a + NODE_SIZE * 2, b, root->RLINK->x, root->RLINK->y + NODE_SIZE);
            }
        }
    }

    // Node Comparison
    void CompareNode(NODE* root, int a, int b, int key) {
        setcolor(WHITE);
        if (key > root->INFO) {
            DrawNodeColor(a, b, key, 15);
            outtextxy(a + 100, b - 10,(char*) ">");
            DrawNodeColor(a + 200, b, root->INFO, 15);
            DrawNodeColor(root->x, root->y, root->INFO, 11);
            delay(1000);
            if (root->RTAG == false) {
                setlinestyle(0, 0, 1);
                setcolor(LIGHTCYAN);
                line(root->x + NODE_SIZE * 2, root->y, root->RLINK->x, root->RLINK->y - NODE_SIZE);
                delay(1000);
            }
        }
        else if (key < root->INFO) {
            DrawNodeColor(a, b, key, 15);
            outtextxy(a + 100, b - 10,(char*) "<");
            DrawNodeColor(a + 200, b, root->INFO, 15);
            DrawNodeColor(root->x, root->y, root->INFO, 11);
            delay(1000);
            if (root->LTAG == false) {
                setlinestyle(0, 0, 1);
                setcolor(LIGHTCYAN);
                line(root->x - NODE_SIZE * 2, root->y, root->LLINK->x, root->LLINK->y - NODE_SIZE);
                delay(1000);
            }
        }
        else {
            outtextxy(a + 100, b - 10,(char*) "=");
            DrawNodeColor(root->x, root->y, key, 11);
            DrawNodeColor(a + 200, b, root->INFO, 15);
        }
    }

    // Function to move node
    void MoveNode(NODE* root, int a, int b, int key) {
        setcolor(WHITE);
        DrawNodeColor(a, b, key, 15);
        char* node;
        int n = imagesize(a - NODE_SIZE, b - NODE_SIZE, a + NODE_SIZE, b + NODE_SIZE);
        node = (char*)malloc(n);
        getimage(a - NODE_SIZE, b - NODE_SIZE, a + NODE_SIZE, b + NODE_SIZE, node);
        
        // Move down
        for (int j = 0; j <= (root->y - b); j += 1)
        {
            putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
            b += j;
            putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
            delay(30);
        }

        // Move to position
        if (root->x > a) {
            for (int i = 0; i <= (root->x - a); i += 3) {
                putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
                a += i;
                putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
                delay(75);
            }
        }
        else {
            for (int i = 0; i <= (a - root->x); i += 3) {
                putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
                a -= i;
                putimage(a - NODE_SIZE, b - NODE_SIZE, node, XOR_PUT);
                delay(75);
            }
        }
    }

    // Function to draw THREAD tree
    void DrawThreadedTree(NODE* root, int a, int b, int noderatio, int key) {
        cleardevice();

        setcolor(LIGHTGREEN);
        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(240, 650,(char*) "LLINK / RLINK : ");
        setlinestyle(0, 0, 1);
        line(460, 660, 510, 660);

        setcolor(LIGHTRED);
        setlinestyle(3, 0, 1);
        outtextxy(755, 650,(char*) "LTAG / RTAG : ");
        line(955, 660, 1005, 660);
        
        setlinestyle(0, 0, 1);
        settextstyle(10, HORIZ_DIR, 2);
        DrawSquareNode(root, a, b, noderatio);
    }

    // Function to insert element
    NODE* insert(NODE* root, int key) {
        // Searching for a Node with given value
        NODE* ptr = root;
        NODE* par = nullptr; // Parent of key to be inserted
        while (ptr != nullptr) {
            CompareNode(ptr, x - 500, y - 150, key);
            // If key already exists, return
            if (key == (ptr->INFO)) {
                DrawNodeColor(x - 500, y - 70, key, 15);
                setcolor(LIGHTRED);
                outtextxy(x - 450, y - 80,(char*) "already exists!");
                cout << "\n\tValue already exists!" << endl;
                setcolor(LIGHTGREEN);
                outtextxy(470, 600,(char*) "Press any key to return...");
                getch();
                return root;
            }

            par = ptr; // Update parent pointer

            // Moving on left subtree.
            if (key < ptr->INFO) {
                if (ptr->LTAG == false)
                    ptr = ptr->LLINK;
                else break;
            }

            // Moving on right subtree.
            else {
                if (ptr->RTAG == false)
                    ptr = ptr->RLINK;
                else break;
            }
        }

        // Create a new node
        NODE* tmp = new NODE;
        tmp->INFO = key;
        tmp->LTAG = true;
        tmp->RTAG = true;

        if (par == nullptr) {
            root = tmp;
            tmp->LLINK = nullptr;
            tmp->RLINK = nullptr;
        }
        else if (key < (par->INFO)) {
            tmp->LLINK = par->LLINK;
            tmp->RLINK = par;
            par->LTAG = false;
            par->LLINK = tmp;
        }
        else {
            tmp->LLINK = par;
            tmp->RLINK = par->RLINK;
            par->RTAG = false;
            par->RLINK = tmp;
        }
        NodeInfo(root, x, y, 8, key, 0, temp);
        MoveNode(tmp, x - 500, y - 150, key);
        ::count++;
        return root;
    }

    // Function to search element
    NODE* search(NODE* root, int key) {
        NODE* curr = root;
        while (curr != nullptr) {
            CompareNode(curr, x - 500, y - 150, key);
            if (curr->INFO == key) {
                DrawNodeColor(x - 500, y - 70, key, 15);
                setcolor(LIGHTGREEN);
                outtextxy(x - 450, y - 80,(char*) "found!");
                return curr;
            }
            // Check left Node
            else if (key < curr->INFO) {
                if (curr->LTAG == false)
                    curr = curr->LLINK;
                else break;
            }
            // Check right Node
            else {
                if (curr->RTAG == false)
                    curr = curr->RLINK;
                else break;
            }
        }
        // Node not found
        DrawNodeColor(x - 500, y - 70, key, 15);
        setcolor(LIGHTRED);
        outtextxy(x - 450, y - 80,(char*) "not found!");
        return nullptr;
    }
    
    NODE* inorderSuccessor(NODE* ptr) {
        setcolor(LIGHTCYAN);
        // If rthread is set, we can quickly find
        if (ptr->RTAG == true) {
            setlinestyle(3, 0, 1);
            if (ptr->RLINK != nullptr) {
                line(ptr->x + NODE_SIZE * 2, ptr->y, ptr->RLINK->x, ptr->RLINK->y + NODE_SIZE);
                delay(1000);
            }
            return ptr->RLINK;
        }

        // Else return leftmost child of right subtree
        setlinestyle(0, 0, 1);
        line(ptr->x + NODE_SIZE * 2, ptr->y, ptr->RLINK->x, ptr->RLINK->y - NODE_SIZE);
        delay(1000);
        ptr = ptr->RLINK;
        while (ptr->LTAG == false) {
            setlinestyle(0, 0, 1);
            line(ptr->x - NODE_SIZE * 2, ptr->y, ptr->LLINK->x, ptr->LLINK->y - NODE_SIZE);
            delay(1000);
            ptr = ptr->LLINK;
        }
        return ptr;
    }

    // Printing the threaded tree
    void Inorder(NODE* root) {
        int i = 0;
        if (root == nullptr) {
            cout << "\nTree is Empty";
            outtextxy(400, 10,(char*) "Tree is Empty");
        }
        setcolor(WHITE);
        settextstyle(10, HORIZ_DIR, 2);
        outtextxy(10, 10,(char*) "Inorder Traversal:");
        // Reach leftmost node
        NODE* ptr = root;
        while (ptr->LTAG == false) {
            setlinestyle(0, 0, 1);
            setcolor(LIGHTCYAN);
            line(ptr->x - NODE_SIZE * 2, ptr->y, ptr->LLINK->x, ptr->LLINK->y - NODE_SIZE);
            ptr = ptr->LLINK;
            delay(1000);
        }

        // One by one print successors
        while (ptr != nullptr) {
            setcolor(WHITE);
            stringstream ss;
            ss << ptr->INFO;
            string s1 = ss.str();
            char arr[10] = "0";
            for (int i = 0; i < s1.length(); i++)
                arr[i] = s1[i];
            arr[s1.length()] = '\0';
            outtextxy(10 + i, 50, arr);
            i += 50;
            //To mau node
            DrawNodeColor(ptr->x, ptr->y, ptr->INFO, 11);
            cout << ptr->INFO << " ";
            delay(1000);
            ptr = inorderSuccessor(ptr);
        }
    }

    NODE*preorderSuccessor(NODE *ptr) {
        if (ptr->LTAG == false) {
            setlinestyle(0, 0, 1);
            line(ptr->x - NODE_SIZE * 2, ptr->y, ptr->LLINK->x, ptr->LLINK->y - NODE_SIZE);
            delay(1000);
            return ptr->LLINK;
        }
        else if (ptr->RTAG == false) {
            setlinestyle(0, 0, 1);
            line(ptr->x + NODE_SIZE * 2, ptr->y, ptr->RLINK->x + 5, ptr->RLINK->y - 30 + NODE_SIZE);
            delay(1000);
            return ptr->RLINK;
        }
        else {
            while (ptr->RLINK != nullptr && ptr->RTAG == true) {
                setlinestyle(3, 0, 1);
                line(ptr->x + NODE_SIZE * 2, ptr->y, ptr->RLINK->x, ptr->RLINK->y + NODE_SIZE);
                ptr = ptr->RLINK;
                delay(1000);
            }        
            if (ptr->RLINK != nullptr) {
                setlinestyle(0, 0, 1);
                line(ptr->x + NODE_SIZE * 2, ptr->y, ptr->RLINK->x, ptr->RLINK->y - NODE_SIZE);
                delay(1000);
            }
            return ptr->RLINK;
        }
    }

    void Preorder(NODE* root) {
        NODE* ptr;
        int i=0;
        if (root == nullptr) {
            cout << "Tree is empty\n";
            outtextxy(400, 10,(char*) "Tree is Empty");
            return;
        }
        setcolor(WHITE);
        settextstyle(10, HORIZ_DIR, 2);
        outtextxy(10, 10,(char*) "Preorder Traversal:");
        ptr = root;
        while (ptr != nullptr) {
            setcolor(WHITE);
            stringstream ss;
            ss << ptr->INFO;
            string s1 = ss.str();
            char arr[10] = "0";
            for (int i = 0; i < s1.length(); i++)
                arr[i] = s1[i];
            arr[s1.length()] = '\0';
            outtextxy(10 + i, 50, arr);
            i += 50;
            //To mau node
            DrawNodeColor(ptr->x, ptr->y, ptr->INFO, 11);
            cout << ptr->INFO << " ";
            delay(1000);
            ptr = preorderSuccessor(ptr);
        }
    }

    NODE* PostorderNextNode(NODE* P)
    {
        // Return left child of left subtree
        if (P->LLINK == nullptr && P->LTAG == true) {
            return P->LLINK;
        }
        else {
            while (P->LLINK != nullptr) {
                if (P->LTAG == true) {
                    setcolor(LIGHTCYAN);
                    setlinestyle(3, 0, 1);
                    line(P->x - NODE_SIZE * 2, P->y, P->LLINK->x, P->LLINK->y + NODE_SIZE);
                    P = P->LLINK;
                    delay(1000);
                }
                else if (P->LTAG == false) {
                    setlinestyle(0, 0, 1);
                    setcolor(LIGHTCYAN);
                    line(P->x - NODE_SIZE * 2, P->y, P->LLINK->x, P->LLINK->y - NODE_SIZE);
                    delay(1000);
                    return P->LLINK;
                }
            }
        }
        return P;
    }

    void Postorder(NODE* root, int count) {
        int arr[100], cnt = 0, i = 0;
        if (root == nullptr) {
            cout << "Tree is empty\n";
            return;
        }
        setcolor(WHITE);
        settextstyle(10, HORIZ_DIR, 2);
        outtextxy(10, 10,(char*) "Postorder Traversal:");
        NODE* P = root;
        while (P != nullptr) {
            // In so
            setcolor(WHITE);
            stringstream ss1;
            ss1 << P->INFO;
            string s1 = ss1.str();
            char key1[10] = "0";
            for (int i = 0; i < s1.length(); i++)
                key1[i] = s1[i];
            key1[s1.length()] = '\0';
            outtextxy(10 + 50 * (count - 1) + i, 50, key1);
            
            // To mau node
            DrawNodeColor(P->x, P->y, P->INFO, 11);
            delay(1000);
            i -= 50;
            
            arr[cnt] = P->INFO;
            cnt++;
            while (P->RTAG == false) {
                // To mau day
                setlinestyle(0, 0, 1);
                setcolor(LIGHTCYAN);
                line(P->x + NODE_SIZE * 2, P->y, P->RLINK->x, P->RLINK->y - NODE_SIZE);
                delay(1000);

                // In so
                P = P->RLINK;
                setcolor(WHITE);
                stringstream ss2;
                ss2 << P->INFO;
                string s2 = ss2.str();
                char key2[10] = "0";
                for (int i = 0; i < s2.length(); i++)
                    key2[i] = s2[i];
                key2[s1.length()] = '\0';
                outtextxy(10 + 50 * (count - 1) + i, 50, key2);
                
                // To mau node
                DrawNodeColor(P->x, P->y, P->INFO, 11);
                delay(1000);
                i -= 50;
                
                arr[cnt] = P->INFO;
                cnt++;
            }
            P = PostorderNextNode(P);
        }
        arr[cnt] = '\0';
        for (int i = cnt - 1; i >= 0; i--)
            cout << arr[i] << " ";
    }
};

// Function to check the input
bool CheckInput(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

// Function to validate Threaded Binary Tree
bool Validate(string str) {
    if (CheckInput(str))
        return true;
    return false;
}

int main()
{
    ThreadedBinaryTree tbt;
    int choice, item, bf;
    string str;
    cout << "Threaded Binary Tree Graphics\n";

    // Graphics
    int gd = DETECT;
    int gm;
    initwindow(1200, 700, "Threaded Binary Tree Graphics", 0, 0, false, true);
    
    // In tren man hinh console
    cout << "\n-----------------------------------" << endl;
    cout << "Threaded Binary Tree Implementation" << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. Insert Element into the tree" << endl;
    cout << "2. Search Tree" << endl;
    cout << "3. PreOrder traversal" << endl;
    cout << "4. InOrder traversal" << endl;
    cout << "5. PostOrder traversal" << endl;
    cout << "6. Exit" << endl;

Menu:
    cout << "\nEnter Your Choice: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        // Accept input as string
        cout << "\nEnter the value to be inserted: ";
        cin >> str;

        // Function call to check if input is valid or not
        bool c = Validate(str);

        if (c == true) {
            item = std::stoi(str);
            root = tbt.insert(root, item);
            settextstyle(10, HORIZ_DIR, 3);
            tbt.DrawThreadedTree(root, x, y, 8, item);
        }
        else cout << "\n\t\tInvalid Input!" << endl;
        goto Menu;
    }
    case 2: {
        if (root == nullptr) {
            cout << "\nTree is Empty";
            outtextxy(10, 10,(char*) "Tree is Empty");
        }
        else {
            cout << "\nEnter the value to be search: ";
            cin >> str;

            // Function call to check if input is valid or not
            bool c = Validate(str);

            if (c == true) {
                item = std::stoi(str);
                tbt.DrawThreadedTree(root, x, y, 8, item);
                NODE *temp = tbt.search(root, item);
                if (temp != nullptr && temp->INFO == item) {
                    cout << "\nElement " << item << " found in the tree";
                }
                else cout << "\nElement " << item << " not found in the tree";
            }
            setcolor(LIGHTGREEN);
            outtextxy(470, 600,(char*) "Press any key to return...");
            getch();
            cleardevice();
            tbt.DrawThreadedTree(root, x, y, 8, item);
        }
        goto Menu;
    }
    case 3: {
       if (root == nullptr) {
            cout << "\nTree is Empty";
            outtextxy(10, 10,(char*) "Tree is Empty");
        }
        else {
            tbt.DrawThreadedTree(root, x, y, 8, item);
            delay(500);
            cout << "\nPreorder Traversal:" << endl;
            tbt.Preorder(root);
            cout << endl;
        }
        setcolor(LIGHTGREEN);
        outtextxy(470, 600,(char*) "Press any key to return...");
        getch();
        cleardevice();
        tbt.DrawThreadedTree(root, x, y, 8, item);
        goto Menu;
    }
    case 4: {
        if (root == nullptr) {
            cout << "\nTree is Empty";
            outtextxy(10, 10,(char*) "Tree is Empty");
        }
        else {
            tbt.DrawThreadedTree(root, x, y, 8, item);
            delay(500);
            cout << "\nInorder Traversal:" << endl;
            tbt.Inorder(root);
            cout << endl;
        }
        setcolor(LIGHTGREEN);
        outtextxy(470, 600,(char*) "Press any key to return...");
        getch();
        cleardevice();
        tbt.DrawThreadedTree(root, x, y, 8, item);
        goto Menu;
    }
    case 5: {
        cout << "\nPostorder Traversal:" << endl;
        tbt.Postorder(root, ::count);
        cout << endl;
        setcolor(LIGHTGREEN);
        outtextxy(470, 600,(char*) "Press any key to return...");
        getch();
        cleardevice();
        tbt.DrawThreadedTree(root, x, y, 8, item);
        goto Menu;
    }
    case 6: {
        break;
    }
    default: {
        cout << "\n\t\tInvalid Input! Try again!";
        goto Menu;
    }
    }
    closegraph();
    return 0;
}