//----------------------------------
//NAME : RAFIA MALIK
//ROLL NO : 221437
//CLASS : BSCS-3A
//----------------------------------
#include<iostream>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include<vector>
#include <set>
#include <unordered_set>
#include <utility>
#include<string>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include <sstream>
#include<Windows.h>
#include <queue>
#include <stack>
#include <conio.h>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Simple hash combining technique
        return h1 ^ h2;
    }
};
//class Researh_Paper;
class User{
    public:
    string user_id, user_name, user_password, area_of_interests;
    string user_record;
    User(){
        // user_record=user_name+".txt";
    }
    User(string user_id,string user_name,string user_password,string area_of_interests){
        this->user_id=user_id;
        this->user_name=user_id;
        this->user_password=user_password;
        this->area_of_interests=area_of_interests;
        //user_record=user_name+".txt";
    }
    void set_available_areas(string u_name){
        string tit,id,des,li,aut,pubk,date;
        set<pair<int,string>> keywords_set;
        int count=1;
        ifstream file("researchPapersDetails.txt");
        while (getline(file, tit) &&
               getline(file, id) &&
               getline(file, date) &&
               getline(file, des) &&
               getline(file, li) &&
               getline(file, aut)&&
               getline(file, pubk)){
                istringstream iss(pubk);
                string word;
                while(getline(iss,word,',')){
                    keywords_set.insert({count,word});
                    count++;
                }
               }
        for (const auto& element : keywords_set) {
        cout<<"("<<element.first<<") "<<element.second<<endl;
        }
        vector<string> selected_interests;
        cout<<"\nPress 0 when Done.";
        int choice=-1;  //begin by choosing interests.
        while(choice){
            cin>>choice;
            for (const auto& element : keywords_set) {
                if(choice==element.first){
                    selected_interests.push_back(element.second);
                }
            }
        }
        // Concatenate elements into a single string separated by commas (skip it for now)

        user_record=user_name+".txt";
        ofstream write(user_record,ios::app);
        for(const auto& it:selected_interests){
            write<<it<<endl;
        } 
    }
    void update_available_areas(string keywords,string u_id){
        set<string> user_interests;
        ifstream input("Authentication.txt");
        while(input>>user_id>>user_name>>user_password){
            if(user_name==u_id){
                user_record=user_name+".txt";
            }
        }
        string keyword;
        istringstream iss(keywords);
        while(getline(iss,keyword,',')){
            user_interests.insert(keyword);
        }
        ifstream record_in(user_record);
        while(getline(record_in,keyword)){
            user_interests.insert(keyword);
        }
        ofstream update_file(user_record);
        for(const auto &element:user_interests){
            update_file<<element<<endl;
        }

    }
    void add_user_record(){
        ofstream file_append("Authentication.txt", ios::app);

        if (!file_append.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        do {
            // cin.clear();
            cout << "\nEnter user_name: ";
            cin>>user_name;
            // Open the file in input mode to check for existing usernames
            ifstream file_check("Authentication.txt");

            if (!file_check.is_open()) {
                cerr << "Error opening file for reading." << endl;
                return;
            }

            bool usernameTaken = false;
            string temp_name;

            while (file_check >> user_id >> temp_name >> user_password) {
                if (user_name == temp_name) {
                    cout << "\nUsername already taken. Please choose a different one.\n";
                    usernameTaken = true;
                    break;
                }
            }

            file_check.close(); // Close the file after checking

            if (!usernameTaken) {
                // Ask for the password since the username is unique
                // cin.clear();
                cout << "\nEnter Password: ";
                cin>>user_password;
                //updating the number of users in statistics file and setting up USER ID automatically
                ifstream input("statistics.txt");
                string s,t,u;int count1,count2,count3;
                while(input>>s>>count1>>t>>count2>>u>>count3){
                    count2++;
                    break;
                }
                user_id=to_string(count2);
                ofstream output("statistics.txt");
                output<<s<<" "<<count1<<" "<<t<<" "<<count2<<" "<<u<<" "<<count3<<endl;
                // Write the new user to the file
                file_append <<user_id<<" "<< user_name<<" "<<user_password<<endl;

                cout << "\nRegistration successful!\n";
                break; // Exit the loop since a unique username has been provided
            }

        } while (true);
        set_available_areas(user_name);
        cout << "\nRecord is successfully saved!\n";
    }
    bool user_authentication(string check_user,string check_password){
        ifstream authentic("Authentication.txt");
        while(authentic>>user_id>>user_name>>user_password){
            if((user_name==check_user) && (user_password==check_password))
            return true;
        }
        return false;
    }
    void record_history(string u_id,string title,string r_id,string s_or_v){
        // Get the current time
        time_t currentTime =time(0);
        // Format the current time in a 12-hour format
        tm* localTime =localtime(&currentTime);
        char formattedTime[20];  // Buffer to store the formatted time
        strftime(formattedTime, sizeof(formattedTime), "%I:%M %p", localTime);
        // Format the current date
        char formattedDate[12];  // Buffer to store the formatted date
        strftime(formattedDate, sizeof(formattedDate), "%m/%d/%Y", localTime);
        ofstream write("SearchViewHistory.txt",ios::app);
        write<<u_id<<","<<formattedDate<<","<<formattedTime<<","<<s_or_v<<","<<r_id<<","<<title<<endl;  
    }
    void view_history(string id){
        string history_content[6];
        ifstream input("SearchViewHistory.txt");
        string file_line,u_id,date,time,type,p_id,title;
        string seperate;
            stack<string> myStack;
        while(getline(input,file_line)){
            myStack.push(file_line);
        }
        while(!myStack.empty()){
            file_line=myStack.top();
            istringstream iss(file_line);
            int i=0;
            while(getline(iss,seperate,',')){
              history_content[i]=seperate;
              i++;
            }
            if(history_content[0]==id){

            cout<<"\n==================================================================";
            cout<<"\nDATE: "<<history_content[1];
            cout<<"\nTIME: "<<history_content[2];
            cout<<"\nVIEWED: "<<"["<<history_content[4]<<"] "<<history_content[5]<<endl;
            }
            myStack.pop();
        }
    }
};
class Researh_Paper:public User{
public:
string paper_id,title,description,publish_date,link;
string authors_names;
string publish_keywords;
bool flag;
public:
Researh_Paper(){
    flag=false;
}
Researh_Paper(string paper_id,string title,string description,string publish_date,string link,
string authors_names, string publish_keywords){
    this->paper_id=paper_id;
    this->title=title;
    this->description=description;
    this->publish_date=publish_date;
    this->link=link;
    this->authors_names=authors_names;
    this->publish_keywords=publish_keywords;
    flag=false;
}
void add_research(){
    cin.clear();
    cin.ignore();
    cout<<"\nEnter title: ";
    getline(cin,title);
    cin.clear();
    cin.ignore();
    cout<<"\nEnter Description: ";
    getline(cin,description);
    cin.clear();
    cin.ignore();
    cout<<"\nEnter authors: ";
    getline(cin,authors_names);
    cin.clear();
    cin.ignore();
    cout<<"\nEnter keywords: ";
    getline(cin,publish_keywords);
    cin.clear();
    cin.ignore();
    cout<<"\nEnter publish date: ";
    getline(cin,publish_date);
    cin.clear();
    cin.ignore();
    cout<<"\nPaste link here:";
    getline(cin,link);
    //Updating the no.of research Papers in file and Setting the ID automatically
    ifstream input("statistics.txt");
    string s,t,u;int count1,count2,count3;
    while(input>>s>>count1>>t>>count2>>u>>count3){
        count1++;
        break;
    }
    paper_id=to_string(count1);
    ofstream output("statistics.txt");
    output<<s<<" "<<count1<<" "<<t<<" "<<count2<<" "<<u<<" "<<count3<<endl;

    ofstream paper_detail("researchPapersDetails.txt",ios::app);
    paper_detail<<title<<endl<<paper_id<<endl<<publish_date<<endl<<description<<endl<<link<<endl<<authors_names<<endl<<publish_keywords<<endl;
}
void view_by_id(string id,string u){
        ifstream file("researchPapersDetails.txt");
        if (!file) {
            cout << "Error opening the file.\n";
            return;
        }
        while (getline(file, title) &&
               getline(file, paper_id) &&
               getline(file, publish_date) &&
               getline(file, description) &&
               getline(file, link) &&
               getline(file,authors_names)&&
               getline(file,publish_keywords)){
                if(paper_id==id){
                cout<<"\n========================================"<<endl;
                cout<<setw(30)<<"\033[1;32mPUBLICATION \033[0m"<<paper_id<<endl;
                cout<<"\n\n========================================"<<endl;
            cout<<"\033[1;33m TITLE: \033[0m"<<title<<endl;
            cout<<"\n----------------------------------------"<<endl;
            cout<<"\033[1;33m PUBLISH DATE: \033[0m"<<publish_date<<endl;
            cout<<"\n----------------------------------------"<<endl;
            cout<<"\033[1;33m LINK \033[0m"<<link<<endl;
            cout<<"\n----------------------------------------"<<endl;
            cout<<"\033[1;33m DESCRIPTION \033[0m"<<description<<endl;
            cout<<"\n----------------------------------------"<<endl;
            cout<<"\033[1;33m AUTHOR/AUTHORS: \033[0m"<<authors_names<<endl;
            cout<<"\n----------------------------------------"<<endl;
            cout<<"\033[1;33m KEYWORDS: \033[0m"<<publish_keywords<<endl;
            cout<<endl;
            record_history(u,title,paper_id,"view");
            update_available_areas(publish_keywords,u);
                }
        }
        file.close();
}    
};

class TreeNode {
public:
    Researh_Paper data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Researh_Paper value) : data(value), left(nullptr), right(nullptr) {}
};

class BST:public Researh_Paper{
public:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, Researh_Paper value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value.title[0] < node->data.title[0]) {
            node->left = insert(node->left, value);
        } else if (value.title[0] > node->data.title[0]) {
            node->right = insert(node->right, value);
        }
        else{
            node->right = insert(node->right, value);
        }

        return node;
    }

    BST() : root(nullptr) {}

    void insert(Researh_Paper value) {
        root = insert(root, value);
    }
    void preOrderTraversal(TreeNode* node,vector<string> vec) {
        unordered_set<pair<string,string>,pair_hash> recommendation_set;
        if (node != nullptr) {
            // cout << node->data.paper_id << ") " << node->data.title << endl;
            string key;
            for(const auto &i:vec){
            istringstream iss(node->data.publish_keywords);
            while(getline(iss,key,',')){
                if(i==key)
                recommendation_set.insert({node->data.paper_id,node->data.title});
                // cout << current->data.paper_id << ") " << current->data.title << endl;
            }

            }
            preOrderTraversal(node->left,vec);
            preOrderTraversal(node->right,vec);
        }
        for(const auto &element : recommendation_set){
            cout << element.first << ") " << element.second << endl;
        }
    }
    void inOrderTraversal(TreeNode* node,vector<string> vec) {
        unordered_set<pair<string,string>,pair_hash> recommendation_set;
        if (node != nullptr) {
            inOrderTraversal(node->left,vec);
            //cout << node->data.paper_id<<") "<< node->data.title << endl;
            string key;
            for(const auto &i:vec){
            istringstream iss(node->data.publish_keywords);
            while(getline(iss,key,',')){
                if(i==key)
                recommendation_set.insert({node->data.paper_id,node->data.title});
                // cout << current->data.paper_id << ") " << current->data.title << endl;
            }

            }
            inOrderTraversal(node->right,vec);
        }
        for(const auto &element : recommendation_set){
            cout << element.first << ") " << element.second << endl;
        }
    }
    void postOrderTraversal(TreeNode* node,vector<string> vec) {
        unordered_set<pair<string,string>,pair_hash> recommendation_set;
        if (node != nullptr) {
            postOrderTraversal(node->left,vec);
            postOrderTraversal(node->right,vec);
            //cout << node->data.paper_id << ") " << node->data.title << endl;
            string key;
            for(const auto &i:vec){
            istringstream iss(node->data.publish_keywords);
            while(getline(iss,key,',')){
                if(i==key)
                recommendation_set.insert({node->data.paper_id,node->data.title});
                // cout << current->data.paper_id << ") " << current->data.title << endl;
            }

            }
        }
        for(const auto &element : recommendation_set){
            cout << element.first << ") " << element.second << endl;
        }
    }
    void insertFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        while (getline(file, title) &&
               getline(file, paper_id) &&
               getline(file, publish_date) &&
               getline(file, description) &&
               getline(file, link) &&
               getline(file, authors_names)&&
               getline(file,publish_keywords)) {
                Researh_Paper obj(paper_id,title,description,publish_date,link,authors_names,publish_keywords);
            insert(obj);  // Use the insert method of the Researh_Paper (BST) class
        }

        file.close();
    }
    void title_seperating(string title,string keys,string id){
        vector<string> my_title_words;
        vector<string> my_key_words;
        bool found=false;
        istringstream iss1(title);
        istringstream iss2(keys);
        string word1,word2;
        while (iss2 >> word2){
            my_key_words.push_back(word2);
        }
        while (iss1 >> word1) {
           my_title_words.push_back(word1);
        }
        for(const auto &i:my_key_words){
            for(const auto &j:my_title_words){
                if(i==j)
                found=true;
            }
        }
        if(found){
            flag=true;
            cout<<id<<") ";
            for(const auto &i:my_title_words){
            bool printed=false;
                for(const auto &j:my_key_words){
                    if(i==j){
                        cout << "\033[1;35m"<<i<<"\033[0m"<<" ";
                        printed=true;
                    }
                }
                if(!printed)
                cout<<i<<" ";
            }
        cout<<endl;
        }
    }
    void author_seperating(string authors,string keys,string id,string title){
        vector<string> my_author_words; 
        bool found=false;       
        istringstream iss(authors);
        string name;
        while (getline(iss, name, ',')) {
            my_author_words.push_back(name);
        }
        for(const auto &i:my_author_words){
            if(i==keys){
                flag=true;
                cout<<endl;
                cout<<id<<") "<<title<<endl;
                return;
            }
        }
    }
    void TitleinOrderTraversal(TreeNode* node,string keywords) {
        if (node != nullptr) {
            TitleinOrderTraversal(node->left,keywords);
            title_seperating(node->data.title,keywords,node->data.paper_id);
            TitleinOrderTraversal(node->right,keywords);
        }
    }
    void AuthorinOrderTraversal(TreeNode* node,string search_aut){
        if (node != nullptr) {
            AuthorinOrderTraversal(node->left,search_aut);
            author_seperating(node->data.authors_names,search_aut,node->data.paper_id,node->data.title);
            AuthorinOrderTraversal(node->right,search_aut);
        }
    }

    void search_by_title(TreeNode *node,string u){
        string keywords;
        cout<<"Enter keywords to Search: ";
        cin.ignore();
        getline(cin,keywords);
        TitleinOrderTraversal(node,keywords);
        if(flag){
        cout<<"\n>>>>";
        cin>>paper_id;
        view_by_id(paper_id,u);
        }
        else{
            cout<<"\nkeywords cannot be found";
        }
        cin.clear();
        //resetting the flag
        flag=false;
    }
    void search_by_author(TreeNode *node,string u){
        //view publishes by inputting author name.
        string search_aut;
        cout<<"Enter Author to Search: ";
        cin.ignore();
        getline(cin,search_aut);
        AuthorinOrderTraversal(node,search_aut);
        if(flag){
        cout<<"\n>>>>";
        cin>>paper_id;
        view_by_id(paper_id,u); 
        }
        else{
            cout<<"\nAuthor cannot be found"<<endl;
        }
        cin.clear();
        //resetting the flag
        flag=false;
    }
    // Breadth-First Search
    void bfs(vector<string> vec) {
        unordered_set<pair<string,string>,pair_hash> recommendation_set;
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // Process current node
            string key;
            for(const auto &i:vec){
            istringstream iss(current->data.publish_keywords);
            while(getline(iss,key,',')){
                if(i==key)
                recommendation_set.insert({current->data.paper_id,current->data.title});
                // cout << current->data.paper_id << ") " << current->data.title << endl;
            }

            }

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        for(const auto &element : recommendation_set){
            cout << element.first << ") " << element.second << endl;
        }
    }

    // Depth-First Search (In-Order Traversal)
    void dfs(vector<string> vec) {
        unordered_set<pair<string,string>,pair_hash> recommendation_set;
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        stack<TreeNode*> s;
        TreeNode* current = root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
            s.pop();

            // Process current node
            string key;
            for(const auto &i:vec){
            istringstream iss(current->data.publish_keywords);
            while(getline(iss,key,',')){
                if(i==key)
                recommendation_set.insert({current->data.paper_id,current->data.title});
                // cout << current->data.paper_id << ") " << current->data.title << endl;
            }

            }

            current = current->right;
        }
        for(const auto &element : recommendation_set){
            cout << element.first << ") " << element.second << endl;
        }
    }
};
    void recommend_papers(string filename){
        vector<string> interest_list;
        ifstream rec(filename);
        string interest;
        while(getline(rec,interest)){
            interest_list.push_back(interest);
        }
        BST tree;
        tree.insertFromFile("researchPapersDetails.txt");
        srand(time(NULL));
        int traversal_number = rand() % 5 + 1;
        cout<<"\033[1;43m  \033[0m ";
        cout << "\033[1;32mRECOMMENDATIONS FOR YOU\033[0m\n";
        switch(traversal_number){
            case 1: //cout<<"\nBy In Order Traversal: "<<endl;
                    tree.inOrderTraversal(tree.root,interest_list);
            break;
            case 2: //cout<<"\nBy DFS: "<<endl;
                    tree.dfs(interest_list);
            break;
            case 3: //cout<<"\nBy Pre Order Traversal: "<<endl;
                    tree.preOrderTraversal(tree.root,interest_list);
            break;
            case 4: //cout<<"\nBy Post Order Traversal: "<<endl;
                    tree.postOrderTraversal(tree.root,interest_list);
            break;
            case 5: //cout<<"\nBy BFS: "<<endl;
                    tree.bfs(interest_list);
            break;
            default: cout<<"Nothing to show";
        }
    }

class Authors{
    protected:
    string author_name,author_username,author_password;
    public:
    Authors(){}
    bool authenticate(string u_name,string u_pass){
        string detail_array[3];
        ifstream input("Authors.txt");
        string author_detail;
        int i=0;
        string each_detail;
        while(getline(input,author_detail)){
        istringstream iss(author_detail);
            while (getline(iss, each_detail, ',')) {
            detail_array[i]=each_detail;
            i++;
            }
            if((detail_array[0]==u_name) && (detail_array[1]==u_pass)){
                return true;
            }
        }
        return false;
    }
    void Add(){
        Researh_Paper the_paper;
        the_paper.add_research();
    }

};
class Admin:public BST,protected Authors{
    private:
    string admin_name,admin_password;
    public:
    Admin(){
        admin_name="rafiamalik";
        admin_password="dsa123";
    }
    void view_statistics(){
        ifstream stats_input("statistics.txt");
        string s,t,u;
        int count1,count2,count3;
        while(stats_input>>s>>count1>>t>>count2>>u>>count3){
            cout<<"\n==============================";
            cout<<"\n>>> RESPOSITORY STATISTICS <<<";
            cout<<"\n==============================";
            cout<<"\nTotal No.of Publishes: "<<count1;
            cout<<"\nTotal No.of Users (Readers): "<<count2;
            cout<<"\nTotal No.of Authors: "<<count3;
        }

    }
    void add_author(){
        bool prompt=true;
        string u_name,u_pass,name;
        ifstream authors("Authors.txt");
        while(prompt){
        cout<<"\nEnter USERNAME: ";
        cin>>author_username;
        while(authors>>u_name>>u_pass>>name){
            if(u_name==author_username){
                cout<<"\nUsername already Taken. Please enter another username";
                break;
            }
        }
        prompt=false;
        }
        cin.clear();
        cin.ignore();
        cout<<"\nEnter Your Name: ";
        getline(cin,author_name);
        cout<<"\nEnter PASSWORD: ";
        cin>>author_password;
        ofstream write("Authors.txt",ios::app);
        write<<author_username<<","<<author_password<<","<<author_name<<endl;
        ifstream stats_input("statistics.txt");
        string s,t,u;
        int count1,count2,count3;
        while(stats_input>>s>>count1>>t>>count2>>u>>count3){
            count3++;
        }
        ofstream stats_output("statistics.txt");
        stats_output<<s<<" "<<count1<<" "<<t<<" "<<count2<<" "<<u<<" "<<count3<<endl;
        cout<<"\nAuthor registered Successfully!";
        cin.clear();
    }
    void view_all_users(){
        ifstream user_details("Authentication.txt");
            cout << "\033[1;47m                                   \033[0m\n";
            cout << "\033[1;5m      AVAILABLE USERS\033[0m\n";
            cout << "\033[1;47m                                   \033[0m\n";
        while(user_details>>user_id>>user_name>>user_password){
            cout<<"USER ID: "<< "\033[1;44m"<<user_id<<"\033[0m\n"<<endl;
            cout<<"USERNAME: "<< "\033[1;44m"<<user_name<<"\033[0m\n"<<endl;
            cout<<"================================="<<endl;
        }
        cout<<endl;
    }
    void view_all_papers(){
        ifstream file("researchPapersDetails.txt");
        if (!file) {
            cout << "Error opening the file.\n";
            return;
        }
        while (getline(file, title) &&
               getline(file, paper_id) &&
               getline(file, publish_date) &&
               getline(file, description) &&
               getline(file, link) &&
               getline(file,authors_names)&&
               getline(file,publish_keywords)){
                cout<<setw(30)<<"\033[1;46m"<<"PUBLICATION "<<paper_id<<"\033[0m\n"<<endl;
            cout<<"\033[1;31mTITLE:  \033[0m\n"<<title<<endl;
            cout<<endl;
            cout<<"\033[1;31mPUBLISH DATE:  \033[0m\n"<<publish_date<<endl;
            cout<<endl;
            cout<<"\033[1;31mLINKE:  \033[0m\n"<<link<<endl;
            cout<<endl;
            cout<<"\033[1;31mDESCRIPTION:  \033[0m\n"<<description<<endl;
            cout<<endl;
            cout<<"\033[1;31mAUTHORS:  \033[0m\n"<<authors_names<<endl;
            cout<<"================================================================================================================="<<endl;
        }
        file.close();
    }

};
class View{
    int choice;
    public:
    View(){
        choice=-1;
    }
    void header(){
        cout << "\033[1;47m                                   \033[0m\n";
        cout << "\033[1;5m    RESEARCH PAPERS RESPOSITORY\033[0m\n";
        cout << "\033[1;47m                                   \033[0m\n";
    }
    int show_mainMenu(){
        cout<<endl;
        header();
        cout<<setw(33)<<"\033[1;33mMAIN MENU\033[0m\n";
        cout << "\033[1;34m<1> User\033[0m\n";
        cout << "\033[1;34m<2> Author\033[0m\n";
        cout << "\033[1;34m<3> Admin\033[0m\n";
        cout<<"\033[1;33m>>>>> \033[0m";
        cin>>choice;
        return choice;
    }
    int show_userMenu(){
        header();
        cout<<setw(30)<<"\033[1;33mUSER\033[0m\n";
        cout << "\033[1;34m<1> Login \033[0m\n";
        cout << "\033[1;34m<2> Register \033[0m\n";
        cout << "\033[1;34m<3> Back To Main Menu \033[0m\n";
        cout<<"\033[1;33m>>>>> \033[0m";
        cin>>choice;
        return choice;
    }
    int show_authorMenu(){
        cout<<endl;
        header();
        cout<<setw(30)<<"\033[1;33mAUTHOR\033[0m\n";
        cout << "\033[1;34m<1> Login \033[0m\n";
        cout << "\033[1;34m<2> Register \033[0m\n";
        cout << "\033[1;34m<3> Back To Main Menu \033[0m\n";
        cout<<"\033[1;33m>>>>> \033[0m";
        cin>>choice;
        return choice;
    }
    int show_adminMenu(){
        cout<<endl;
        header();
        cout<<setw(30)<<"\033[1;33mADMIN\033[0m\n";
        cout << "\033[1;34m<1> Show Statistics \033[0m\n";
        cout << "\033[1;34m<2> All Available Users Details \033[0m\n";
        cout << "\033[1;34m<3> All Available Papers Details \033[0m\n";
        cout << "\033[1;34m<4> Back To Main Menu \033[0m\n";
        cout<<"\033[1;33m>>>>> \033[0m";
        cin>>choice;
        return choice;
    }
    void header2(){
        cout<<setw(100) << "\033[1;47m                                   \033[0m\n";
        cout<<setw(95) << "\033[1;5m    RESEARCH PAPERS RESPOSITORY\033[0m\n";
        cout<<setw(100) << "\033[1;47m                                   \033[0m\n";
    }
    int userMenuFeatures(){
        cout<<"\n";
        cout << "\033[1;34m<1> Search by Author \033[0m\n";
        cout << "\033[1;34m<2> Search by Title \033[0m\n";
        cout << "\033[1;34m<3> View from Recommendations \033[0m\n";
        cout << "\033[1;34m<4> Show View History \033[0m\n";
        cout << "\033[1;34m<5> Back to Menu \033[0m\n";
        cout << "\033[1;33m >>>>> \033[0m";
        cin>>choice;
        return choice;
    }
    int authorMenuFeatures(){
        cout<<"\n";
        cout << "\033[1;34m<1> Add research paper \033[0m\n";
        cout << "\033[1;34m<2> Back to Menu \033[0m\n";
        cout << "\033[1;33m >>>>> \033[0m";
        cin>>choice;
        return choice;
    }
};

int main(){
    system("cls");
    BST tree;
    tree.insertFromFile("researchPapersDetails.txt");
    
    View v;
    bool main_loop=true;
    int main_choice;
    while(main_loop){
       main_choice=v.show_mainMenu();
       if(main_choice==1)
       {
        bool user_loop=true;
        int user_choice;
        while(user_loop)
        {
            user_choice=v.show_userMenu();
            if(user_choice==1){
                string check_user, check_password;
                cout << "\nEnter Username: ";
                cin>>check_user;
                cout << "\nEnter Password: ";
                cin>>check_password;

                ifstream authentic("Authentication.txt");
                bool user_found=false;
                while (authentic >> tree.user_id >> tree.user_name >> tree.user_password) 
                {
                    if ((tree.user_name == check_user) && (tree.user_password == check_password)) 
                    {
                        user_found=true;
                        tree.user_record=tree.user_name+".txt";
                    }
                }
                if(!user_found){
                    cout<<"\nUser cannot be found. Incorrect Username or Password\n";
                    getch();
                    system("cls");
                }
                else{
                    system("cls");
                        v.header2();
                        cout<<"\n";
                        cout<<setw(15)<<"\033[1;33m* WELCOME TO YOUR ACCOUNT *\033[0m\n";
                        cout<<"\n";
                        recommend_papers(tree.user_record);
                        bool user_loop2=true;
                        while(user_loop2){
                            int my3=v.userMenuFeatures();
                            if(my3==1){
                                tree.search_by_author(tree.root,tree.user_id);
                                getchar();
                            }
                            else if(my3==2){
                                tree.search_by_title(tree.root,tree.user_id);
                                getchar();
                            }
                            else if(my3==3){
                                cout<<"\nEnter ID from the above recemommendations: ";
                                cin>>tree.paper_id;
                                tree.view_by_id(tree.paper_id,tree.user_id);
                                getchar();
                            }
                            else if(my3==4){
                                cout<<"\nHISTORY";
                                tree.view_history(tree.user_id);
                                getchar();
                            }
                            else if(my3==5){
                                user_loop2=false;
                            }
                        }
                }
            }
            else if(user_choice==2){
                BST tree1;
                tree1.add_user_record();
            }
            else if(user_choice==3){
                user_loop=false;
            }
            else{
                cout<<"\nInvalid Input.";
            }
        }
       }
       else if(main_choice==2)
       {
        bool author_loop=true;
        int author_choice;
        while(author_loop){
            system("cls");
            author_choice=v.show_authorMenu();
            if(author_choice==1){
                bool author_loop2=true;
                int author_choice2;
                while(author_loop2){
                    system("cls");
                    v.header2();
                    author_choice2=v.authorMenuFeatures();
                    if(author_choice2==1){
                        Authors author;
                        string username,password;
                        cout<<"\nEnter USERNAME: ";
                        cin>>username;
                        cout<<"\nEnter PASSWORD: ";
                        cin>>password;
                        if(author.authenticate(username,password)){
                            system("cls");
                            author.Add();
                            cout<<"\nData Entered Successfully";
                            getch();
                        }
                        else{
                            cout<<"\nAuthor not found. Invalid Username or Password";
                            getch();
                            system("cls");
                        }
                    }
                    else if(author_choice2==2){
                        author_loop2=false;
                        system("cls");
                    }
                }
            }
            else if(author_choice==2){
                Admin adm;
                adm.add_author();
                getch();
            }
            else if(author_choice==3){
                author_loop=false;
                system("cls");
            }
            else{
                cout<<"\nInvalid Input";
                getch();
            }
        }
       }
       else if(main_choice==3){
        bool admin_loop=true;
        int admin_choice;
        string uname,passw;
        Admin admin;
        cout<<"\nEnter USERNAME: ";
        cin>>uname;
        cout<<"\nEnter PASSWORD: ";
        cin>>passw;
        if(uname=="rafiamalik" && passw=="dsa123"){
            while(admin_loop){
                admin_choice=v.show_adminMenu();
                if(admin_choice==1){
                    admin.view_statistics();
                }
                else if(admin_choice==2){
                    system("cls");
                    admin.view_all_users();
                }
                else if(admin_choice==3){
                    system("cls");
                    admin.view_all_papers();
                }
                else if(admin_choice==4){
                    admin_loop=false;
                    system("cls");
                }
                else{
                    cout<<"\nInvalid Input.\n";
                    getch();
                    system("cls");
                }
            }
        }
       }
       else if(main_choice==4){
        main_loop=false;
        system("cls");
       }
       else{
        cout<<"\nInvalid Input.\n";
        getch();
        system("cls");
       }
    }
}