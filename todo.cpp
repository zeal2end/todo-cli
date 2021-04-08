#include "bits/stdc++.h"
using namespace std;
class todo{
	private:
	string cmd,arg2;
	ifstream fin,donein;
	ofstream fout;
	public:
	todo(int argc , char* args[]){
		if(argc == 1){
			this->cmd == "help";
		}else{
			this->cmd = args[1];
		}
		if(argc == 3)
			this->arg2 = args[2];
		else arg2 = "";
		input(cmd);
	}
	void Help(){
		cout << "Usage :-"<<endl;
		cout << "$ ./todo add \"todo item\"  # Add a new todo"<<endl;
		cout << "$ ./todo ls               # Show remaining todos"<<endl;
		cout << "$ ./todo del NUMBER       # Delete a todo"<<endl;
		cout << "$ ./todo done NUMBER      # Complete a todo" <<endl;
		cout << "$ ./todo help             # Show usage"<<endl;
		cout << "$ ./todo report           # Statistics" <<endl;
	}
	void List(){
		fin.open("todo.txt");
		vector<string> tasks;
		while(fin){
			string line;
			getline(fin,line);
			if(line.size() == 0)continue;
			else tasks.push_back(line);
		}
		fin.close();
		int n = (int)tasks.size();
		for(int i = 0;i<n;i++){
			cout << "[" << n-i << "] " << tasks[i] <<endl;
		}
		tasks.clear();
		if(n == 0){
			cout << "There are no pending todos!" <<endl;
		}
	}
	void add(string data){
		if(data.size() == 0){
			cout << "Error: Missing todo string. Nothing added!"<<endl;
			return ;
		}
		fin.open("todo.txt");
		vector<string> tasks;
		int n = 0;
		while(fin){
			string line;
			getline(fin,line);
			if(line.size() == 0)continue;
			tasks.push_back(line),n++;
		}
		fin.close();
		fout.open("todo.txt");
		fout << data ;
		for(int i = 0;i<n;i++){
			fout <<endl <<  tasks[i] ;
		}
		fout.close();
		cout << "Added todo: \"" << data << "\"" <<endl;
	}

	string del(string data,bool d= false){
		if(data.size() == 0){
			cout << "Error: Missing NUMBER for deleting todo." << endl;
			return "";
		}
		stringstream go(data);
		int ind;
		go >> ind;
		// index to del.
		vector<string> tasks;
		fin.open("todo.txt");
		int now = 0;
		while(fin){
			string line,cur;
			getline(fin,line);
			if(line.size() == 0)continue;
			tasks.push_back(line),now++;
		}
		fin.close();
		string s = "";
		if(ind > now || ind == 0){
			cout << "Error: todo #"<< ind << " does not exist. Nothing deleted."<<endl;
			return "";
		}
		else{
			now = now - ind;
			fout.open("todo.txt");
			for(int i = 0;i<(int)tasks.size();i++){
				if(i == now){
					s = tasks[i];
					continue;
				}
				fout << tasks[i] << endl;
			}
			fout.close();
		}
		if(!d){
			cout << "Deleted todo #"<<ind <<endl;
		}
		return s;
	}
	int DoneSize(){
		int s =0;
		fin.open("done.txt");
		while(fin){
			string line;
			getline(fin,line);
			if(line.size() == 0)continue;
			s++;
		}
		fin.close();
		return s;
	}
	int todoSize(){
		int s = 0;
		fin.open("todo.txt");
		while(fin){
			string line;
			getline(fin,line);
			if(line.size() == 0)continue;
			s++;
		}
		fin.close();
		return s;
	}
	void Done(string data){
		string s = del(data,true);
		if(s == ""){
			cout << "Error: Missing NUMBER for marking todo as done." <<endl;
			return;
		}
		else{
			cout << "Marked todo #"<< data << " as done." <<endl;
		}

		time_t now = time(0);
		tm *ltm = localtime(&now);

		vector<string> tasks;
		fin.open("done.txt");
		while(fin){
			string line;
			getline(fin,line);
			if(line.size() == 0)continue;
			tasks.push_back(line);
		}
		fin.close();
		fout.open("done.txt");
		int size = (int)tasks.size();
		for(int i = 0;i<size;i++){
			fout << tasks[i] << endl;
		}
		fout << size+1<<". " << 1900+ltm->tm_year <<"-"<< 1+ltm->tm_mon << "-" << ltm->tm_mday <<" " << s <<endl;
		fout.close();
	}

	void report(){
		time_t now= time(0);
		tm *ltm = localtime(&now);
		int pending = todoSize();
		int completed = DoneSize();
		cout << 1900+ltm->tm_year << "-" << 1+ltm->tm_mon << "-" << ltm->tm_mday << " Pending : " << pending << " Completed : " << completed << endl;
	}

	void input(string &s){
		for(char &c: s)c |= 32;
		if(s == "ls")List();
		else if(s == "add")add(arg2);
		else if(s == "del")del(arg2);
		else if(s == "done")Done(arg2);
		else if(s == "report")report();
		else{
			Help();
		}
	}
};
int main(int argc, char* argv[])
{
	todo T(argc,argv);
    return 0;
}
