#include<iostream>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include<ctime>
#include<conio.h>

#define account0 6210810940012937393
#define random(a,b) (rand()%(b - a + 1) + a)

using namespace std;

int number = 0;
int n = 0;
class ATM;
class depositcard;
class account{
public:
	account(string i, string n, int h,string se, string a, string t, string s, string p,double m){
		id = i;
		name = n;
		sex = se;
		address = a;
		tele = t;
		shenfen = s;
		password = p;
		money = m;
        Hash=h;
	}
	string getid(){
		return id;
	}
	void display();
	void querymoney();
protected:
	string id;
	string name;
	string address;
	string tele;
	string shenfen;
	string password;
	string sex;
	double money;
    int Hash;
};

class ATM{
public:
	void setdeposit();
	void enterdeposit();
	void delaccount();
	void exitatm();
	bool passwordeq(int Hash, double money);
	int passworda(double m);
	void dsave();
	void dread();
	string inputpassword();
	bool checkshen(string str);
	void menu();
protected:
	depositcard *deposit[50];
	static int depositcount;
};

class depositcard:public account, public ATM{
public:
	friend class ATM;
	depositcard(string i, string n, int h, string se, string a, string t, string s, string p,double m):account(i,n,h,se,a,t,s,p,m){}
	void save();
	void fetch();
	string getp(){
		return password;
	}
};
int ATM::depositcount = 0;
void ATM::dsave(){
	ofstream infile("deposit.txt", ios::out);
	ofstream outfile("deposit.txt", ios::out);
	outfile << depositcount << "  ";
	for(n = 0; n < depositcount; n++){
		outfile << deposit[n] -> id << "  ";
		outfile << deposit[n] -> money << "  ";
		outfile << deposit[n] -> name << "  ";
		outfile << deposit[n] -> password << "  ";
		outfile << deposit[n] -> shenfen << "  ";
		outfile << deposit[n] -> tele << "  ";
		outfile << deposit[n] -> address << "  ";
		outfile << deposit[n] -> sex << "  ";
        outfile<<deposit[n]->Hash<<"  ";
	}
	outfile.close();
}
void ATM::dread(){
	string id;
	string sex;
	string nam;
	string passw;
	string tele;
	string adress;
	string shenfen;
	double money;
    int Hash;
	ifstream infile("deposit.txt", ios::in);
	infile >> depositcount;
	if(!infile){
		cerr << "Error no data" << endl;
		return;
	}
	for(n = 0; n < depositcount; n++){
		infile >> id;
		infile >> money;
		infile >> nam;
		infile >> passw;
		infile >> shenfen;
		infile >> tele;
		infile >> adress;
		infile >> sex;
        infile>>Hash;
		depositcard * acc = new depositcard(id, nam, Hash,sex, adress, tele, shenfen, passw, money);
		deposit[n] = acc;
	}
	infile.close();
	cout << "reading" << endl;
}
string  ATM::inputpassword(){
	string s;
	char ch;
	while((ch = getch()) != '\r'){
		s += ch;
		cout << "*";
	}
	return s;
}
void account::display(){
	cin.get();
	system("cls");
	cout << "==================================" << endl;
	cout << "        name:" << name << endl;
	cout << "        sex:" << sex << endl;
	cout << "        address:" << address << endl;
	cout << "        telephone:" << tele << endl;
	cout << "        id:" << id << endl;
	cout << "        meney:" << money << endl;
	cout << "==================================" << endl;
}
bool ATM::checkshen(string str){
	int len = str.length();
	if(len != 18){
		return false;
	}
	else{
		int i;
		for(i = 0; i < 18; i++){
			if(str[i] < '0' || str[i] > '9'){
				if(i == 17 && str[i] != 'x' && str[i] != 'X'){
					return false;
				}
				else if(i != 17){
					return false;
				}
				else
					return false;
			}
		}
	}
	return true;
}
void ATM::exitatm(){
	cout << "bye" << endl;
	exit(-1);
}
void ATM::menu(){
	cout << "        welcome" << endl;
	getch();
	do{
		system("cls");
		cout << "==================================" << endl;
		cout << "        1.creat" << endl;
		cout << "        2.login" << endl;
		cout << "        3.delete" << endl;
		cout << "        4.exit" << endl;
		cout << "==================================" << endl;
		int u = 0;
		cin >> u;
		while(u < 1 || u > 4){
			cout << "please input a true number" << endl;
			cin >> u;
		}
		system("cls");
		switch(u){
			case 1:
				setdeposit();
				break;
			case 2:
				enterdeposit();
				break;
			case 3:
				delaccount();
				break;
			case 4:
				exitatm();
				break;
			}
		}while(1);
		system("cls");
}
void ATM::setdeposit(){
	srand((unsigned)time(NULL));
	string i, n, a, t, s, se, p;
	int h;
	double m;
	int find = 1;
	cin.get();
	cout << "please input name" << endl;
	getline(cin,n);
	cout << "please input sex" << endl;
	cin >> se;
	cin.get();
	cout << "plese input address" << endl;
	getline(cin,a);
	cout << "please input the phone number" << endl;
	cin >> t;
	while(1){
		cout << "please input your id card number" <<endl;
		cin >> s;
		if(!checkshen(s)){
			cout << "error" << endl;
			continue;
		}
		else
			break;
	}
	while(1){
		int x = 2;
		cout << "please input 6 number" << endl;
		p = inputpassword();
		cout << endl;
		string p1;
		cout << "please input again" << endl;
		p1 = inputpassword();
		cout << endl;
		while(p != p1 && x != 0){
			cout << "wrong  you still have " << x << "time" << endl;
			p1 = inputpassword();
			x--;
			cout << endl;
		}
		if(p1 == p)
			break;
		if(x == 0){
			find = 0;
			break;
		}
	}
	if(find == 0)
		return ;
	cout << "please input number for set money" << endl;
	cin >> m;
	while(m <= 0){
		cout << "please input true number" << endl;
		cin >> m;
	}
	cin.get();
	h = passworda(m);
	long long acc = account0 + random(1,100) + number;
	number++;
	cout << "success" << endl;
	cout << "your id number is" << acc << "don't forget it" <<endl;
	stringstream str;
	str << acc;
	str >> i;
	deposit[depositcount] = new depositcard(i,n,h,se,a,t,s,p,m);
	depositcount++;
	dsave();
	cout << "input key to continue" <<endl;
	cin.get();
	return;
}
void ATM::enterdeposit(){
	dread();
	string id, p;
	int f1 = 1;
	int flag = 1;
	int j;
	int i = 0;
	int x = 2;
	int y = 2;
	cout << "please input your card number" << endl;
	cin >> id;
	while(flag && x != 0){
		for(int i = 0; i < depositcount; i++){
			if(id == deposit[i] -> getid()){
				flag = 0;
				j = 1;
				break;
			}
		}
		if(flag == 1){
			cout << "wrong card number you still have " << x << "time" <<endl;
			cin >> id;
			x--;
		}
		if(x == 0)
			cout << "return last GUI" << endl;
	}
	if(x == 0)
		return;
	while(1){
		cout << "please input password" << endl;
		p = inputpassword();
	//	cout << p << endl;
	//	cout << deposit[j] -> passw;
		if(p != deposit[i] -> getp()){
			cout << endl << "wrong, you still have" << y << "time" << endl;
			p = inputpassword();
			y--;
		}
		else
			break;
		if(y == 0){
			f1 = 0;
			cout << "return last GUI" << endl;
			break;
		}
	}
		if(f1 == 0)
			return;
		int n;
		do{
			system("cls");
			cout << "        choose your number" << endl;
			cout << "        1.information" << endl;
			cout << "        2.set money" << endl;
			cout << "        3.get money" << endl;
			cout << "        4.check" << endl;
			cout << "        5.return" << endl;
			cin >> n;
			while(n < 1 || n > 5){
				cout << "please input a true number" << endl;
				cin >> n;
			}
			switch(n){
				case 1:
					deposit[i] -> display();
					break;
				case 2:
					deposit[i] -> save();
					dsave();
					break;
				case 3:
					deposit[i] -> fetch();
					dsave();
					break;
				case 4:
					deposit[i] -> querymoney();
					dsave();
					break;
				case 5:
					return;
				}
				cin.get();
			}while(1);
}
void depositcard::save(){
	if(passwordeq(Hash, money)){
	cin.get();
	system("cls");
	double a;
	cout << "please input number for set money" << endl;
	cin >> a;
	while(a <= 0){
		cout << "please input a true number";
		cin >> a;
	}
	cout << "success" << endl;
	money += a;
	Hash = passworda(money);
	cout << "type ket to continue" << endl;
	cin.get();
	}
}
void account::querymoney(){
	system("cls");
	cout << "money" << money << endl;
	cin.get();
}
void depositcard::fetch(){
	if(passwordeq(Hash, money)){
	system("cls");
	double a;
	int b;
	do{
		cout << "input number for get money";
		cin >> a;
		while(a < 0){
			cout << "please input a true number" << endl;
			cin >> a;
		}
		if(money < a)
			cout << "sorry you don't have too much money" << endl;
		else{
			money = money - a;
			cout << endl << "success" << endl;
		}
		cout << "get money again" << endl;
		cin >> b;
		while(b != 0 && b != 1){
			cout << "please input a true numebr" << endl;
			cin >> b;
		}
	}while(b == 0);
	Hash = passworda(money);
	cout << "input key to continue" << endl;
	cin.get();
}
}
void ATM::delaccount(){
	int n;
	int i = 0;
	int j;
	int k;
	int flag = 1;
	string id;
	string p;
	if(n == 0){
		while(flag){
			cout << "please input id card number" << endl;
			cin >> id;
			for(i = 0; i < depositcount; i++){
				if(id == deposit[i] -> getid()){
					j = i;
					flag = 0;
					break;
				}
			}
			if(flag == 1){
				cout << "wrong" << endl;
				cin >> id;
			}
		}
		while(1){
			cout << "please input password" << endl;
			cout << deposit[j] -> getp() << endl;
			if(p != deposit[j] -> getp()){
				cout << "wrong" << endl;
				p = inputpassword();
			}
			else
				break;
		}
		delete deposit[j];
		for(k = j; k < depositcount; k++)
			deposit[k] = deposit[k + 1];
		deposit[depositcount - 1] = NULL;
		depositcount--;
		cout << "success" << endl;
		dsave();
		cin.get();
	}
}
int ATM :: passworda(double m){
    int s;
    s = m;
    s = s ^ 1;
    s = s << 2;
    s = s ^ (1 << 2-1);
    s = ~s;
    return s;
}
bool ATM :: passwordeq(int Hash , double money){
    int Ha1 = passworda(money);
    if(Ha1==Hash) return true;
    else{
        exit(0);
    }

}
int main(){
	ATM atm;
	atm.menu();
	return 0;
}
