//author: Minh D Nguyen
//email: minhnguyenduc221193@yahoo.com

/*
In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way: 
High Card: Highest value card. 
One Pair: Two cards of the same value. 
Two Pairs: Two different pairs. 
Three of a Kind: Three cards of the same value. 
Straight: All cards are consecutive values. 
Flush: All cards of the same suit. 
Full House: Three of a kind and a pair. 
Four of a Kind: Four cards of the same value. 
Straight Flush: All cards are consecutive values of same suit. 
Royal Flush: Ten, Jack, Queen, King, Ace, in same suit. 
The cards are valued in the order: 
2, 3, 4, 5, 6, 7, 8, 9, Ten, Jack, Queen, King, Ace. 

If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives. But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared; if the highest cards tie then the next highest cards are compared, and so on.
Input:
Your program should read lines from standard input. Each line contains 2 hands (left and right). Cards and hands are separated by space.
Output:
Print out the name of the winning hand or "none" if the hands are equal.
•	Test 1
Test Input 

6D 7H AH 7S QC 6H 2D TD JD AS
Expected Output 

left

•	Test 2

Test Input 
JH 5D 7H TC JS JD JC TS 5S 7S
Expected Output 

none
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int checkPair(vector<int> v){
	set<int> duplicatedCheckSet;

	for(unsigned int i = 0; i < v.size(); i++){
		set<int>::iterator it = duplicatedCheckSet.find(v[i]);
		if(it == duplicatedCheckSet.end() || duplicatedCheckSet.empty())
			duplicatedCheckSet.insert(v[i]);
		else {
			int result = *it;
			duplicatedCheckSet.clear();
			return result;
		}
	}
	return -1;
}

vector<int> checkTwoPairs(vector<int> v){
	int temp = checkPair(v);
	vector<int> outcome(2,-1);
	if(temp == -1)
		return outcome;

	map<int,int> duplicatedCheckMap;
	for(unsigned int i = 0; i < v.size(); i++){
		map<int,int>::iterator it = duplicatedCheckMap.find(v[i]);
		if(it == duplicatedCheckMap.end() || duplicatedCheckMap.empty())
			duplicatedCheckMap.insert(make_pair(v[i],1));
		else {
			duplicatedCheckMap.at(v[i])++;
		}
	}

	int count = 0;
	vector<int> result(2,-1);

	for(map<int,int>::iterator it = duplicatedCheckMap.begin(); it != duplicatedCheckMap.end(); it++){
		if(it->second == 2){
			count++;
			result[count - 1] = it->first;
		}
	}

	if(result[0] < result[1]){
		int temp = result[0];
		result[0] = result[1];
		result[1] = temp;
	}

	duplicatedCheckMap.clear();
	if(count == 2)	return result;
	return outcome;
}

int checkThreeKinds(vector<int> v){

	map<int,int> duplicatedCheckMap;
	map<int,int>::iterator it;

	for(unsigned int i = 0; i < v.size(); i++){
		it = duplicatedCheckMap.find(v[i]);
		if(it == duplicatedCheckMap.end() || duplicatedCheckMap.empty()){
			duplicatedCheckMap.insert(make_pair(v[i],1));
		}
		else {
			it->second++;
			if(it->second == 3){
				int value = it->first;
				duplicatedCheckMap.clear();
				return value;
			}
		}
	}
	return -1;
}

int checkFourKinds(vector<int> v){
	map<int,int> duplicatedCheckMap;
	map<int,int>::iterator it;

	for(unsigned int i = 0; i < v.size(); i++){
		it = duplicatedCheckMap.find(v[i]);
		if(it == duplicatedCheckMap.end() || duplicatedCheckMap.empty()){
			duplicatedCheckMap.insert(make_pair(v[i],1));
		}
		else{
			it->second++;
			if(it->second == 4){
				int value = it->first;
				duplicatedCheckMap.clear();
				return value;
			}
		}
	}

	return -1;
}

vector<int> checkFullHouse(vector<int> v){
	
	vector<int> result(2,-1);
	map<int,int> duplicatedCheckMap;
	map<int,int>::iterator it;

	for(unsigned int i = 0; i < v.size(); i++){
		it = duplicatedCheckMap.find(v[i]);
		if(it == duplicatedCheckMap.end() || duplicatedCheckMap.empty()){
			duplicatedCheckMap.insert(make_pair(v[i],1));
		}
		else it->second++;	
	}

	bool hasThree = false;
	bool hasTwo = false;

	for(it = duplicatedCheckMap.begin(); it != duplicatedCheckMap.end(); it++){
		if(it->second == 2){	
			hasTwo = true;
			result[1] = it->first;
		}
		else if (it->second == 3){
			hasThree = true;
			result[0] = it->first;
		}
	}

	if(hasThree && hasTwo)
		return result;
	
	result[0] = -1;
	result[1] = -1;
	return result;
}

bool checkStraight(vector<int> s){
	sort(s.begin(),s.end());
	for(unsigned int i = 1; i < s.size(); i++){
		if((s[0]+i) != s[i]){
			return false;
		}
	}
	return true;
}

bool checkFlush(string s){
	if( (s[1] == s[4]) && (s[1] == s[7]) && (s[1] == s[10]) & (s[1] == s[13])){
		return true;
	}
	return false;
}

bool checkStraightFlush(string s,vector<int> v){
	return checkStraight(v) && checkFlush(s);
}

bool checkRoyalFlush(string s, vector<int> cardValue){
	set<int> royalSet;
	royalSet.insert(10);
	royalSet.insert(11);
	royalSet.insert(12);
	royalSet.insert(13);
	royalSet.insert(14);

	if(checkFlush(s)){
		set<int> duplicatedCheckSet;

		if(royalSet.find(cardValue[0]) != royalSet.end() && royalSet.find(cardValue[1]) != royalSet.end() && royalSet.find(cardValue[2]) != royalSet.end()
			&& royalSet.find(cardValue[3]) != royalSet.end() && royalSet.find(cardValue[4]) != royalSet.end()){
			
			for(int i = 0; i < 5; i++){
				set<int>::iterator it = duplicatedCheckSet.find(cardValue[i]);
				if( it != duplicatedCheckSet.end()){
					royalSet.clear();
					duplicatedCheckSet.clear();
					return false;
				}
				else {
					duplicatedCheckSet.insert(cardValue[i]);	
				}
			}
		}
		else return false;

		return true;
	}
	return false;
	
}

vector<int> chartoInt(string s){
	vector<int> cardValue;
	for(unsigned int i =0; i < s.length(); i+=3){
		if(s[i] == '2')
			cardValue.push_back(2);
		else if(s[i] == '3')
			cardValue.push_back(3);
		else if(s[i] == '4')
			cardValue.push_back(4);
		else if(s[i] == '5')
			cardValue.push_back(5);
		else if(s[i] == '6')
			cardValue.push_back(6);
		else if(s[i] == '7')
			cardValue.push_back(7);
		else if(s[i] == '8')
			cardValue.push_back(8);
		else if(s[i] == '9')
			cardValue.push_back(9);
		else if(s[i] == 'T')
			cardValue.push_back(10);
		else if(s[i] == 'J')
			cardValue.push_back(11);
		else if(s[i] == 'Q')
			cardValue.push_back(12);
		else if(s[i] == 'K')
			cardValue.push_back(13);
		else cardValue.push_back(14);
	}

	return cardValue;
}


vector<int> cardRank(string s){
	// number at index 0,3,6,9,12
	//suit at index 1,4,7,10,13

	vector<int> cardValue = chartoInt(s);
	vector<int> result;
	vector<int> FullHouse = checkFullHouse(cardValue);
	vector<int> TwoPairs = checkTwoPairs(cardValue);

	if(checkRoyalFlush(s,cardValue)){
		result.push_back(10);
		cout << "royal" << endl;
	}
	else if (checkStraightFlush(s,cardValue)){
		result.push_back(9);
		cout << "straight flush" << endl;
	}
	else if (checkFourKinds(cardValue) != -1){
		result.push_back(8);
		result.push_back(checkFourKinds(cardValue));
		cout << "4 kinds" << endl;
	}
	else if (FullHouse[0] != -1){
		result.push_back(7);
		result.push_back(FullHouse[0]);
		result.push_back(FullHouse[1]);
		cout << "full house" << endl;
	}
	else if (checkFlush(s)){
		result.push_back(6);
		cout << "flush" << endl;
	}
	else if (checkStraight(cardValue)){
		result.push_back(5);
		cout << "straight" << endl;	
	}
	else if (checkThreeKinds(cardValue) != -1){
		result.push_back(4);
		result.push_back(checkThreeKinds(cardValue));
		cout << "3 kinds"<< endl;
	}
	else if (TwoPairs[0] != -1){
		result.push_back(3);
		result.push_back(TwoPairs[0]);
		result.push_back(TwoPairs[1]);
		cout << "2 pairs" << endl;
	}
	else if (checkPair(cardValue) != -1){
		result.push_back(2);
		result.push_back(checkPair(cardValue));
		cout << " has pair" << endl;
	}
	else {
		result.push_back(1);
		cout << "high card" << endl;
	}
	sort(cardValue.begin(),cardValue.end(),greater<int>());
	for(unsigned int i = 0; i <cardValue.size(); i++){
		result.push_back(cardValue[i]);
	}

	return result;
}

int main(){
	cout << "enter card " << endl;
	string cards;
	getline(cin,cards);

	//parsing card on each hand 
	string leftHand = cards.substr(0,14);
	string rightHand = cards.substr(15,14);

	vector<int> leftCards = cardRank(leftHand);
	for(int i=0; i<leftCards.size();i++){
		cout << leftCards[i] << " ";
	}
	cout <<endl;

	cout << "right hand"<<endl;
	vector<int> rightCards = cardRank(rightHand);
	for(int i=0; i<rightCards.size();i++){
		cout << rightCards[i] << " ";
	}
	cout <<endl;
	
	string outcome = "none";
	
	for(unsigned int i = 0; i < leftCards.size(); i++){
		if(leftCards[i] > rightCards[i]){
			outcome = "left";
			break;
		}
		else if (leftCards[i] < rightCards[i]){
			outcome = "right";
			break;
		}
	}
	
	cout << outcome<< endl;
	return 0;
}