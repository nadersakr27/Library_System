#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
const int maxbooks = 1000;
const int maxuser = 1000;
vector<string> nammesuseer;

struct book {

    string name;
    int id;
    int quantity;
    vector<string> bro;

    book() {
        name = "";
        id = 0;
        quantity = 0;
    }

    void addbook() {

        cout << "Enter ID, name and quantity of book : " << "\n";
        cin >> id >> name >> quantity;
    }
};

struct user {
    string name;
    int userid;

    user() {
        name = "";
        userid = 0;
    }

    void adduser() {
        cout << "Enter name of user and ID of user: " << "\n";
        cin >> name >> userid;
    }
};

bool compa(book &a, book &b) {
    return a.name < b.name;
}

bool compaid(book &a, book &b) {
    return a.id < b.id;
}

struct lib {
    user users[maxuser];
    book libbooks[maxbooks];
    int len = 0;
    int lenu = 0;

    void addbooks() {
        libbooks[len++].addbook();
        cout << "Successful Addition.\n";
    }

    void searchpr() {
        cout << "Enter the prefix: \n";
        string p;
        cin >> p;
        bool found = false;
        for (int i = 0; i < len; ++i) {
            string prname = libbooks[i].name;
            auto f = prname.find(p);
            if (f != std::string::npos) {
                found = true;
                cout << prname << "\n";
            }
        }
        if (!found) {
            cout << "There is no book with prefix " << p << "\n";
        }
    }

    int searbookname(string &pe) {
        for (int i = 0; i < len; ++i) {
            if (pe == libbooks[i].name) {
                return i;
            }
        }
        return -1;
    }

    int searchuser(string &namee) {
        for (int i = 0; i < len; ++i) {
            if (namee == users[i].name) {
                return i;
            }
        }
        return -1;
    }

    void printbooks() {
        for (int i = 0; i < len; ++i) {
            cout << "Name : " << libbooks[i].name << " ,Id : " << libbooks[i].id << " ,Quantity : "
                 << libbooks[i].quantity << " ,Borrow : " << libbooks[i].bro.size() << " ";
            if (!libbooks[i].bro.empty()) { cout << "with names : \n"; }
            int ew = 1;
            for (auto &w: libbooks[i].bro) {
                cout << ew << ") " << w << " ";
            }
            cout << '\n';
        }
    }

    void adduser() {
        users[lenu++].adduser();
        cout << "Successful Addition.\n";
    }

    void printusers() {
        for (int i = 0; i < lenu; ++i) {
            cout << "Name : " << users[i].name << " Id : " << users[i].userid << "\n";
        }
    }
};

void prsortname(lib libb) {
    if(libb.len==0){cout <<"There are no books ,now.\n";}
    sort(libb.libbooks, libb.libbooks + libb.len, compa);
    libb.printbooks();
}

void prsortid(lib libb) {
    if(libb.len==0){cout <<"There are no books ,now.\n";}
    sort(libb.libbooks, libb.libbooks + libb.len, compaid);
    libb.printbooks();
}

void printwhob() {
    for (auto &i: nammesuseer) {
        cout << i << " ";
    }
    cout << "\n";
}

void userborrow(lib &lib1) {
    cout << "Enter the name of User and the name of the book : " << "\n";
    string username;
    cin >> username;
    string bookname;
    cin >> bookname;
    int help = lib1.searbookname(bookname);
    int ee = lib1.searchuser(username);
    if (help == -1) {
        cout << "There is no book with this name. " << "\n";
    } else if (ee == -1) {
        cout << "There is no user with this name. " << "\n";
    } else {
        nammesuseer.push_back(username);
        lib1.libbooks[help].bro.push_back(username);
        cout << "Successful Borrowing.\n";
    }
}

void returnbook(lib &lib1) {
    cout << "Enter the name of User and the name of the book : " << "\n";
    string username;
    cin >> username;
    string bookname;
    cin >> bookname;
    int help = lib1.searbookname(bookname);
    int ee = lib1.searchuser(username);

    if (help == -1) {
        cout << "There is no book with this name. " << "\n";
    } else if (ee == -1) {
        cout << "There is no user with this name. " << "\n";
    } else {
        auto er = std::find(lib1.libbooks[help].bro.begin(), lib1.libbooks[help].bro.end(), bookname);
        if (er == lib1.libbooks[help].bro.end()) {
            cout << "This user did not borrow this book \n";
            return;
        }
        auto fn = std::find(nammesuseer.begin(), nammesuseer.end(), username);
        nammesuseer.erase(fn);
        auto f = std::find(lib1.libbooks[help].bro.begin(), lib1.libbooks[help].bro.end(), username);
        lib1.libbooks[help].bro.erase(f);
        cout << "Successful Returning.\n";
    }

}

int main() {
    lib libe;
    cout
            << "Enter choise from [1 : 10] : \n1) Add Book\n2) Search Books by prefix\n3) Print who borrowed by name\n4) Print boosk by id \n5) Print boosk by name \n6) Add user\n7) User borrow book\n8) User return book \n9) Print Users\n10) Exit\n";
    int choise;
    bool k = true;
    while (k) {
        cin >> choise;
        if (choise == 1) {
            libe.addbooks();
        } else if (choise == 2) {
            libe.searchpr();
        } else if (choise == 3) {
            printwhob();
        } else if (choise == 4) {
            prsortname(libe);
        } else if (choise == 5) {
            prsortid(libe);
        } else if (choise == 6) {
            libe.adduser();
        } else if (choise == 7) {
            userborrow(libe);
        } else if (choise == 8) {
            returnbook(libe);
        } else if (choise == 9) {
            libe.printusers();
        } else if (choise == 10) {
            k = false;
        } else {
            break;
        }


    }
}