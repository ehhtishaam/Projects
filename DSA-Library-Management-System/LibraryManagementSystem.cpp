// Online Library Management using Binary Search Tree
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// BOOK STRUCTURE (data stored in each BST node)
struct Book 
{
    long long isbn;
    string title;
    string author;
    string genre;
    int year;
};

// BST NODE
struct Node 
{
    Book data;
    Node* left;
    Node* right;

    Node(Book b) : data(b), left(nullptr), right(nullptr) {}
};

// BINARY SEARCH TREE CLASS
class BST 
{
private:
    Node* root;
    int count;

    // helper: find minimum node in a subtree (used in delete)
    Node* minNode(Node* node) 
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // recursive delete
    Node* deleteNode(Node* node, long long isbn, bool& deleted) 
    {
        if (node == nullptr) 
        {
            deleted = false;
            return nullptr;
        }

        if (isbn < node->data.isbn) 
        {
            node->left = deleteNode(node->left, isbn, deleted);
        }
        else if (isbn > node->data.isbn) 
        {
            node->right = deleteNode(node->right, isbn, deleted);
        }
        else 
        {
            // FOUND — handle 3 cases

            // Case 1: Leaf node (no children)
            if (node->left == nullptr && node->right == nullptr) 
            {
                delete node;
                deleted = true;
                count--;
                return nullptr;
            }

            // Case 2a: Only right child
            if (node->left == nullptr) 
            {
                Node* temp = node->right;
                delete node;
                deleted = true;
                count--;
                return temp;
            }

            // Case 2b: Only left child
            if (node->right == nullptr) 
            {
                Node* temp = node->left;
                delete node;
                deleted = true;
                count--;
                return temp;
            }

            // Case 3: Two children
            // Find in-order successor (smallest in right subtree)
            Node* successor = minNode(node->right);
            // Copy successor data into current node
            node->data = successor->data;
            // Delete the successor from right subtree
            node->right = deleteNode(node->right, successor->data.isbn, deleted);
            // Note: count-- already happened inside the recursive call
        }
        return node;
    }

    // recursive traversals
    void inorder(Node* node) const 
    {
        if (node == nullptr) return;
        inorder(node->left);
        printBook(node->data);
        inorder(node->right);
    }

    void preorder(Node* node) const 
    {
        if (node == nullptr) return;
        printBook(node->data);
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const 
    {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        printBook(node->data);
    }

    // search by title helper
    void searchByTitleHelper(Node* node, const string& title, vector<Book>& results) const
    {
        if (node == nullptr) 
            return;

        searchByTitleHelper(node->left, title, results);
        
        string a = node->data.title, b = title;
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        transform(b.begin(), b.end(), b.begin(), ::tolower);
        if (a == b)
            results.push_back(node->data);

        searchByTitleHelper(node->right, title, results);
    }

    // traversal helpers for file save
    void collectInorder(Node* node, vector<Book>& books) const 
    {
        if (node == nullptr) return;
        collectInorder(node->left, books);
        books.push_back(node->data);
        collectInorder(node->right, books);
    }

    void collectPreorder(Node* node, vector<Book>& books) const
    {
        if (node == nullptr) return;
        books.push_back(node->data);
        collectPreorder(node->left, books);
        collectPreorder(node->right, books);
    }

    // calculate tree height
    int height(Node* node) const 
    {
        if (node == nullptr) return 0;
        int lh = height(node->left);
        int rh = height(node->right);
        return 1 + max(lh, rh);
    }

    // free all nodes (destructor helper)
    void freeTree(Node* node) 
    {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    // print one book row
    void printBook(const Book& b) const 
    {
        cout << left
             << setw(15) << b.isbn
             << setw(42) << b.title.substr(0, 40)
             << setw(25) << b.author.substr(0, 23)
             << setw(12) << b.genre
             << b.year
             << "\n";
    }

    // print table header
    void printHeader() const 
    {
        cout << string(105, '-') << "\n";
        cout << left
             << setw(15) << "ISBN"
             << setw(42) << "Title"
             << setw(25) << "Author"
             << setw(12) << "Genre"
             << "Year"
             << "\n";
        cout << string(105, '-') << "\n";
    }

public:
    BST() : root(nullptr), count(0) {}

    ~BST() { freeTree(root); }

    int size()       const { return count; }
    int treeHeight() const { return height(root); }
    bool isEmpty()   const { return root == nullptr; }

    //  INSERT — iterative
    //  Returns: true = success, false = duplicate ISBN
    bool insert(Book b) 
    {
        Node* newNode = new Node(b);

        if (root == nullptr) 
        {
            root = newNode;
            count++;
            return true;
        }

        Node* current = root;
        while (true) {
            if (b.isbn == current->data.isbn) 
            {
                delete newNode;
                return false;          // duplicate
            }
            else if (b.isbn < current->data.isbn) 
            {
                if (current->left == nullptr) 
                {
                    current->left = newNode;
                    count++;
                    return true;
                }
                current = current->left;
            }
            else 
            {
                if (current->right == nullptr) 
                {
                    current->right = newNode;
                    count++;
                    return true;
                }
                current = current->right;
            }
        }
    }

    //  SEARCH — iterative
    //  Returns: pointer to Node if found, nullptr otherwise
    //  Also returns number of comparisons made (steps)
    Node* search(long long isbn, int& steps) const 
    {
        Node* current = root;
        steps = 0;
        while (current != nullptr) 
        {
            steps++;
            if (isbn == current->data.isbn)
                return current;
            else if (isbn < current->data.isbn)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

    // Search by title
    void searchByTitle(const string& title) const
    {
        vector<Book> results;

        searchByTitleHelper(root, title, results);

        if (results.empty())
        {
            cout << "  No book found with title: " << title << "\n";
            return;
        }

        printHeader();

        for (auto& b : results)
            printBook(b);

        cout << string(105, '-') << "\n";
    }

    //  DELETE — recursive (3 cases)
    //  Returns: true = deleted, false = not found
    bool remove(long long isbn) 
    {
        bool deleted = false;
        root = deleteNode(root, isbn, deleted);
        return deleted;
    }

    //  DISPLAY ALL — in-order (sorted by ISBN)
    void displayAll() const 
    {
        if (isEmpty()) 
        {
            cout << "  Library is empty.\n";
            return;
        }
        printHeader();
        inorder(root);
        cout << string(105, '-') << "\n";
        cout << "  Total books: " << count
             << "\n  Tree height: " << treeHeight() << "\n";
    }

    //  DISPLAY PRE-ORDER
    void displayPreorder() const 
    {
        if (isEmpty()) 
        {
            cout << "  Library is empty.\n"; return; 
        }
        printHeader();
        preorder(root);
        cout << string(105, '-') << "\n";
    }

    //  DISPLAY POST-ORDER
    void displayPostorder() const 
    {
        if (isEmpty()) 
        {
            cout << "  Library is empty.\n"; return; 
        }
        printHeader();
        postorder(root);
        cout << string(105, '-') << "\n";
    }

    //  SAVE TO FILE
    bool saveToFile(const string& filename) const 
    {
        ofstream file(filename);
        if (!file.is_open()) return false;

        vector<Book> books;
        collectPreorder(root, books);

        for (auto& b : books) 
        {
            file << b.isbn  << "|"
                 << b.title  << "|"
                 << b.author << "|"
                 << b.genre  << "|"
                 << b.year   << "\n";
        }
        file.close();
        return true;
    }

    //  LOAD FROM FILE
    int loadFromFile(const string& filename) 
    {
        ifstream file(filename);
        if (!file.is_open()) return -1;   // file not found

        int loaded = 0;
        string line;
        while (getline(file, line)) 
        {
            if (line.empty()) continue;

            stringstream ss(line);
            string token;
            vector<string> parts;

            while (getline(ss, token, '|'))
                parts.push_back(token);

            if (parts.size() < 5) continue;   // skip malformed lines

            Book b;
            try 
            {
                b.isbn   = stoll(parts[0]);
                b.title  = parts[1];
                b.author = parts[2];
                b.genre  = parts[3];
                b.year   = stoi(parts[4]);
            } 
            catch (...) 
            {
                continue;   // skip lines that can't be parsed
            }

            if (insert(b)) loaded++;
        }
        file.close();
        return loaded;
    }
};

//  INPUT HELPERS
void clearInput() 
{
    cin.clear();
    cin.ignore(10000, '\n');
}

string getLine(const string& prompt) 
{
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

long long getLongLong(const string& prompt) 
{
    long long v;
    while (true) 
    {
        cout << prompt;
        if (cin >> v && v > 0) 
        {
            clearInput(); return v; 
        }
        cout << "  Invalid input. Please enter a positive number.\n";
        clearInput();
    }
}

int getInt(const string& prompt) 
{
    int v;
    while (true) 
    {
        cout << prompt;
        if (cin >> v) 
        {
            clearInput(); return v; 
        }
        cout << "  Invalid input.\n";
        clearInput();
    }
}

//  MENU FUNCTIONS
void printBanner() 
{
    cout << "\n";
    cout << "ONLINE LIBRARY MANAGEMENT SYSTEM" << "\n";
    cout << "\n";
}

void printMenu(int bookCount, int treeHeight) 
{
    cout << "\nMAIN MENU" << "\n";
    cout << "Books in library: " << setw(5) << left << bookCount << "\n";
    cout << "Tree height     : " << treeHeight << "\n";
    cout << "1. Insert a Book" << "\n";
    cout << "2. Search by ISBN" << "\n";
    cout << "3. Search by Title" << "\n";
    cout << "4. Delete a Book" << "\n";
    cout << "5. Display All Books (In-order / Sorted)" << "\n";
    cout << "6. Display Pre-order Traversal" << "\n";
    cout << "7. Display Post-order Traversal" << "\n";
    cout << "8. Save Library to File" << "\n";
    cout << "9. Load Library from File" << "\n";
    cout << "0. Exit & Save" << "\n";
    cout << "Enter choice: ";
}

// 1. INSERT
void menuInsert(BST& library) 
{
    cout << "\n  INSERT BOOK\n";
    Book b;
    b.isbn   = getLongLong("  ISBN   : ");
    b.title  = getLine    ("  Title  : ");
    b.author = getLine    ("  Author : ");
    b.genre  = getLine    ("  Genre  : ");
    b.year   = getInt     ("  Year   : ");

    if (library.insert(b)) 
    {
        cout << "  [OK] \"" << b.title << "\" inserted successfully.\n";
        cout << "  BST now has " << library.size() << " books.\n";
        cout << "  Current tree height: " << library.treeHeight() << "\n";
    } 
    else 
    {
        cout << "  [ERROR] ISBN " << b.isbn << " already exists in the library.\n";
    }
}

// 2. SEARCH by ISBN
void menuSearch(BST& library) 
{
    cout << "\n  SEARCH BY ISBN\n";
    long long isbn = getLongLong("  Enter ISBN: ");
    int steps = 0;
    Node* result = library.search(isbn, steps);

    cout << "  Comparisons made: " << steps << "\n";
    if (result) 
    {
        Book& b = result->data;
        cout << "  [FOUND]\n";
        cout << "  ISBN   : " << b.isbn << "\n";
        cout << "  Title  : " << b.title << "\n";
        cout << "  Author : " << b.author << "\n";
        cout << "  Genre  : " << b.genre << "\n";
        cout << "  Year   : " << b.year << "\n";
    } 
    else 
    {
        cout << "  [NOT FOUND] No book with ISBN " << isbn << ".\n";
    }
}

// 3. SEARCH by Title
void menuSearchByTitle(BST& library)
{
    cout << "\n  SEARCH BY TITLE\n";

    string title = getLine("  Enter title: ");

    library.searchByTitle(title);
}

// 4. DELETE
void menuDelete(BST& library) 
{
    cout << "\n  DELETE BOOK\n";
    long long isbn = getLongLong("  Enter ISBN to delete: ");

    // show book first so user knows what they are deleting
    int steps = 0;
    Node* found = library.search(isbn, steps);
    if (!found) 
    {
        cout << "  [NOT FOUND] No book with ISBN " << isbn << ".\n";
        return;
    }
    cout << "  Found: \"" << found->data.title << "\" by " << found->data.author << "\n";
    string confirm = getLine("  Confirm delete? (yes/no): ");
    if (confirm == "yes" || confirm == "y" || confirm == "YES") 
    {
        if (library.remove(isbn))
        {
            cout << "  [OK] Book deleted. Library now has " << library.size() << " books.\n";
            cout << "  Current tree height: " << library.treeHeight() << "\n";
        }
    } 
    else 
    {
        cout << "  Delete cancelled.\n";
    }
}

// 8. SAVE
void menuSave(BST& library) 
{
    cout << "\n  SAVE TO FILE\n";
    string filename = getLine("  Filename (default: library.txt): ");
    if (filename.empty()) filename = "library.txt";
    if (library.saveToFile(filename))
        cout << "  [OK] " << library.size() << " books saved to \"" << filename << "\".\n";
    else
        cout << "  [ERROR] Could not open file for writing.\n";
}

// 9. LOAD
void menuLoad(BST& library) 
{
    cout << "\n  LOAD FROM FILE\n";
    string filename = getLine("  Filename (default: library.txt): ");
    if (filename.empty()) filename = "library.txt";
    int loaded = library.loadFromFile(filename);
    if (loaded == -1)
    {
        cout << "  [ERROR] File \"" << filename << "\" not found.\n";
    }
    else
    {
        cout << "  [OK] " << loaded << " books loaded. Total: " << library.size() << "\n";
        cout << "  Current tree height: " << library.treeHeight() << "\n";
    }
}


//  MAIN
int main() 
{
    BST library;
    const string AUTO_SAVE_FILE = "library.txt";

    printBanner();

    // Auto-load on startup if file exists
    int autoLoaded = library.loadFromFile(AUTO_SAVE_FILE);
    if (autoLoaded > 0)
        cout << "  Auto-loaded " << autoLoaded
             << "  books from \"" << AUTO_SAVE_FILE << "\".\n";

    int choice = -1;

    while (choice != 0) 
    {
        printMenu(library.size(), library.treeHeight());

        if (!(cin >> choice)) 
        {
            clearInput();
            choice = -1;
        } 
        else 
        {
            clearInput();
        }

        switch (choice) 
        {
            case 1:  menuInsert(library);                    break;
            case 2:  menuSearch(library);                    break;
            case 3:  menuSearchByTitle(library);             break;
            case 4:  menuDelete(library);                    break;
            case 5:  library.displayAll();                   break;
            case 6:  library.displayPreorder();              break;
            case 7:  library.displayPostorder();             break;
            case 8:  menuSave(library);                      break;
            case 9:  menuLoad(library);                      break;
            case 0:
                cout << "\n  Saving library before exit...\n";
                if (library.saveToFile(AUTO_SAVE_FILE))
                    cout << "  [OK] " << library.size()
                         << "  books saved to \"" << AUTO_SAVE_FILE << "\".\n";
                cout << "  Goodbye!\n\n";
                break;
            default:
                cout << "  Invalid choice. Please enter 0-9.\n";
        }
    }

    return 0;
}