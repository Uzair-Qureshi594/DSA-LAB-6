#include <iostream>
#include <string>
using namespace std;

class SongNode {
public:
    string songName;
    SongNode *prev, *next;
    SongNode(string name) : songName(name), prev(nullptr), next(nullptr) {}
};

class Playlist {
    SongNode *head, *tail;

public:
    Playlist() : head(nullptr), tail(nullptr) {}

    void addSongToEnd(string songName) {
        SongNode *newSong = new SongNode(songName);
        if (!head) head = tail = newSong;
        else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Added song: " << songName << endl;
        printPlaylist();
    }

    void traverseForward() {
        cout << "Playlist (Forward): ";
        for (SongNode *temp = head; temp; temp = temp->next)
            cout << temp->songName << " ";
        cout << endl;
    }

    void traverseBackward() {
        cout << "Playlist (Backward): ";
        for (SongNode *temp = tail; temp; temp = temp->prev)
            cout << temp->songName << " ";
        cout << endl;
    }

    void deleteSong(string songName) {
        for (SongNode *temp = head; temp; temp = temp->next) {
            if (temp->songName == songName) {
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;

                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                delete temp;
                cout << "Deleted song: " << songName << endl;
                printPlaylist();
                return;
            }
        }
        cout << "Song not found: " << songName << endl;
    }

    void printPlaylist() {
        cout << "Current Playlist: ";
        for (SongNode *temp = head; temp; temp = temp->next)
            cout << temp->songName << " ";
        cout << endl;
    }

    ~Playlist() {
        while (head) {
            SongNode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist myPlaylist;
    string songName, del;
    char c;

    while (true) {
        cout << "\nEnter the song name: ";
        getline(cin, songName);
        myPlaylist.addSongToEnd(songName);

        cout << "Do you want to add another song? (y/n): ";
        cin >> c;     
        cin.ignore();
        if (c == 'n' || c == 'N') break; 
    }

    myPlaylist.traverseForward();
    myPlaylist.traverseBackward();

    cout << "Enter the song name to delete: ";
    getline(cin, del);
    myPlaylist.deleteSong(del);
    myPlaylist.traverseForward();

    return 0;
}
