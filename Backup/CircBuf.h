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
	
public:

	char* buffer;

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
		if(sz > capacityLeft){
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

		if(static_cast<size_t>(len) > capacityLeft){
			expand();
		}

		for(int i = 0; i <= len; i++){
			if(static_cast<size_t>(tail) >= totalCapacity){
				tail = 0;
			}
			buffer[tail] = strInsert[i];
			if(i < len){
				tail++;
			}
			//capacityLeft--;
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
		for(int i = 0; i < static_cast<int>(passed); i++){
			if(static_cast<size_t>(head) == totalCapacity){
				head = 0;
			}
			totalStr += buffer[head];

			head++;
			numelements--;
			capacityLeft++;
		}
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

	};	
	void		expand(){

		char* temp = new char[totalCapacity + CHUNK];

		if(tail < head){
			std::copy(buffer + head, buffer + totalCapacity, temp);
			cout << examine() << endl;
			std::copy(buffer, buffer + tail, temp + (head - totalCapacity));
		}
		else{
			std::copy(buffer + head, buffer + totalCapacity, temp);
		}

		//delete[] buffer;

		buffer = temp;
		tail = numelements;
		head = 0;
		totalCapacity += CHUNK;
		capacityLeft += CHUNK;

	};
};
#endif
