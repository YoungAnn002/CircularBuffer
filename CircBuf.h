//
#ifndef CIRCBUF_H
#define CIRCBUF_H

#include <string>
#include <cstddef>
#include <cmath>
using std::string;
using std::cout;
using std::endl;

class CircBuf {
	const size_t CHUNK { 8 };
	// Insert your private stuff here
	private:
	size_t numelements = 0;  //size
	size_t totalCapacity = CHUNK; //total capacity
	int tail = 0; //end of the list
	int head = 0; //beginning of the list
	size_t capacityLeft = totalCapacity;
	char* buffer;

	
public:


	CircBuf(size_t reserve = 0){
		//initiator, makes the buffer the correct size and makes the capacity the same size.

		reserve = ceil(reserve / 8.0);
		totalCapacity= CHUNK * reserve;
		buffer = new char[totalCapacity];
		capacityLeft = totalCapacity;

	};		// Number of elements you want it to be able to hold to start with.
	~CircBuf(){
		//destructer deletes the current buffer
		delete[] buffer;
	};
	size_t	size(){
		//returns the number of elements in the buffer
		return numelements;
	};
	size_t	capacity(){
		//returns the number of elements that the buffer can hold
		return totalCapacity;
	};
	
	void		insert(char newChar){
		//inserts a new character
		if(capacityLeft == 1){
			expand();
		}
		else if(static_cast<size_t>(tail) == totalCapacity){
			tail = 0;
		}


		buffer[tail] = newChar;
		tail++;
		numelements++;
		capacityLeft--;
	};
	void		insert (const char* toInsert, size_t sz){
		//gets passed a simple character or an array of characters
		// sz is the size of the array
		while(sz > capacityLeft){
			expand();
		}

		for(size_t i = 0; i < sz; i++){
			if(static_cast<size_t>(tail) > totalCapacity){
				tail = 0;
			}
			buffer[tail] = toInsert[i];
			tail++;
		}
		numelements += sz;
		capacityLeft -= sz;
	};
	void		insert(const string& strInsert){
		//takes a string, parses it and inserts each character individually
		int len = strInsert.length();

		while(static_cast<size_t>(len) > capacityLeft){
			expand();
		}

		for(int i = 0; i < len; i++){
			if(static_cast<size_t>(tail) >= totalCapacity){
				tail = 0;
			}
			buffer[tail] = strInsert[i];
			if(i < len){
				tail++;
			}

		}

		capacityLeft -= len;
		numelements += len;


	};
	char		get(){
		//grabs the element at head, pushes head forward then returns the element
		if(static_cast<size_t>(head) > totalCapacity){
			head = 0;
		}

		char give = buffer[head];
		head++;
		numelements--;
		capacityLeft++;
		//cout << give << ", " << head << ", " << numelements << ", " << capacityLeft << endl;
		return give;
	};
	string	get(size_t passed){
		string totalStr;
		//takes the number passed in and concatinates that many characters into a string.
		if(passed > numelements){
			passed = numelements;
		}
		for(int i = 0; i < static_cast<int>(passed); i++){
			if(static_cast<size_t>(head) == totalCapacity){
				head = 0;
			}
			totalStr += buffer[head];

			head++;
		}

		if(passed > numelements){
			numelements = 0;
		}
		else{
			numelements -= passed;
		}

		capacityLeft += passed;

		return totalStr;
	};
	string	flush(){
		// Returns a string with all the characters, AND shrinks the buffer to zero.
		string totalStr = "";

		while (head != tail){
			if(static_cast<size_t>(head) == totalCapacity){
				head = 0;
			}
			totalStr += buffer[head];
			head++;
		}

		numelements = 0;
		head = 0;
		tail = 0;
		capacityLeft = totalCapacity;

		return totalStr;
	};	
	string	examine(){
		//Build a string and make already read characters a '-' and an unread character with the character.
		string totalStr = "[";

		for(size_t i = 0; i < totalCapacity; i++){
			if(buffer[i] == static_cast<char>(NULL)){
				totalStr += '-';
			}
			else if(i >= static_cast<size_t>(tail) && i < static_cast<size_t>(head)){
				totalStr += '-';
			}
			else if((i < static_cast<size_t>(head) || i >= static_cast<size_t>(tail)) && head < tail){
				totalStr += '-';
			}
			else{
				totalStr += buffer[i];
			}
		}

		totalStr += ']';
		return totalStr;
	};	
	void		shrink(){
		// Reduces the unused space in the buffer.
		size_t reserve = ceil(numelements / 8.0);
		size_t newCapacity = reserve * CHUNK;
		char* temp = new char[newCapacity];
		if(tail < head){
			std::copy(buffer + head, buffer + totalCapacity, temp);
			std::copy(buffer, buffer + tail, temp + (totalCapacity - head));
		}
		else{
			std::copy(buffer + head, buffer + totalCapacity, temp);
		}


		//buffer = temp;
		tail = numelements;
		head = 0;
		totalCapacity = newCapacity;
		capacityLeft = newCapacity - numelements;
		
		delete[] buffer;
		buffer = new char[totalCapacity];

		std::copy(temp, temp + totalCapacity, buffer);
		delete[] temp;

	};	
	void expand(){
        char* temp = new char[totalCapacity];

		if(tail < head){
			std::copy(buffer + head, buffer + totalCapacity, temp);
			std::copy(buffer, buffer + tail, temp + (totalCapacity - head));
		}
		else{
			std::copy(buffer + head, buffer + totalCapacity, temp);
		}

		totalCapacity += CHUNK;
		capacityLeft += CHUNK;
		delete[] buffer;
		//buffer = temp;
        buffer = new char[totalCapacity];
        std::copy(temp, temp + totalCapacity, buffer);
        tail = numelements;
		head = 0;
        delete[] temp;
    };
};


/*
 *	Program walk through.
 *	Well let's start at the beginning, I allocated all of my variables in the private variables area
 *	after that I made the constructor that actually assigned all the variables to the values I wanted
 *	provided through the user or not. 
 *	After that I made the destructor, size and capacity functions
 *	since those were easy enough.
 *	Insert:
 *	Going to the insert functions, the first function takes a single
 *	character and adds it to the buffer. The next one takes a char array and will assign each
 *	character to the buffer. Last insert function takes a string and adds each character to the buffer.
 *	Get:
 *	As for the get functions the first one will take out only the first character and return it.
 *	The second one is used for grabbing a certain number of characters and returning them as a string.
 *	After that is the flush function that takes all the characters in the buffer, turns them into a
 *	string and returns it. 
 *	Other:
 *	Next is examine which gives you a sneak peak into the whole buffer and
 *	replaces all the used and null characters with dashes. Lastly is the shrink and expand functions.
 *	shrink will make the buffer smaller to fit the ammount of elements in the buffer and the expand
 *	function will make the buffer larger if the buffer is full with unused characters.
 *	P.S.
 *	Not really sure if this was what you were looking for but lemme know if it wasn't...
*/
#endif
