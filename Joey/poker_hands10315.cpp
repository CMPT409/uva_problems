#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <sstream>
#include <list>
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

unordered_map<char, int> mp = {{'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, 
						{'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12}, 
						{'C', 0}, {'D', 1}, {'H', 2}, {'S', 3}};


struct hand
{
	bitset<64> cardsBit;
	int valueNum[13] = {0};
	int suitNum[4] = {0};
	int pair = 0;
	int twoPairs = 0;
	int three = 0;
	int straight = 0;
	int flush = 0;
	int fullHouse = 0;
	int four = 0;
	int straightFlush = 0;

public:
	void setCard(string card){ 
		int value = mp[card[0]];
		int suit = mp[card[1]];
		valueNum[value]++;
		suitNum[suit]++;
		cardsBit[value] = 1;
	}
	void check(){
		int straightCount = 0;
		for (int i = 0; i < 13; ++i)
		{
			if (valueNum[i] == 0)
			{
				straightCount = 0;
			}
			else{	//valueNum[i] >= 1
				straightCount++;
				if (straightCount == 5){
					straight = 1;
					cardsBit[59] = 1;
					cardsBit[39 + i] == 1;
					break;
				}
				// cout << valueNum[i] << " card " << i<< endl;
			}
			if (valueNum[i] == 2){
				pair++;
				cardsBit[56] = 1;
				cardsBit[13 + i] = 1;
			}
			else if (valueNum[i] == 3){
				three = 1;
				cardsBit[58] = 1;
				cardsBit[26 + i] = 1;
			}
			else if (valueNum[i] == 4){
				four = 1;
				cardsBit[62] = 1;
				cardsBit[26 + i] = 1;
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			if (suitNum[i] == 5){
				flush = 1;
				cardsBit[60] = 1;
			}
		}
		
		if (pair == 2){
			twoPairs = 1;
			cardsBit[57] = 1;
		}
		if (pair == 1 && three == 1){
			fullHouse = 1;
			cardsBit[61] = 1;
		}
		if (straight == 1 && flush == 1){
			straightFlush = 1;
			cardsBit[63] = 1;
		}
	}
};

int main(int argc, char const *argv[])
{
	while(true){
		string line;
		getline(cin, line);
		if (line == "") {
			break;
		}
		stringstream ss(line);
		string blackCards[5];
		string whiteCards[5];
		struct hand blackHand;
		struct hand whiteHand;

		for (int i = 0; i < 5; ++i)
		{
			ss >> blackCards[i];
			blackHand.setCard(blackCards[i]);
		}
		for (int i = 0; i < 5; ++i)
		{
			ss >> whiteCards[i];
			whiteHand.setCard(whiteCards[i]);
		}
		blackHand.check();
		whiteHand.check();
		// cout << blackHand.cardsBit << endl;
		// cout << whiteHand.cardsBit << endl;
		if (blackHand.cardsBit.to_ullong() > whiteHand.cardsBit.to_ullong())
		{
			cout << "Black wins." << endl;
		}
		else if (blackHand.cardsBit.to_ullong() < whiteHand.cardsBit.to_ullong())
		{
			cout << "White wins." << endl;
		}
		else {
			cout << "Tie." << endl;
		}
	}
	return 0;
}