#include<iostream>
#include<string>
#include<iomanip>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
class Goti{
	string gotiStatus;
	char gotiValue;
	char gotiSymbol;
	int startingNumber;
	int currentPosition;
	public:
		Goti(char a,char b){
			gotiValue=a;
			gotiSymbol=a;
			startingNumber=b;
			gotiStatus="inside";
		}
		void setGotiStatus(string status){
			gotiStatus=status;
			if(gotiStatus=="inside")
				gotiValue=gotiSymbol;
			else
				gotiValue=' ';	
		}
		bool isInside(){
			if(gotiStatus=="inside")
				return true;
			else
				return false;	
		}
		char getGotiValue(){
			return gotiValue;
		}
		char getGotiSymbol(){
			return gotiSymbol;
		}
		void setGotiSymbol(char ch){
			gotiSymbol=ch;
		}
		int getStartingNumber(){
			return startingNumber;
		}
		void setGotiCurrentPosition(int p){
			currentPosition=p;
		}
		int getGotiCurrentPosition(){
			return currentPosition;
		}
		int getNewPosition(int diceNumber,int current_position){
			if(startingNumber==5){
				int numberMap[]={5,8,11,14,17,24,25,26,27,28,29,41,53,52,51,50,49,48,56,59,62,65,68,71,70,69,66,63,60,57,54,47,46,45,44,43,42,30,18,19,20,21,22,23,15,12,9,6,3,0,1,4,7,10,13,16};
				for(int i=0;i<56;i++){
					if(numberMap[i]==current_position){
						if(i+diceNumber==56){
							return 1000;
						}
						else if(i+diceNumber>55)
							return currentPosition;
						else		
							return numberMap[i+diceNumber];
					}
				}
			}
			else if(startingNumber==66){
				int numberMap[]={66,63,60,57,54,47,46,45,44,43,42,30,18,19,20,21,22,23,15,12,9,6,3,0,1,2,5,8,11,14,17,24,25,26,27,28,29,41,53,52,51,50,49,48,56,59,62,65,68,71,70,67,64,61,58,55};
				for(int i=0;i<56;i++){
					if(numberMap[i]==current_position){
						if(i+diceNumber==56)
							return 1000;
						else if(i+diceNumber>55)
							return currentPosition;
						else		
							return numberMap[i+diceNumber];
					}
				}
			}
		}
};
class Player{
	Goti *goti1;
	Goti *goti2;
	char tokenOverTokenSymbol;
	int gotisReachedCount;
	public:
		Player(char a,char b,int c,char d){
			goti1=new Goti(a,c);
			goti2=new Goti(b,c);
			tokenOverTokenSymbol=d;
			gotisReachedCount=0;
		}
		Goti* getGoti1(){
			return goti1;
		}
		Goti* getGoti2(){
			return goti2;
		}
		int getStartingNumber(){
			return goti1->getStartingNumber();
		}
		char getTokenOverTokenSymbol(){
			return tokenOverTokenSymbol;
		}
		void incrementGotiCompleted(){
			gotisReachedCount++;
		}
		bool hasWon(){
			if(gotisReachedCount>=2)
				return true;
			else
				return false;	
		}
};
class Ludo{
	private:
		int diceNumber;
	    char box[72];
	    Player *p1;
	    Player *p2;
	    bool gameFinished;
	public:
		Ludo(){
			diceNumber=0;
			for(int i=0;i<=71;i++){
				box[i]=' ';
			}
			p1=new Player('o','0',5,'1');
			p2=new Player('x','y',66,'z');
			gameFinished=false;
			srand(time(NULL));
		}
	    void startGame(){
	    	makeBoard();
	    	while(1){
			    makePlayerTurn(p1,p2,1);
			    if(gameFinished){
			    	system("cls");
			    	cout<<"Player 1 won!";
			    	break;
				}
			    makePlayerTurn(p2,p1,2);
			    if(gameFinished){
			    	system("cls");
			    	cout<<"Player 2 won!";
			    	break;
				}
			}
		}	
		void makePlayerTurn(Player *player,Player *opponent,int playerNumber){
			do{
				cout<<"Player "<<playerNumber<<" press any key to roll dice: ";
				getch();
				diceNumber=getRandomNumber();
				cout<<diceNumber<<endl;
				if(player->getGoti1()->isInside() && player->getGoti2()->isInside()){
					if(diceNumber!=6){
					    cout<<"You got "<<diceNumber<<".Wait for your 6.";
						getch();
						system("cls");
						makeBoard();
					}
					else{
						getch();
						movePlayerGoti(player,opponent);
					}
				}
				else{
					movePlayerGoti(player,opponent);
				}
				if(diceNumber==6)
					cout<<"You got another turn!!!"<<endl;
				if(player->hasWon()){
					gameFinished=true;
					break;
				}
			}while(diceNumber==6);
		}
		void movePlayerGoti(Player *player,Player *opponent){
			//if both goti's are at home
			if(player->getGoti1()->isInside() && player->getGoti2()->isInside()){
				player->getGoti1()->setGotiStatus("outside");
				int n=player->getStartingNumber();
				clearNewPositionBox(n,opponent);
				player->getGoti1()->setGotiCurrentPosition(n);
				box[n]=player->getGoti1()->getGotiSymbol();
				system("cls");
				makeBoard();
			}
			//if both goti's are outside the home
			else if(!player->getGoti1()->isInside() && !player->getGoti2()->isInside()){
				int a;
				cout<<endl<<"press 1 to move token 1 else press any other key to move token 2: ";
				cin>>a;
				Goti *gotiToMove;
				Goti *secondGoti;
				if(a==1){
					gotiToMove=player->getGoti1();
					secondGoti=player->getGoti2();
				}
				else{
					gotiToMove=player->getGoti2();
					secondGoti=player->getGoti1();
				}
				int currentPosition=gotiToMove->getGotiCurrentPosition();
				if(box[currentPosition]==player->getTokenOverTokenSymbol())
					box[currentPosition]=secondGoti->getGotiSymbol();
				else//error
					box[currentPosition]=' ';
				int newPosition=gotiToMove->getNewPosition(diceNumber,currentPosition);
				if(newPosition==1000){
					box[currentPosition]=' ';
					player->incrementGotiCompleted();
					gotiToMove->setGotiSymbol(' ');
				}
				else if(newPosition==currentPosition){
					box[currentPosition]=gotiToMove->getGotiSymbol();
					gotiToMove->setGotiCurrentPosition(currentPosition);
				}
				else{
					gotiToMove->setGotiCurrentPosition(newPosition);
					clearNewPositionBox(newPosition,opponent);
					if(box[newPosition]==secondGoti->getGotiSymbol() && secondGoti->getGotiSymbol()!=' ')
						box[newPosition]=player->getTokenOverTokenSymbol();
					else	
						box[newPosition]=gotiToMove->getGotiSymbol();
				}
				system("cls");
				makeBoard();
			}
			//if only one goti is outside the home
			else{
				Goti *outsideGoti;
				Goti *insideGoti;
				//if goti 1 is outside the home
				if(!player->getGoti1()->isInside()){
					outsideGoti=player->getGoti1();
					insideGoti=player->getGoti2();
				}
				//if goti 2 is outside the home
				else{
					outsideGoti=player->getGoti2();
					insideGoti=player->getGoti1();	
				}
				if(diceNumber==6){
					int a;
					if(outsideGoti->getGotiSymbol()==' '){
						a=1;
					}
					else{
						cout<<endl<<"press 1 to begin a new token else press any other key to move the already outside token: ";
						cin>>a;
					}
					//if player wants to start the new goti
					if(a==1){
						int n=player->getStartingNumber();
						clearNewPositionBox(n,opponent);
						insideGoti->setGotiStatus("outside");
						insideGoti->setGotiCurrentPosition(n);
						//if there is already a goti of the same player on the starting number box
						if(box[n]==outsideGoti->getGotiSymbol() && outsideGoti->getGotiSymbol()!=' '){
							box[n]=player->getTokenOverTokenSymbol();
						}
						else{
							box[n]=insideGoti->getGotiSymbol();
						}
						system("cls");
						makeBoard();
					}
					//if player wants to continue the already outside goti
					else{
						//searching for the current box position of player's outsideGoti to move it
						int currentPosition=outsideGoti->getGotiCurrentPosition();
						int newPosition=outsideGoti->getNewPosition(diceNumber,currentPosition);
						if(newPosition==1000){
							box[currentPosition]=' ';
							player->incrementGotiCompleted();
							outsideGoti->setGotiSymbol(' ');
						}
						else{
							clearNewPositionBox(newPosition,opponent);
							box[newPosition]=outsideGoti->getGotiSymbol();
							box[currentPosition]=' ';
							outsideGoti->setGotiCurrentPosition(newPosition);
						}
						system("cls");
						makeBoard();	
					}
				}
				else{
					//here i will move goti1 according to the number map
					getch();
					int currentPosition=outsideGoti->getGotiCurrentPosition();
					int newPosition=outsideGoti->getNewPosition(diceNumber,currentPosition);
					if(newPosition==1000){
						box[currentPosition]=' ';
						player->incrementGotiCompleted();
						outsideGoti->setGotiSymbol(' ');
					}
					else if(newPosition==currentPosition){
						box[currentPosition]=outsideGoti->getGotiSymbol();
						outsideGoti->setGotiCurrentPosition(currentPosition);
					}
					else{
						clearNewPositionBox(newPosition,opponent);
						box[newPosition]=outsideGoti->getGotiSymbol();
						box[currentPosition]=' ';
						outsideGoti->setGotiCurrentPosition(newPosition);
					}
					system("cls");
					makeBoard();
				}
			}
		}
		void clearNewPositionBox(int newPosition,Player *opponentPlayer){
			if(box[newPosition]==opponentPlayer->getGoti1()->getGotiSymbol()){
				opponentPlayer->getGoti1()->setGotiStatus("inside");
			}
			else if(box[newPosition]==opponentPlayer->getGoti2()->getGotiSymbol()){
				opponentPlayer->getGoti2()->setGotiStatus("inside");
			}
			else if(box[newPosition]==opponentPlayer->getTokenOverTokenSymbol()){
				opponentPlayer->getGoti1()->setGotiStatus("inside");
				opponentPlayer->getGoti2()->setGotiStatus("inside");
			}
		}
		void makeBoard(){
			cout<<setw(58)<<"LUDO GAME __ made by Adeel and Usman"<<endl<<endl<<endl<<endl;
			// making upper part of ludo board
			for(int a=0;a<=5;a++){
				for(int i=0;i<=32;i++)
					cout<<" ";		
				cout<<"|   |   |   |";;
				if(a==0)
					cout<<"            PLAYER 1";
				cout<<endl;
				for(int i=0;i<=32;i++)
					cout<<" ";
				cout<<"| "<<box[a*3]<<" | "<<box[a*3+1]<<" | "<<box[a*3+2]<<" |"<<endl;
				for(int i=0;i<=32;i++)
					cout<<" ";
				cout<<"|   |   |   |";
				if(a==0)
					cout<<"    Token 1: "<<p1->getGoti1()->getGotiValue()<<"    Token 2: "<<p1->getGoti2()->getGotiValue();
				cout<<endl;
				if(a==5){
					for(int i=0;i<=8;i++)
						cout<<" ";
					for(int i=0;i<=60;i++)
						cout<<"-";
					cout<<endl;
				}
				else{
					for(int i=0;i<=32;i++)
						cout<<" ";
					cout<<"-------------"<<endl;
			    }
		    }
		    //making left and right part of ludo board
		    //First row of left right part of ludo board
			for(int i=0;i<=12;i++)
			   	cout<<" ";
			cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=10;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<box[i+18]<<" | ";;
		    for(int i=0;i<=9;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<"| "<<box[i+24]<<" ";
			cout<<endl;
			for(int i=0;i<=12;i++)
		    	cout<<" ";
		    cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=8;i++)
				cout<<" ";
			for(int i=0;i<=60;i++)
				cout<<"-";
			cout<<endl;
			//second row of left right part of ludo board 
			for(int i=0;i<=12;i++)
			   	cout<<" ";
			cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=10;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<box[i+30]<<" | ";;
		    for(int i=0;i<=9;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<"| "<<box[i+36]<<" ";
			cout<<endl;
			for(int i=0;i<=12;i++)
		    	cout<<" ";
		    cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=8;i++)
				cout<<" ";
			for(int i=0;i<=60;i++)
				cout<<"-";
			cout<<endl;
			//third row of left right part of ludo board
			for(int i=0;i<=12;i++)
			   	cout<<" ";
			cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=10;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<box[i+42]<<" | ";;
		    for(int i=0;i<=9;i++)
		    	cout<<" ";
			for(int i=0;i<=5;i++)
				cout<<"| "<<box[i+48]<<" ";
			cout<<endl;
			for(int i=0;i<=12;i++)
		    	cout<<" ";
		    cout<<"|   |   |   |   |   |           |   |   |   |   |   |"<<endl;
		    for(int i=0;i<=8;i++)
				cout<<" ";
			for(int i=0;i<=60;i++)
				cout<<"-";
			cout<<endl;
			//makinig bottom part of ludo board
			for(int a=0;a<=5;a++){
				if(a==5){
					cout<<"            PLAYER 2";
					for(int i=0;i<=12;i++)
						cout<<" ";
				}
				else{
				    for(int i=0;i<=32;i++)
					    cout<<" ";
				}
				cout<<"|   |   |   |"<<endl;
				for(int i=0;i<=32;i++)
					cout<<" ";
				cout<<"| "<<box[(a*3)+54]<<" | "<<box[(a*3+1)+54]<<" | "<<box[(a*3+2)+54]<<" |"<<endl;
				if(a==5){
					cout<<"    Token 1: "<<p2->getGoti1()->getGotiValue()<<"    Token 2: "<<p2->getGoti2()->getGotiValue();
					for(int i=0;i<=4;i++)
						cout<<" ";
				}
				else{
					for(int i=0;i<=32;i++)
						cout<<" ";
				}
				cout<<"|   |   |   |"<<endl;
				for(int i=0;i<=32;i++)
					cout<<" ";
				if(a!=5)
					cout<<"-------------"<<endl;
			}
			cout<<endl<<endl<<endl;
	    	for(int i=0;i<=79;i++)
	    		cout<<"_";
			cout<<endl<<endl;
		}
		int getRandomNumber(){
			return 1+rand()%6;
		}
};
int main(){
	Ludo ludo;
	ludo.startGame();
	getch();
}
