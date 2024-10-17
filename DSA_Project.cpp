#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;
};

class Playlist {
private:
    Song* head;
    Song* current;

public:
    Playlist() : head(NULL), current(NULL) {}

    // Function to add a song to the playlist
    void addSong(const string& title, const string& artist) {
        Song* newSong = new Song{title, artist, NULL};
        if (!head) {
            head = newSong;
            newSong->next = head; // Point to itself
        } else {
            Song* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newSong;
            newSong->next = head; // Make it circular
        }
    }

    // Function to remove a song from the playlist
    void removeSong(const string& title) {
        if (!head) return;

        Song* temp = head;
        Song* prev = NULL;

        do {
            if (temp->title == title) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    // Removing head
                    if (head->next == head) {
                        delete head;
                        head = NULL;
                        return;
                    }
                    // Find the last node
                    Song* last = head;
                    while (last->next != head) {
                        last = last->next;
                    }
                    last->next = head->next;
                    Song* oldHead = head;
                    head = head->next;
                    delete oldHead;
                }
                delete temp;
                return;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != head);
    }

    // Function to play the playlist
    void play() {
        if (!head) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        current = head;
        do {
            cout << "Playing: " << current->title << " by " << current->artist << endl;
            current = current->next;
        } while (current != head);
    }

    // Function to shuffle the playlist
    void shuffle() {
        if (!head || head->next == head) return; // If there's 0 or 1 song

        // Count the songs
        int count = 0;
        Song* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);

        // Create an array to hold the song pointers
        Song** songs = new Song*[count];
        temp = head;
        for (int i = 0; i < count; i++) {
            songs[i] = temp;
            temp = temp->next;
        }

        // Shuffle the songs
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < count; i++) {
            int j = rand() % count;
            swap(songs[i]->title, songs[j]->title);
            swap(songs[i]->artist, songs[j]->artist);
        }

        delete[] songs; // Free allocated memory
    }

    // Display the playlist
    void display() {
        if (!head) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Song* temp = head;
        do {
            cout << "Song: " << temp->title << " by " << temp->artist << endl;
            temp = temp->next;
        } while (temp != head);
    }
};

int main() {
    Playlist playlist;
    playlist.addSong("Song 1", "Artist A");
    playlist.addSong("Song 2", "Artist B");
    playlist.addSong("Song 3", "Artist C");

    cout << "Current Playlist:" << endl;
    playlist.display();

    cout << "\nPlaying Playlist:" << endl;
    playlist.play();

    cout << "\nShuffling Playlist..." << endl;
    playlist.shuffle();
    playlist.display();

    cout << "\nRemoving 'Song 2'..." << endl;
    playlist.removeSong("Song 2");
    playlist.display();

    return 0;
}

