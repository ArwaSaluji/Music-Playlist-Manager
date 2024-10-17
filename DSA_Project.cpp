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
	
	string song;
	string artist;
	Playlist playlist;
	
	cout << "Music Playlist Manager System" << endl;
	
	int c , n = 1;
	
	do 
	{
		cout << "1. Add Song to Playlist \t2. Display Playlist \n3. Play Playlist \t\t4. Shuffle Playlist \n5. Remove Song from Playlist \t0. Exit"<<endl ;
		cout<<endl;
		cout << "Enter a choice : ";
		cin >> c ;
		cout<<endl;
		switch(c)
		{
			case 1:	
				int a ;
				cout << "Enter the number of songs you want to add to the playlist : ";
				cin >> a ;
				for ( int i = 0 ; i < a ; i++)
				{
					cout << "Enter Song : ";
					cin >> song;
					cout << "Enter Artist : ";
					cin >> artist;
					playlist.addSong(song , artist);
					cout<<endl;
				}
				cout << "Songs Added to the Playlist" << endl;
				cout << endl;
				break;
				
			case 2:
				cout << "Current Playlist:" << endl;
				playlist.display();
				break;
				
			case 3:
				cout << "\nPlaying Playlist:" << endl;
	    		playlist.play();
	    		break;
	    		
	    	case 4:
	    		cout << "\nShuffling Playlist..." << endl;
	    		playlist.shuffle();
	    		playlist.display();
	    		break;
	    		
	    	case 5:
	    		cout << "Enter the name of song you want to remove :: "<< endl;
	    		cin >> song;
	    		cout << "\nRemoving Song "<< song << endl;
			    playlist.removeSong(song);
			    playlist.display();
			    break;
		}
		
		cout << "Enter 1 to continue and 0 to exit :: " << endl;
		cin >> n;
	
	}while ( n != 0 && c != 0);
	
    return 0;
}
