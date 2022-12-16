#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
const int maxbooks = 1000;
const int maxuser = 1000;
vector<string> nammesuseer;
// creating book struct--
struct book {
    // initialize variables --------
    string name;
    int id;
    int quantity;
    vector<string> bro;

    // creating book method to include book variables -------
    book() {
        name = "";
        id = 0;
        quantity = 0;
    }
    //creating addbook method to get book information from the User------
    void addbook() {
        cout << "Enter ID, name and quantity of book : " << "\n";
        cin >> id >> name >> quantity;
    }
};
//creating User Struct---
struct user {
//    intialize user variable -------
    string name;
    int userid;
    // creating User method to include book variables -------
    user() {
        name = "";
        userid = 0;
    }
    //creating addbook method to get User information from the User------
    void adduser() {
        cout << "Enter name of user and ID of user: " << "\n";
        cin >> name >> userid;
    }
};
//creating compare method to compare which book is greater in name
bool compa(book &a, book &b) {
    return a.name < b.name;
}
//creating compare method to compare which book is greater in ID
bool compaid(book &a, book &b) {
    return a.id < b.id;
}
//creating Library struct
struct lib {
//    intialize library variables
    user users[maxuser];
    book libbooks[maxbooks];
    int len = 0;
    int lenu = 0;
//    adding book to library
    void addbooks() {
        libbooks[len++].addbook();
        cout << "Successful Addition.\n";
    }
//    searching by prefix in library books
    void searchpr() {
        cout << "Enter the prefix: \n";
        string p;
        cin >> p;
        bool found = false;
//        check if there is only one book to show if found false that is mean that there is anybook with this prefix
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
//    searching book method to help if we want to check if the book is in the lib or not if it was found method return its index if not method return -1
    int searbookname(string &pe) {
        for (int i = 0; i < len; ++i) {
            if (pe == libbooks[i].name) {
                return i;
            }
        }
        return -1;
    }
//    searching book method to help if we want to check if the user is in the lib or not if it was found method return its index if not method return -1
    int searchuser(string &namee) {
        for (int i = 0; i < len; ++i) {
            if (namee == users[i].name) {
                return i;
            }
        }
        return -1;
    }
//this method to show all the books in library which added with its name and its id and its quantity
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
//    adding user struct to users arr of user struct
    void adduser() {
        users[lenu++].adduser();
        cout << "Successful Addition.\n";
    }
// show all the users in users arr in lib struct
    void printusers() {
        for (int i = 0; i < lenu; ++i) {
            cout << "Name : " << users[i].name << " Id : " << users[i].userid << "\n";
        }
    }
};
//sorting the books with its name to help in searching or view the books with name
void prsortname(lib libb) {
    if(libb.len==0){cout <<"There are no books ,now.\n";}
    sort(libb.libbooks, libb.libbooks + libb.len, compa);
    libb.printbooks();
}
//sorting the books with its name to help in searching or view the books with ID
void prsortid(lib libb) {
    if(libb.len==0){cout <<"There are no books ,now.\n";}
    sort(libb.libbooks, libb.libbooks + libb.len, compaid);
    libb.printbooks();
}
//show all the user borrow from lib in this time
void printwhob() {
    for (auto &i: nammesuseer) {
        cout << i << " ";
    }
    cout << "\n";
}
//orginaze borrowing process in lib by saving name of user and which book is borrowed
void userborrow(lib &lib1) {
    cout << "Enter the name of User and the name of the book : " << "\n";
    string username;
    cin >> username;
    string bookname;
    cin >> bookname;
//    check if book in lib
//    check if user in lib
    int help = lib1.searbookname(bookname);
    int ee = lib1.searchuser(username);
    if (help == -1) {
        cout << "There is no book with this name. " << "\n";
    } else if (ee == -1) {
        cout << "There is no user with this name. " << "\n";
    } else {
//        borrow the book
        nammesuseer.push_back(username);
        lib1.libbooks[help].bro.push_back(username);
        cout << "Successful Borrowing.\n";
    }
}
//orginaze Returning process in lib by saving name of user and which book is retuerned
void returnbook(lib &lib1) {
    cout << "Enter the name of User and the name of the book : " << "\n";
    string username;
    cin >> username;
    string bookname;
    cin >> bookname;
    //check if the book is in lib
    //check if the user is in lib
    int help = lib1.searbookname(bookname);
    int ee = lib1.searchuser(username);
    if (help == -1) {
        cout << "There is no book with this name. " << "\n";
    } else if (ee == -1) {
        cout << "There is no user with this name. " << "\n";
    } else {
//        return the book
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
//    initialize the lib struct
    lib libe;
//    print all options in lib
    cout
            << "Enter choise from [1 : 10] : \n1) Add Book\n2) Search Books by prefix\n3) Print who borrowed by name\n4) Print boosk by id \n5) Print boosk by name \n6) Add user\n7) User borrow book\n8) User return book \n9) Print Users\n10) Exit\n";
    int choise;
    bool k = true;
//   run the query if it is in option
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