#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
class Helper
{
public:
	template <class T>
	static void ExpandArray(T**& list, T*& value)
	{
		if (list == 0) {
			list = new  T * [2];
			list[0] = value;
			list[1] = 0;
		}
		else {
			int count = 0;
			for (; list[count] != 0; count++);//calculating size;

			//copying
			int size = count + 2;
			T** temp = new T * [size];
			int k = 0;
			for (int i = 0; i < count; i++)
			{
				if (list[i] != 0) {
					temp[k] = list[i];
					k++;
				}
			}
			temp[k] = value;
			k++;
			temp[k] = nullptr;
			delete[] list;
			list = temp;
			temp = 0;
		}
	}
	static int findsubstring(char* str, char* sub) {

		bool flag = false;
		int index = -1;

		for (int i = 0; i < StringLength(str); i++)
		{
			if (str[i] == sub[0])
			{
				if (StringLength(sub) == 1)
					return i;
				else {
					int j = i + 1;
					for (int k = 1; k < StringLength(sub); k++, j++)
					{
						if (str[j] == sub[k])
							flag = true;
						else {
							flag = false;
							break;
						}

					}
					if (flag == true) {
						return i;
					}
				}
			}

		}
		return -1;
	}
	static void StringConcatenate(char*& str1,const char* str2) {
		int size1 = StringLength(str1);
		int size2 = StringLength(str2);
		int size3 = size1 + size2 + 1;

		char* str3 = new char[size3];
		int k = 0;
		for (int i = 0; i < size1; i++)
		{
			str3[k++] = str1[i];
		}
		for (int i = 0; i < size2; i++)
		{
			str3[k++] = str2[i];
		}

		str3[k] = '\0';

		delete[] str1;

		str1 = str3;

		str3 = 0;

	}
	static bool stringCompare(char str1[], char str2[]) {
		int len = StringLength(str1);
		if (len != StringLength(str2))
			return false;

		for (int i = 0; i < len; i++)
			if (str1[i] != str2[i])
				return false;
		return true;
	}
	static int StringLength(char* str)
	{

		int i = 0;
		for (; str[i] != '\0';)
			i++;
		return i;

	}
	static int StringLength(const char* str)
	{

		int i = 0;
		for (; str[i] != '\0';)
			i++;
		return i;

	}
	static void StringCopy(char* dest, char* source) {
		int k = 0;
		for (int i = 0; source[i] != '\0'; i++)
		{
			dest[k++] = source[i];
		}
		dest[k] = '\0';
	}
	static void StringCopy(char* dest, const char* source) {
		int k = 0;
		for (int i = 0; source[i] != '\0'; i++)
		{
			dest[k++] = source[i];
		}
		dest[k] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		char* arr = new char[StringLength(str) + 1];
		StringCopy(arr, str);
		return arr;
	}
	static char* GetStringFromBuffer(const char* str)
	{
		char* arr = new char[StringLength(str) + 1];
		StringCopy(arr, str);
		return arr;
	}
};

class SocialNetwork;
class User;
class Page;
class Object;
class Post;
class Activity;
class comments;
class Memory;
class Date;

class Object
{

protected:
	char* ID;
public:
	Object();
	~Object();
	virtual void PrintName() = 0;
	virtual void viewTimeline() =0 ;
	virtual void  AddPostToTimeline(Post*) = 0;
	//NOTE: NO Need For virtual Destructor
};

Object::Object()
{
	ID = 0;

}

Object::~Object()
{
	if (ID)
		delete[] ID;
}

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	~Date();
	Date(Date& rhs);
	static Date CurrDate;
	static int monthDays[12];
	static void SetCurrDate(int, int, int);
	int countLeapYears();
	int GiveDiffFromCurrDate();
	void Print();
	void ReadDataFromFile(ifstream&);
	bool CheckIfwithinDate();
	bool MatchMemoryDate();
	void PrintDifference() {
		cout << "( " << CurrDate.year - year << " years ago)";
	}
};

Date Date::CurrDate(0, 0, 0);
int Date:: monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
Date::Date()
{
	day = CurrDate.day;
	month = CurrDate.month;
	year = CurrDate.year;
}
Date::Date(Date& rhs)
{
	day = rhs.day;
	month = rhs.month;
	year = rhs.year;
}
Date::~Date()
{
}
int Date::  countLeapYears()
{
	if (month <= 2)
		year--;

	return year / 4 - year / 100 + year / 400;
}
void Date::SetCurrDate(int d, int m, int y)
{
	CurrDate.day = d;
	CurrDate.month = m;
	CurrDate.year = y;

}
int Date:: GiveDiffFromCurrDate() {
	long int n1 = year * 365 + day;

	// Add days for months in given date
	for (int i = 0; i < month - 1; i++)
		n1 += monthDays[i];

	// Add a day for every leap year
	n1 += countLeapYears();


	long int n2 = CurrDate.year * 365 + CurrDate.day;
	for (int i = 0; i < CurrDate.month - 1; i++)
		n2 += monthDays[i];
	n2 += CurrDate.countLeapYears();

	return (n2 - n1);
}
void Date::Print()
{
	cout << day << "/" << month << "/" << year;
}

void Date::ReadDataFromFile(ifstream& read)
{
	read >> day;
	read >> month;
	read >> year;
}

bool Date::CheckIfwithinDate()
{
	int Diff = GiveDiffFromCurrDate();
	if((Diff == 1) || Diff == 0 )
		return true;
	return false;
}

bool Date::MatchMemoryDate()
{
	if ((day == CurrDate.day) && (month == CurrDate.month) && (year < CurrDate.year)) {
		cout << "On this Day \n " << year - CurrDate.year << " year ago you shared:\n";
		return true;
	}

	return false;
}

class Activity
{
private:
	int action;
	char* details;
public:
	Activity();
	~Activity();
	void readDataFromFile(ifstream&);
	void Print();

};

Activity::Activity()
{
	action = 0;
	details = 0;
}

Activity::~Activity()
{
	if (details)
		delete[] details;
}
void Activity::readDataFromFile(ifstream& read)
{
	read >> action;

	char temp[100];
	read.getline(temp, 100);
	details = Helper::GetStringFromBuffer(temp);
}
void Activity::Print()
{
	if (action == 1)
		cout << " feeling " << details;
	else if (action == 2)
	{
		cout << " thinking about " << details;
	}
	else if (action == 3)
	{
		cout << " Making " << details;
	}
	else if (action == 4)
	{
		cout << " celebrating " << details;
	}
}
class comment
{
private:
	char* ID;
	char* text;
	Object* commentedby;
public:
	comment();
	~comment();
	void setData(char*, char*, Object*);
	void Print();

};

comment::comment()
{
	ID = 0;
	text = 0;
	commentedby = 0;
}

comment::~comment()
{
	if (ID)
		delete[] ID;
	if (text)
		delete[] text;
}
void comment::setData(char* commentId, char* content, Object* Ptr)
{

	ID = Helper::GetStringFromBuffer(commentId);
	text = Helper::GetStringFromBuffer(content);
	commentedby = Ptr;
}
void comment::Print()
{
	commentedby->PrintName();
	cout << " wrote: ";
	cout << "\"" << text << "\"";
}
class Post
{
protected:
	char* ID;
	char* text;
	Object* postedby;
	Object** likedby;
	Activity* act;
	Date DatePosted;
	int NoOfLikes;
	comment** comments;
	int NoOfcomments;
public:
	Post();
	Post(const char* Id, const char* text, Object* sharedby);
	~Post();
	void readDataFromFile(ifstream&);
	void setPostedBy(Object*&);
	bool setLikedBy(Object*&);
	char* GetID();
	void AddComment(comment* value);
	virtual void Print(bool DateState , bool CommentState );
	bool CheckIfWithinDate();
	bool CheckIfMemory();
	void viewLikedBy();
	void TellTimeDifferenceFromToday();
};
void Post::TellTimeDifferenceFromToday() {
	DatePosted.PrintDifference();
}
Post::Post()
{
	ID = 0;
	postedby = 0;
	likedby = 0;
	text = 0;
	act = 0;
	NoOfLikes = 0;
	comments = 0;
	NoOfcomments = 0;
}

Post::Post(const char* Id, const char* caption, Object* sharedby) :DatePosted()
{

	ID = Helper::GetStringFromBuffer(Id);
	text = Helper::GetStringFromBuffer(caption);
	postedby = sharedby;
	likedby = 0;
	act = 0;
	NoOfLikes = 0;
	comments = 0;
	NoOfcomments = 0;
}


Post::~Post()
{
	if (ID)
		delete[] ID;
	if (text)
		delete[] text;
	if (act)
		delete act;

	if(comments)
	for (int i = 0;  i < NoOfcomments;  i++)
	{
		if(comments[i])delete comments[i];
	}

}

void Post::readDataFromFile(ifstream& read)
{
	int type = 0;
	read >> type;

	char tempText[100];
	read >> tempText;
	ID = Helper::GetStringFromBuffer(tempText);

	DatePosted.ReadDataFromFile(read);

	read.ignore(numeric_limits<streamsize>::max(), '\n');
	read.getline(tempText, 100);
	text = Helper::GetStringFromBuffer(tempText);


	if (type == 2) {
		act = new Activity;
		act->readDataFromFile(read);
	}
}

void Post::setPostedBy(Object*& ptr)
{
	postedby = ptr;
}

bool Post::setLikedBy(Object*& value)
{
	//checking if already liked
	for (int i = 0; i < NoOfLikes; i++) {
		if (value == likedby[i]) {
			cout << "\n :/ Already Liked the post\n";
			return false;
		}
	}
	
	Helper::ExpandArray(likedby, value);
		NoOfLikes++;
		return true;;
}

char* Post::GetID()
{
	return ID;
}

void Post::AddComment(comment* value)
{
	Helper::ExpandArray(comments, value);
		NoOfcomments++;
}

void Post::Print(bool DateState=true,bool CommentState=true)
{
	cout << "--->";
	if (act) {
		postedby->PrintName();
		cout << " is ";
		act->Print();
		cout << endl;
	}
	else
	{
		//cout << "--- ";
		if (postedby)
			postedby->PrintName();
		cout << " shared ";
	}
	cout << "\"" << text << "\"\t\t";
	
	if(DateState)
	DatePosted.Print();
	cout << endl;
	
	if (comments && CommentState) {
		for (int i = 0; i < NoOfcomments; i++)
		{
			cout << "\t\t\t";
			comments[i]->Print();
			cout << endl;
		}
	}
	//if (likedby && NoOfLikes>0) 
	//{
	//	cout << "\nliked by ";

	//	
	//	if (NoOfLikes == 2) {
	//		likedby[0]->PrintName(); cout << " and "; likedby[1]->PrintName();
	//	}
	//	else if (NoOfLikes > 2) {

	//		likedby[0]->PrintName(); cout << ","; likedby[1]->PrintName(); cout << " and " << NoOfLikes - 2 << " others.";
	//	}
	//	else if (NoOfLikes == 1)
	//		likedby[0]->PrintName();
	//	cout << endl;

	//}
	//cout << "Likes: " << NoOfLikes << "\tComments: " << NoOfcomments<<endl;
	//cout << "---------------------------------------------------------------------------------\n";
	cout << endl;
	cout << endl;
}
bool Post::CheckIfWithinDate()
{
	return (DatePosted.CheckIfwithinDate());
}

bool Post::CheckIfMemory()
{
	return DatePosted.MatchMemoryDate();

}

void Post::viewLikedBy()
{	
	if(likedby!=0)
	for (int i = 0; i < NoOfLikes; i++)
	{
		likedby[i]->PrintName();
		cout << endl;
	}
	else {
		cout << "\nNo likes\n";
	}
}

class Memory :public Post
{

private:
	Post* OrigPost;
public:
	Memory();
	Memory(const char*,Post* Ptrconst, const char* text, Object* sharedby);
	~Memory();
	void Print(bool,bool);
};
Memory::Memory(const char* ID,Post* Ptr, const char* text, Object* sharedby) :Post(ID, text, sharedby)
{
	OrigPost = Ptr;

}
Memory::Memory()
{
	OrigPost = 0;

}

Memory::~Memory()
{

}
void Memory::Print(bool,bool) {
	cout << "\n~~~~";
	postedby->PrintName();
	cout << " shared a memmory ";
	cout << "~~~~\t";
	DatePosted.Print();
	cout << endl;
	cout <<"\"" << text << "\"\n";
	OrigPost->TellTimeDifferenceFromToday();
	cout << endl;
	OrigPost->Print(true,false);

}



class Page :public Object
{
private:
	char* Title;
	Post** TimeLine;
	int NoOfPosts;
public:
	Page();
	~Page();
	void ReadDataFromFile(ifstream&);
	void PrintListView();
	char* GetID();
	void PrintName();
	void viewTimeline();
	void PrintLatestPost();
	void AddPostToTimeline(Post* value);
};

void Page:: viewTimeline() {
	cout << endl;
	PrintName(); cout << " 's Timeline: \n";
	for (int i = 0; i < NoOfPosts; i++)
	{
		TimeLine[i]->Print();
	}
}
Page::Page()
{
	Title = 0;
	TimeLine = 0;
	NoOfPosts = 0;
}

Page::~Page()
{
	if (Title)
		delete[] Title;
	if (TimeLine)
	{
		for (int i = 0; i < NoOfPosts; i++)
		{
			if (TimeLine[i])
				delete TimeLine[i];
		}
		delete[] TimeLine;
	}
}

void Page::ReadDataFromFile(ifstream& read)
{
	char temp[50] = "";
	read >> temp;
	ID = Helper::GetStringFromBuffer(temp);

	read.getline(temp, 50);
	Title = Helper::GetStringFromBuffer(temp);

}

void Page::PrintListView()
{
	cout << ID << " - " << Title << endl;
}

char* Page::GetID()
{
	return ID;
}

void Page::PrintName()
{
	cout << " " << Title;
}
void Page::PrintLatestPost()
{
	for (int i = 0; i < NoOfPosts; i++)
	{
		if (TimeLine[i]->CheckIfWithinDate())
			TimeLine[i]->Print();
	}
}
void Page:: AddPostToTimeline(Post* value) {
	Helper::ExpandArray(TimeLine, value);
	NoOfPosts++;
}
class User :public Object
{
private:
	char* Fname;
	char* Lname;
	User** FriendList;
	Page** LikedPages;
	Post** TimeLine;
	int NoOfPosts;
	int NoOfLikedPages;
	int NoOfFriends;
public:
	User();
	~User();
	bool SearchInTimeline(Post*);
	void PrintListView();
	void ReadDataFromFile(ifstream&);
	void LikePage(Page*);
	void AddFriends(User*);
	void ViewFriendList();
	void viewLikedPages();
	char* GetID();
	char* getFname();
	char* getLname();
	void PrintName();
	void viewTimeline();
	void PrintLatestPost();
	void viewHome();
	void SeeMyMemories();
	void AddPostToTimeline(Post* value);
};

User::User()
{
	Fname = 0;
	Lname = 0;
	FriendList = 0;
	LikedPages = 0;
	NoOfLikedPages = 0;
	NoOfFriends = 0;
	TimeLine = 0;
	NoOfPosts = 0;
}

User::~User()
{
	if (Fname)
		delete[] Fname;
	if (Lname)
		delete[] Lname;
	if (FriendList)
		delete[] FriendList;
	if (LikedPages)
		delete[] LikedPages;
	if (TimeLine)
	{
		for (int i = 0; i < NoOfPosts; i++)
		{
			if (TimeLine[i])
				delete TimeLine[i];
		}
		delete[] TimeLine;
	}


}

void User::PrintListView()
{
	cout << ID << " - " << Fname << " " << Lname << endl;

}

void User::ReadDataFromFile(ifstream& read)
{
	char temp[50] = "";
	read >> temp;
	ID = Helper::GetStringFromBuffer(temp);

	read >> temp;
	Fname = Helper::GetStringFromBuffer(temp);

	read >> temp;
	Lname = Helper::GetStringFromBuffer(temp);


}

void User::LikePage(Page* value)
{
	Helper::ExpandArray(LikedPages, value);
		NoOfLikedPages++;
}

void User::AddFriends(User* value)
{
	Helper::ExpandArray(FriendList, value);
	NoOfFriends++;
}

void User::ViewFriendList()
{
	cout << "Command:\t View friend list\n";
	cout << "-------------------------------------------------------------------------------------\n";
	PrintName();
	cout << "'s -Friend List->\n\n";

	cout << "Total Friends " << NoOfFriends << endl;
	if (FriendList == 0) {
		cout << "\nNo Friends\n";
		return;
	}
	for (int i = 0; FriendList[i] != 0; i++)
	{
		FriendList[i]->PrintListView();
	}
	cout << "-------------------------------------------------------------------------------------\n";
}

void User::viewLikedPages()
{

	cout << "Command:\t View Liked Pages\n";
	cout << "-------------------------------------------------------------------------------------\n";
	PrintName();
	cout << "'s Liked Pages->\n\n";
	cout << "Total Liked Pages: " << NoOfLikedPages << endl;
	if (LikedPages == 0) {
		cout << "\nNo Liked Pages\n";
		return;
	}
	for (int i = 0; LikedPages[i] != 0; i++)
	{
		LikedPages[i]->PrintListView();
	}
	cout << "-------------------------------------------------------------------------------------\n";
}

char* User::GetID()
{
	return ID;
}

char* User::getFname()
{
	return Fname;
}

char* User::getLname()
{
	return Lname;
}

void User::PrintName()
{
	cout << " " << Fname << " " << Lname;
}
void User::viewTimeline()
{
	cout << "Command:\t View Timeline\n";
	cout << "-------------------------------------------------------------------------------------\n";

	PrintName(); cout << " 's Timeline: \n";
	if (TimeLine == 0)
	{
		cout << "No Posts\n";
		return;
	}
	for (int i = 0; i < NoOfPosts; i++)
	{
		TimeLine[i]->Print();
	}
	cout << "-------------------------------------------------------------------------------------\n";
}
void User::PrintLatestPost()
{
	for (int i = 0; i < NoOfPosts; i++)
	{
		if (TimeLine[i]->CheckIfWithinDate())
			TimeLine[i]->Print(false);
	}
}
void User::viewHome()
{

	cout << "Command:\t View Home\n";
	cout << "-------------------------------------------------------------------------------------\n";
	PrintName();
	cout << " HOMEPAGE->\n";
	if (LikedPages == 0 && FriendList == 0) {
		cout << "Hmmm...Look's Like you have not Added any friend Nor You have liked any page";
		return;
	}
	if(FriendList)
	for (int i = 0; i < NoOfFriends; i++)
	{
		FriendList[i]->PrintLatestPost();
	}
	if(LikedPages)
	for (int i = 0; i < NoOfLikedPages; i++)
	{
		LikedPages[i]->PrintLatestPost();
	}
}

void User::SeeMyMemories()
{
	cout << "\n-------------------------------------------------------------------------------------\n";
	cout << "Your Memories:\n";
	cout << "-------------------------------------------------------------------------------------\n";
	for (int i = 0; i < NoOfPosts; i++)
	{
		if (TimeLine[i]->CheckIfMemory()) {
			TimeLine[i]->Print();
			cout << endl;
		}
	}
	cout << "-------------------------------------------------------------------------------------\n";
}

bool User::SearchInTimeline(Post* PostPtr) {
	for (int i = 0; i < NoOfPosts; i++)
	{
		if (TimeLine[i] == PostPtr)
			return true;
	}
	return false;
}
void User:: AddPostToTimeline(Post* value) {
	Helper::ExpandArray(TimeLine, value);
	NoOfPosts++;
}

class SocialNetwork
{
private:
	User** UsersList;
	Page** PagesList;
	Post** PostList;
	int NoOfPages;
	int NoOfUsers;
	int NoOfPosts;
	int NoOfComments;
public:
	SocialNetwork();
	~SocialNetwork();
	void Load();
	void LoadPagesFromFile();
	void LoadUsersFromFile();
	void LoadPostsFromFile();
	void LoadCommentsFromFile();
	Page* SearchPageByID(char*);
	User* SearchUserByID(char*);
	Object* SearchObjectByID(char*);
	Post* SearchPostByID(char*);
	void AddPost(Post*);//For Adding new Post

	void Run();
	void viewPage(const char*);
	void viewPost(const char*);
	void viewPostLikedList(const char*);
	void LikePost(const char* PostId, Object* RequesteBy);
	void PostCommment(const char* PostId, const char* text, Object* RequestedBy);
	void ShareMemory(const  char*, const char*, User*);
	User* SetCurrentUser(const char* UserID);
};
SocialNetwork::SocialNetwork()
{
	PostList = 0;
	UsersList = 0;
	PagesList = 0;
	NoOfPages = 0;
	NoOfUsers = 0;
}

SocialNetwork::~SocialNetwork()
{
	if (UsersList)
	{
		for (int i = 0; i < NoOfUsers; i++)
		{
			if(UsersList[i])
				delete UsersList[i];
		}
		delete[] UsersList;
	}
	if (PagesList)
	{
		for (int i = 0; i < NoOfPages; i++)
		{
			if(PagesList[i])
				delete PagesList[i];
		}
		delete[] PagesList;
	}
}

void SocialNetwork::Load() {

	LoadPagesFromFile();
	LoadUsersFromFile();
	LoadPostsFromFile();
	LoadCommentsFromFile();

}

void SocialNetwork::LoadPagesFromFile()
{

	ifstream read("pages.txt");
	if (!read) {
		cout << "Could'nt Open Read File";
	}
	else {
		read >> NoOfPages;
		//Allocation On Heap
		PagesList = new Page * [NoOfPages];
		for (int i = 0; i < NoOfPages; i++)
		{
			PagesList[i] = new Page;
		}

		//Each User reading its Data
		for (int i = 0; i < NoOfPages; i++)
		{

			PagesList[i]->ReadDataFromFile(read);
			//PagesList[i]->PrintListView();
		}
	}
	read.close();
}

void SocialNetwork::LoadUsersFromFile()
{
	ifstream read("users.txt");
	if (!read) {
		cout << "Could'nt Open File";
	}
	else {
		read >> NoOfUsers;
		//Allocation
		UsersList = new User * [NoOfUsers];
		for (int i = 0; i < NoOfUsers; i++)
		{
			UsersList[i] = new  User;
		}
		//Allocating Temporary Storage
		char*** TempStorage = new char** [NoOfUsers];
		for (int i = 0; i < NoOfUsers; i++)
		{
			TempStorage[i] = new char* [10];
		}

		//Reading
		for (int i = 0; i < NoOfUsers; i++)
		{
			//Reading Id,Fname,Lname
			UsersList[i]->ReadDataFromFile(read);
			char temp[10];
			char  check[3] = "-1";

			//Storing Friend Users Id On Tempstorage
			int j = 0;
			for (; true; j++) {
				read >> temp;
				if (Helper::stringCompare(temp, check) == true) {
					break;
				}
				else {
					TempStorage[i][j] = Helper::GetStringFromBuffer(temp);
				}
			}
			TempStorage[i][j] = 0;


			//Associating Liked Pages
			for (int j = 0; true; j++)
			{

				read >> temp;
				if (Helper::stringCompare(temp, check) == true) {
					break;
				}
				else {
					Page* PagePtr = SearchPageByID(temp);
					if (PagePtr)
					{
						UsersList[i]->LikePage(PagePtr);
					}
				}
			}

		}

		//Associating Friends
		for (int i = 0; i < NoOfUsers; i++)
		{
			for (int j = 0; TempStorage[i][j] != 0; j++)
			{
				User* userPtr = SearchUserByID(TempStorage[i][j]);
				if (userPtr) {
					UsersList[i]->AddFriends(userPtr);
				}
			}
		}
		//Deleting Temp Storage
		for (int i = 0; i < NoOfUsers; i++)
		{
			for (int j = 0; TempStorage[i][j] != 0; j++)
			{
				delete[]  TempStorage[i][j];
			}
			delete[] TempStorage[i];
		}
		delete[] TempStorage;
	}
}

void SocialNetwork::LoadPostsFromFile()
{
	ifstream read("Posts.txt");
	if (!read)
		cout << "could'nt open Post File\n";
	else {

		read >> NoOfPosts;
		PostList = new Post * [NoOfPosts];

		for (int i = 0; i < NoOfPosts; i++) {
			PostList[i] = new Post;

			PostList[i]->readDataFromFile(read);

			char temp[50];
			read >> temp;
			Object* tempPtr = SearchObjectByID(temp);
			PostList[i]->setPostedBy(tempPtr);

			tempPtr->AddPostToTimeline(PostList[i]);

			char check[3] = "-1";
			while (true) {
				read >> temp;
				if (Helper::stringCompare(temp, check) == true) {

					break;
				}
				else {
					tempPtr = SearchObjectByID(temp);
					PostList[i]->setLikedBy(tempPtr);
				}
			}

		}

	}
}

void SocialNetwork::LoadCommentsFromFile()
{
	ifstream read("Comments.txt");
	if (!read) {
		cout << "could'nt load comments file";
	}
	else {
		read >> NoOfComments;

		for (int i = 0; i < NoOfComments; i++)
		{
			comment* ptr = new comment;
			char Id[20];
			read >> Id;

			char PostID[20];
			read >> PostID;

			Post* FoundPost = SearchPostByID(PostID);
			if (FoundPost) {
				FoundPost->AddComment(ptr);
			}

			char ObjID[50];
			read >> ObjID;
			Object* PostedBy = SearchObjectByID(ObjID);

			char text[50];
			read.getline(text, 50);

			ptr->setData(Id, text, PostedBy);

		}
	}
}

Page* SocialNetwork::SearchPageByID(char* pageID)
{
	for (int i = 0; i < NoOfPages; i++)
	{
		if (Helper::stringCompare(PagesList[i]->GetID(), pageID) == true)
			return PagesList[i];
	}
	return nullptr;
}

User* SocialNetwork::SearchUserByID(char* userID)
{
	for (int i = 0; i < NoOfUsers; i++)
	{
		if (Helper::stringCompare(UsersList[i]->GetID(), userID) == true)
			return UsersList[i];
	}
	return nullptr;
}

Object* SocialNetwork::SearchObjectByID(char* toSearch)
{
	for (int i = 0; i < NoOfUsers; i++)
	{
		if (Helper::stringCompare(UsersList[i]->GetID(), toSearch) == true)
			return UsersList[i];
	}
	for (int i = 0; i < NoOfPages; i++)
	{
		if (Helper::stringCompare(PagesList[i]->GetID(), toSearch) == true)
			return PagesList[i];
	}

	return nullptr;
}

Post* SocialNetwork::SearchPostByID(char* search)
{
	for (int i = 0; i < NoOfPosts; i++)
	{
		if (Helper::stringCompare(PostList[i]->GetID(), search) == true)
			return PostList[i];
	}
	return nullptr;
}



void SocialNetwork::AddPost(Post* value) {
	if (PostList == 0) {
		PostList = new  Post * [2];
		PostList[0] = value;
		PostList[1] = 0;
		NoOfPosts++;
	}
	else {
		int count = NoOfPosts;
		//copying
		int size = count + 2;
		Post** temp = new Post * [size];
		int k = 0;
		for (int i = 0; i < count; i++)
		{
			if (PostList[i] != 0) {
				temp[k] = PostList[i];
				k++;
			}
		}
		temp[k] = value;
		k++;
		temp[k] = nullptr;
		delete[] PostList;
		PostList = temp;
		temp = 0;

		NoOfPosts++;
	}
}
User* SocialNetwork::SetCurrentUser(const char* userID) {
	char* NonConstID = Helper::GetStringFromBuffer(userID);
	cout << "Command:\t Set current user to " << userID << endl;
	User* Currentuser = SearchUserByID(NonConstID);
	if (Currentuser) {
		Currentuser->PrintName(); cout << " set as current user";
		return Currentuser;
	}
	else {
		cout << "Invalid ID, User Not Found\n";
			return nullptr;
	}
	cout << endl << endl;
}
void SocialNetwork::Run()
{
	User* Currentuser = SetCurrentUser("u3");
	if (Currentuser == nullptr)
		return;

	Currentuser->ViewFriendList();
	cout << endl;

	//Currentuser->viewLikedPages();
	cout << endl;

	//Currentuser->viewTimeline();
	Date::SetCurrDate(14, 11, 2019);

	Currentuser->viewHome();


	viewPage("p1");

	viewPost("post7");
	
	viewPostLikedList("post7");
	
	LikePost("post7", Currentuser);
	viewPostLikedList("post7");

	PostCommment("post7", "Nice yaar", Currentuser);

	viewPost("post7");

	Currentuser->SeeMyMemories();///Remember To set Date acordingly for seeing memories
	ShareMemory("post1", "Never Thought Time Flies", Currentuser);
	//Currentuser->viewTimeline();
	viewPost("post13");

}

void SocialNetwork::viewPage(const char* searchID)
{
	cout << "Command:\t View Page\n";
	cout << "-------------------------------------------------------------------------------------\n";
	char NonConstSearchId[10];
	Helper::StringCopy(NonConstSearchId, searchID);

	for (int i = 0; i < NoOfPages; i++)
	{
		if (Helper::stringCompare(PagesList[i]->GetID(), NonConstSearchId) == true) {
			PagesList[i]->PrintName();
			cout << "->\n";
			PagesList[i]->viewTimeline();
			cout << "-------------------------------------------------------------------------------------\n";
			return;
		}
	}
	cout << "No Page Found Against This ID";
}

void SocialNetwork::viewPost(const char* searchID)
{
	char NonConstSearchId[10];
	Helper::StringCopy(NonConstSearchId, searchID);

	for (int i = 0; i < NoOfPosts; i++)
	{
		if (Helper::stringCompare(PostList[i]->GetID(), NonConstSearchId) == true) {
			cout << "\n------\n";
			cout << PostList[i]->GetID() << ":";

			PostList[i]->Print();
			return;
		}
	}
	cout << "\nNo Post Found Against This ID\n";
}

void SocialNetwork::viewPostLikedList(const char* PostID)
{
	cout << "Command:\t View "<<PostID<<" Likes:\n";
	cout << "-------------------------------------------------------------------------------------\n";
	char NonConstPostId[10];
	Helper::StringCopy(NonConstPostId, PostID);

	Post* temp = SearchPostByID(NonConstPostId);

	if (temp) {
		cout << "\n" << temp->GetID() << " is liked By : \n";
		temp->viewLikedBy();
	cout << "-------------------------------------------------------------------------------------\n";
	}
	else
		cout << "NO Post Found Against this ID";
}


void SocialNetwork::LikePost(const char* PostId, Object* RequesteBy)
{
	char NonConstPostId[10];
	Helper::StringCopy(NonConstPostId, PostId);
	cout << "Command: LikePost";
	Post* temp = SearchPostByID(NonConstPostId);

	if (temp) {
		cout << endl;
		if (temp->setLikedBy(RequesteBy)) {
		RequesteBy->PrintName(); cout << " Liked " << temp->GetID() << endl;
		}
	}
	else
		cout << "NO Post Found Against this ID\n";
}

void SocialNetwork::PostCommment(const char* PostId, const char* text, Object* RequestedBy)
{
	char NonConstPostID[10];
	Helper::StringCopy(NonConstPostID, PostId);
	char NonConstText[100];
	Helper::StringCopy(NonConstText, text);

	Post* PostPtr = SearchPostByID(NonConstPostID);

	if (PostPtr) {
		cout << endl;
		RequestedBy->PrintName(); cout << " Commented On " << PostPtr->GetID() << endl;
		comment* NewComment = new comment();
		
		char NumberOfID[4];
		_itoa_s( NoOfComments+1, NumberOfID, 10);
		char* Id = new char[5];
		Id[0] = { '\0' };
		Helper::StringConcatenate(Id, "c");
		Helper::StringConcatenate(Id, NumberOfID);

		NewComment->setData(Id, NonConstText, RequestedBy);
		PostPtr->AddComment(NewComment);//Associating with Posts
	}
	else
		cout << "NO Post Found Against this ID\n";
}

void SocialNetwork::ShareMemory(const  char* PostID, const char* caption, User* sharedBY) {

	cout << "Command: ShareMemory()\n:";
	char NonConstPostID[10];
	Helper::StringCopy(NonConstPostID, PostID);

	Post* OrigPtr = SearchPostByID(NonConstPostID);
	if (!(OrigPtr->CheckIfMemory()))
	{
		cout << "\nCan not share memory today.\n";
		return;
	}

	if (sharedBY->SearchInTimeline(OrigPtr))
	{
		char NumberOfID[4];
		_itoa_s(NoOfPosts + 1, NumberOfID, 10);
		char* Id=new char[5];
		Id[0]={'\0'};
		Helper::StringConcatenate(Id, "post");
		Helper::StringConcatenate(Id, NumberOfID);

		Memory* NewMemory = new Memory(Id,OrigPtr, caption, sharedBY);
		sharedBY->AddPostToTimeline(NewMemory);
		AddPost(NewMemory);
	}
	else {
		cout << "\nNO Memory Found Against this ID\n";
	}


}

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SocialNetwork Fb;
	Fb.Load();
	Fb.Run();
	
}