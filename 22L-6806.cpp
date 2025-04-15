#include<iostream>
#include<fstream>

using namespace std;

class Helper
{
public:
	static int StringLenght(const char* str)
	{
		if (str != 0 )
		{
			int i = 0;
			while (str[i] != '\0')
			{
				i++;
			}
			return i;
		}
		else
		{
			return 0;
		}
	}
	static void StringCopy(char* dest, const char* src)
	{
		int  i = 0;
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		int l = StringLenght(str);
		char* String = new char[l + 1];
		StringCopy(String, str);
		return String;

	}
	
	static bool CheckingStringsToBeMatched(char* myString, const char* tofind)
	{
		int len1 = StringLenght(myString);
		int len2 = StringLenght(tofind);

		for (int i = 0; i <= len1 ; i++)
		{
			if (myString[i] == tofind[0])
			{
				int j;

				for (j = 1; j < len2; j++)
				{
					if (myString[i + j] != tofind[j])
						break;
				}

				if (j == len2)
					return true;
			}
		}

		return false;
	}
	static int Strcmp( char* s1, const char* s2)
	{
		int i = 0;
		while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
			i++;
		}
		if (s1[i] < s2[i]) {
			return -1;
		}
		else if (s1[i] > s2[i]) {
			return 1;
		}
		else {
			if (strlen(s1) < strlen(s2)) {
				return -1;
			}
			else if (strlen(s1) > strlen(s2)) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	
};

class Date;
class page;
class user;
class facebook;
class Activity;
class Object;
class Comments;
class Post;
class Memory;

class Date
{
private:
	int Day;
	int Month;
	int Year;
	
public:
	Date();           //Default Constructor
	Date(int, int, int);//overloaded construuctor with default arguments
	void Print();     
	int get_year()
	{
		return Year;
	}
	int get_month()
	{
		return Month;
	}
	int get_day()
	{
		return Day;
	}
	int Compare(Date);
	void ReadFromFile(fstream& file)
	{
		file >> Day;
		file >> Month;
		file >> Year;
	}

	static Date CurrentDate;
	static void  SetCurrentDate(Date d)
	{
		cout << "Command:                Set current System Date " << d.Day << " " << d.Month << " " << d.Year;
	

		CurrentDate.Day = d.Day;
		CurrentDate.Month = d.Month;
		CurrentDate.Year = d.Year;

		cout << "\nSystem Date :\t";
		CurrentDate.Print();

	}

	void Pervious_Day()
	{

		Day -= 1;
	}
	
};
Date Date::CurrentDate;
Date::Date()
{
	Day = 0;
	Month = 0;
	Year = 0;
}
void Date::Print()
{
	cout << Day << "/" << Month << "/" << Year ;
}
Date::Date(int dd, int mm, int yy)
{
	Day = dd;
	Month = mm;
	Year = yy;
}
int Date::Compare(Date d1)

{
	if (Year > d1.Year)
	{
		return 1;
	}
	else if (Year < d1.Year)
	{
		return -1;
	}
	else
	{
		if (Month > d1.Month)
		{
			return 1;
		}
		else if (Month < d1.Month)
		{
			return -1;
		}
		else
		{
			if (Day > d1.Day)
			{
				return 1;
			}
			else if (Day < d1.Day)
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}

}

class Object
{
private:
	char* ID;
public:
	Object()
	{
		ID = NULL;
	}
	virtual ~Object()
	{
		delete[]ID;
	}
	char* get_id()
	{
		return ID;
	}
	void set_id(char* id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}
	
	virtual void AddPostToTimeline(Post*) = 0;
	virtual void PrintListVeiw() = 0;
	virtual void Print_Name() = 0;
};

class Activity
{
private:
	int Type;
	char* Value;
public:
	Activity()
	{
		Type = 0;
		Value = nullptr;
		
	}
    ~Activity()
	{
		if (Value != nullptr)
		{
			delete[] Value;
		}
	}
	int get_Type()
	{
		return Type;
	}
	void ReadFromFile(fstream& fin)
	{
		int t;
		fin >> t;
		Type = t;

		char value[100];
		fin.getline(value, 100);
		Value = Helper::GetStringFromBuffer(value);
	}

	void Print_activity()
	{
		
		if (Type == 1)
		{
			cout << " is feeling " << Value << endl;
		}
		else if (Type == 2)
		{
			cout << " is thinking about " << Value << endl;
		}
		else if (Type == 3)
		{
			cout << " is making " << Value << endl;
		}
		else if (Type == 4)
		{
			cout << " is celebrating " << Value << endl;

		}
	}
};


class Comments
{
private:
	char* Id;
	char* text;
	Object* CommentBy;
public:
	Comments()
	{
		Id = NULL;
		text = NULL;
		CommentBy = NULL;
	}
	~Comments()
	{
		if(Id) delete[] Id;
		if(text) delete[] text;
	}
	char* get_text()
	{
		return text;
	}
	void SetValues(char* id,char* txt,Object* commentBy)
	{
		Id = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(txt);
		CommentBy = commentBy;

	}
	void Print_comments()
	{
		cout << "\t\t";
		CommentBy->Print_Name(); 
		cout << " wrote:\"" << text << "\" " << endl;
	}
};

class Post
{
private:

	char* Post_ID;
	char* TEXT;

	Date SharedDate;
	Activity* activity;
	int form = 0;

	Object* SharedBy;

	Object** LikedBy;
	int numberOfLikes;

	Comments** comments;
	int numberOfcomments;

public:
	Post()
	{	
		
		Post_ID=0;
		TEXT=0;
		form = 0;
		activity = 0;
		SharedBy = 0;
		LikedBy = new Object * [10];
		for(int i=0;i<10;i++)
		{
			LikedBy[i] = 0;
		} 
		comments = new Comments * [10];
		for (int i = 0; i < 10; i++)
		{
			comments[i] = 0;
		}
		numberOfLikes = 0;
		numberOfcomments = 0;
	}
	~Post()
	{
		if (Post_ID)
			delete[]Post_ID;
		if (TEXT)
			delete[]TEXT;
		if (SharedBy)
			delete[]SharedBy;
		if (LikedBy)
			delete[]LikedBy;
		if (activity)
			delete[]activity;
		if (comments)
			delete[]comments;
		
	}
	void ReadDataFromFile(fstream& Post_file)
	{
		
		Post_file >> form;
		if(form==1||form==2)
		{
			char id[15];
			char txt[100];

			Post_file >> id;
			Post_ID = Helper::GetStringFromBuffer(id);
			SharedDate.ReadFromFile(Post_file);
			Post_file.ignore();
			Post_file.getline(txt, 100);
			TEXT = Helper::GetStringFromBuffer(txt);
			if (form == 2)
			{
				activity = new Activity;
				activity->ReadFromFile(Post_file);
			}
		}
		else
		{
			cout << "Error............" << endl;
			exit(0);
		}
	}
	char* get_id()
	{
		return Post_ID;
	}
	 
	int getday()
	{
		int day = SharedDate.get_day();
		return day;
	}
	int getmonth()
	{
		int month = SharedDate.get_month();
		return month;
	}
	char* get_memoeryText()
	{
		return TEXT;
	}
	void SetSharedBy(Object* sharedBy)
	{
		SharedBy = sharedBy;
	}

	Object* GetSharedBy()
	{
		return SharedBy;
	}
	Date GetSharedDate() 
	{
		return SharedDate;
	}
	void Likedpost(Object* likedBy)
	{
		if(LikedBy[numberOfLikes] == NULL)
		{
			LikedBy[numberOfLikes] = likedBy;
			numberOfLikes++;
		}
	}
	virtual void ViewPOst(bool date_allow = true,bool comment_allow =true  )
	{
		
		if (form == 2)
		{
			cout << "---";
			SharedBy->Print_Name();
			activity->Print_activity();
			cout << "   \"" << TEXT << "\"" ;
			if (activity->get_Type() == 4||date_allow==1)
			{
				cout << "(";
				SharedDate.Print();
				cout << ")"<<endl;
			}
			else
			{
				cout << endl;
			}
		}
		else
		{
			cout << "---";
			SharedBy->Print_Name();
			cout << " shared ";
			cout << "   \"" << TEXT << "\"" << endl;
		}
		if(comment_allow == 1)
		{
			ViewComment();
		}
		cout << endl;
	}

	void AddComment(Comments* c)
	{

			comments[numberOfcomments] = c;
			numberOfcomments++;
		
	}

	void ViewlikeBy()
	{
		cout << "Command:                 ViewLikedList("<< Post_ID <<")" << endl;
		cout << "\nPost Liked By:" << endl;
		for (int i = 0; i < numberOfLikes; i++)
		{
			LikedBy[i]->PrintListVeiw();
		}
		cout << "-------------------------------------------------------------" << endl;
		cout << endl;

	}
	void ViewComment()
	{


		for (int i = 0; i < numberOfcomments; i++)
		{
			comments[i]->Print_comments();
		}
		cout << "-------------------------------------------------------------" << endl;
		cout << endl;
	}

	void setvalue(Object* ptr, char* arr)
	{
		SharedBy = ptr;
		TEXT = Helper::GetStringFromBuffer(arr);
	}
};
class Memory : public Post
{
private:
	Post* OriginalPost;
public:
	Memory()
	{
		OriginalPost = NULL;
	}
	Memory(Post* temp, char* arr)
	{
		OriginalPost = temp;
		setvalue(OriginalPost->GetSharedBy(), arr);
	}
	void ViewPOst(bool date_allow = true, bool comment_allow = true)
	{
		cout << "~~~";
		GetSharedBy()->Print_Name();
		cout << "shared a memory~~~...(";
		Date::CurrentDate.Print();
		cout << ")" << endl;
		cout << get_memoeryText() << endl;
	
	
		int year =Date::CurrentDate.get_year() - OriginalPost->GetSharedDate().get_year();
		cout <<"\t\t("<< year << " Years Ago)\n" << endl;

		OriginalPost->ViewPOst(1,0);
		
		
	}
	
};
class page:public Object
{
private:
	
	char* Title;
	Post** TimeLine;
	int TimeLine_List;
public:
	page() 
	{
		Title = nullptr;
		TimeLine = new Post * [10];
		for (int i = 0; i < 10; i++)
		{
			TimeLine[i] = NULL;
		}

		TimeLine_List = 0;
	}
	~page()
	{
		if (Title)
			delete Title;
	
		if (TimeLine) {
			for (int i = 0; i < TimeLine_List; i++) {
				if (TimeLine[i])
				delete TimeLine[i];
			}
			delete[] TimeLine;
		}

	}
	void  ReadDataFromFile(fstream& fin)
	{
		char id[10];
		char title[50];
		fin >> id;
		fin.getline(title, 100);
	
		set_id(id);
		Title = Helper::GetStringFromBuffer(title);
	}

	void Print_Name()
	{
		cout << Title;
	}
	void PrintListVeiw()
	{
		cout << get_id() << "_" << Title << endl;
	}
	
	void viewPage_post()
	{
		Date Current_Date = Date::CurrentDate;
		Current_Date.Pervious_Day();

		for (int i = 0; i < TimeLine_List; i++)
		{
			if (TimeLine[i]->GetSharedDate().Compare(Date::CurrentDate) == 0 || TimeLine[i]->GetSharedDate().Compare(Current_Date) == 0)
			{
				TimeLine[i]->ViewPOst(0,1);
			}
		}

	}
	void AddPostToTimeline(Post* ptr)
	{
		
			if (TimeLine[TimeLine_List] == NULL)
			{
				TimeLine[TimeLine_List] = ptr;
				TimeLine_List++;
				
			}
		
	}
	void viewPagepost()
	{
		cout << Title << endl;
		for (int i = 0; i < TimeLine_List; i++)
		{
				TimeLine[i]->ViewPOst(1,1);
			
		}
	}
};

class user:public Object
{
private:

	char* Firstname;
	char* Lastname;
	page** liked_Pages;
	user** Friend_List;
	int numliked_Pages;
	int numFriend_List;
	Post** TimeLine;
	int TimeLine_List;
	
public:
	user()
	{
	
		Firstname = nullptr;
		Lastname = nullptr;

		liked_Pages = new page * [10];
		for (int i = 0; i < 10; i++)
		{
			liked_Pages[i] = NULL;
		}

		Friend_List = new user * [10];
		for (int i = 0; i < 10; i++)
		{
			Friend_List[i] = NULL;
		}

		numFriend_List = 0;
		numliked_Pages = 0;

		TimeLine = new Post * [10];
		for (int i = 0; i < 10; i++)
		{
			TimeLine[i] = NULL;
		}

		TimeLine_List = 0;

		
	}
	~user()
	{
		
		if (Firstname) delete Firstname;
		if (Lastname) delete Lastname;

		if (Friend_List) 
		{
			delete[] Friend_List;
		}
		if (liked_Pages) 
		{
			delete[] liked_Pages;
		}
		if (TimeLine) {
			for (int i = 0; i < TimeLine_List; i++) {
				if (TimeLine[i])
				delete TimeLine[i];
			}
			delete[] TimeLine;
		}
	}
	void ReadDataFromFile(fstream& fin) {
		char id[20];
		char firstname[50];
		char lastname[50];
		fin >> id >> firstname >> lastname;

	
		set_id(id);
		Firstname = Helper::GetStringFromBuffer(firstname);
		Lastname = Helper::GetStringFromBuffer(lastname);
	}
	

	void likedpage(page* ptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (liked_Pages[i] == 0)
			{
				liked_Pages[i] = ptr;
				numliked_Pages++;
				break;
			}

		}
	}
	void AddFriend(user* ptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (Friend_List[i] == NULL)
			{
				Friend_List[i] = ptr;
				numFriend_List++;
				break;
			}
		}
	}
	void PrintListVeiw()
	{
		cout << get_id() << "_" << Firstname << " " << Lastname << endl;
	}
	void Print_Name()
	{
		cout << Firstname << " " << Lastname;
	}
	void viewFriend_list()
	{
		cout << "\nCommand:                Set current user \"" << get_id() << "\"" << endl;
		Print_Name();
		cout<< " successfully set as Current User" << endl<<endl;

		cout << "Command:                View Friend List" << endl;
		cout << "-------------------------------------------------------------" << endl;

		Print_Name();
		cout << " -Friend List" << endl << endl;

		for (int i = 0; i < numFriend_List; i++)
		{
			Friend_List[i]->PrintListVeiw();
		}
		cout << "-------------------------------------------------------------" << endl;

	}
	void viewliked_Pages()
	{
		cout << "\nCommand:                View Liked Pages" << endl;
		cout << "-------------------------------------------------------------" << endl;

		Print_Name();
		cout << " -Liked Pages" << endl << endl;

		for (int i = 0; i < numliked_Pages; i++)
		{
			liked_Pages[i]->PrintListVeiw();
		}
		cout << "-------------------------------------------------------------" << endl;

	}

	void AddPostToTimeline(Post* ptr)
	{
			if (TimeLine[TimeLine_List] == NULL)
			{
				TimeLine[TimeLine_List] = ptr;
				TimeLine_List++;
			}
			
	}
	void viewFriend_post()
	{
		Date Current_Date = Date::CurrentDate;
		Current_Date.Pervious_Day();

		for (int i = 0; i < TimeLine_List; i++)
		{
			if(TimeLine[i]->GetSharedDate().Compare(Date::CurrentDate)==0|| TimeLine[i]->GetSharedDate().Compare(Current_Date) == 0)
			{
				TimeLine[i]->ViewPOst(0,1);
			}
		}
	}
	
	void ViewHomeScreen()
	{
		cout << "Command:                View Home" << endl;
		cout << "-------------------------------------------------------------" << endl;

		Print_Name();
		cout << " -Home Page" << endl<<endl;

		for(int i=0;i< numFriend_List;i++)
		{
			Friend_List[i]->viewFriend_post();
		}

		for (int i = 0; i < numliked_Pages; i++)
		{
			liked_Pages[i]->viewPage_post();
		}
		cout << "\n-------------------------------------------------------------" << endl;

	}

	void post_comment(Post* post ,char* comment_text)
	{

		Comments* new_comment = new Comments;

		char arr[] = "c14";
		new_comment->SetValues(arr , comment_text,this);
	
       post->AddComment(new_comment);
	}

	void ViewTimeLine()
	{
		cout << "Command:                View TimeLine" << endl;
		cout << "-------------------------------------------------------------" << endl;
		Print_Name();
		cout << "-Time Line" << endl<<endl;

		for (int i = 0; i < TimeLine_List; i++)
		{
				TimeLine[i]->ViewPOst(1,1);
			
		}
	}

	void ShareYourMemory(Post* p,char* text)
 	{
		if(TimeLine_List)
		{
			cout << "Command:                 ShareMemory(" << p->get_id();
			cout << ",\"" << text << "\")" << endl;

			TimeLine[TimeLine_List++] = new Memory(p, text);

		}
		
	}
	void See_memories(Post* p)
	{
		if(TimeLine_List)
		{
			cout << "Command:                   SeeYourMemories()" << endl << endl;
			cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl;
			cout << "\nOn this Day" << endl;

			int year = Date::CurrentDate.get_year() - p->GetSharedDate().get_year();
			cout << "(" << year << " Years Ago)" << endl;

			for (int i = 0; i < TimeLine_List; i++)
			{
				if ((TimeLine[i]->getday() == Date::CurrentDate.get_day()) && (TimeLine[i]->getmonth() == Date::CurrentDate.get_month()) && (Date::CurrentDate.get_year() - TimeLine[i]->GetSharedDate().get_year() != 0))
				{

					TimeLine[i]->ViewPOst();
				}
			}
		}
		

	 }
};

class facebook
{
private:
	page** PagesList;
	user** UsersList;
	user* CurrentUser;
	int numUsers;
	int numPages;

	Post** posts;
	char* Id;


	char* comment_id;
	char* text;
	char* postID;
	char* temp_Id;

public:
	facebook()
	{
		CurrentUser = nullptr;
		UsersList = nullptr;
		PagesList = nullptr;
		posts = nullptr;
		

		Id = NULL;
		numUsers = 0;
		numPages = 0;
		


		comment_id = 0;
		text = 0;
		postID = 0;
		temp_Id = 0;
	}

	~facebook()
	{
		if (UsersList) {
			for (int i = 0; i < numUsers; i++) {
				if(UsersList[i])
				delete UsersList[i];
			}
			delete[] UsersList;
		}
		if (PagesList) {
			for (int i = 0; i < numPages; i++) {
				if(PagesList[i])
					delete PagesList[i];
			}
			delete[] PagesList;
		}
		if (posts)
		{
			delete posts;
		}
	}
	
	user* SearchUser(char* ptr)
	{
		if (ptr)
		{
			for (int i = 0; i < 20; i++)
			{
				int a = Helper::CheckingStringsToBeMatched(UsersList[i]->get_id(), ptr);
				if (a == 1)
				{
					return UsersList[i];
				}
			}
		}
		

	}
	page* SearchPage(char* ptr)
	{
		
		for (int i = 0; i < 12; i++)
		{
			int a = Helper::CheckingStringsToBeMatched(PagesList[i]->get_id(), ptr);
			if (a == 1)
			{
				return PagesList[i];
			}
		}
	}
	Post* SearchPost(char* ptr)
	{
		if (ptr)
		{
			for (int i = 0; i < 12; i++)
			{
				int a = Helper::CheckingStringsToBeMatched(posts[i]->get_id(), ptr);
				if (a == 1)
				{
					return posts[i];
				}
			}
		}


	}
	Object* SearchObjectByID(char* ptr)
	{
		
		if(ptr[0]=='p')
		{
			return SearchPage(ptr);
		}
		else if (ptr[0] == 'u')
		{
			return SearchUser(ptr);
		}


	}
	

	void LoadPagesFromFile(fstream&);
	void LoadUsersFromFile(fstream&);
	
	void LoadComments(fstream&);
	void LoadPost(fstream&);

	void load();
};

void facebook::LoadPagesFromFile(fstream& PagesFile)
{
	int total;
	PagesFile >> total;
	PagesList = new page * [total];
	for (int i = 0; i < total; i++)
	{
		PagesList[i] = new page;
		PagesList[i]->ReadDataFromFile(PagesFile);
	}
}

void facebook::LoadUsersFromFile(fstream& Userfile)
{
	int ToTaL;
	Userfile >> ToTaL;

	char arr[20]="\0";

	char*** TempID = nullptr;

	TempID = new char** [ToTaL];

	UsersList = new user * [ToTaL];
	for (int i = 0; i < ToTaL; i++)
	{
		UsersList[i] = new user;
		UsersList[i]->ReadDataFromFile(Userfile);

		char temp[15] = "\0";
		

		TempID[i] = new char* [10];
		
		for (int index = 0; temp[0]!='-'; index++)
		{
			Userfile >> temp;
			if(Helper::Strcmp(temp, "-1") != 0)
			{
				TempID[i][index] = Helper::GetStringFromBuffer(temp);
				arr[i] = (index + 1);
			}
			
		}
		temp[0] = '\0';
		for (int index = 0; temp[0] != '-'; index++)
		{
			Userfile >> temp;
			if (Helper::Strcmp(temp, "-1") != 0)
			{
				page* ptr;
				ptr = SearchPage(temp);
				UsersList[i]->likedpage(ptr);
			}


		}
		temp[0] = '\0';
	}
	for (int i = 0; i < ToTaL; i++)
	{
		for (int index = 0; index < arr[i]; index++)
		{
			user* u_ptr;
			u_ptr = SearchUser(TempID[i][index]);
			UsersList[i]->AddFriend(u_ptr);
			delete[] TempID[i][index];
		}
		delete[] TempID[i];
	}
	delete[] TempID;
}

void facebook::LoadPost(fstream& Postfile)
{
	int Total = 0;
	Postfile >> Total;
	char temp[30] = {'\0'};

	posts = new Post * [Total];
	for (int i = 0; i < Total; i++)
	{
		posts[i] = new Post;
		posts[i]->ReadDataFromFile(Postfile);
	
		Postfile >> temp;
		Id = Helper::GetStringFromBuffer(temp);
		Object* sharedBy = SearchObjectByID(Id);
		posts[i]->SetSharedBy(sharedBy);
		sharedBy->AddPostToTimeline(posts[i]);


		Object* likedBy;

		temp[0] = '\0';
		
		for (int index = 0; temp[0] != '-'; index++)
		{
			Postfile >> temp;
			if (Helper::Strcmp(temp, "-1") != 0)
			{
				likedBy = SearchObjectByID(temp);
				posts[i]->Likedpost(likedBy);
			}
		}
	}

}

void facebook::LoadComments(fstream& Commentfile)  
{
	int Total=0;
	Commentfile >> Total;
	
	for (int i = 0; i < Total; i++)
	{
		
		Comments *coment  = new Comments;
	
		char temp[100];
		
		Commentfile >> temp;
		comment_id = Helper::GetStringFromBuffer(temp);
		Commentfile >> temp;
		postID = Helper::GetStringFromBuffer(temp);
		Post* postPtr = SearchPost(postID);
		postPtr->AddComment(coment);

		Commentfile >> temp;
		temp_Id= Helper::GetStringFromBuffer(temp);

		Object* comment_By = SearchObjectByID(temp_Id);
		
		Commentfile.ignore();

		Commentfile.getline(temp,100);
		text = Helper::GetStringFromBuffer(temp);
		
		coment->SetValues(comment_id, text, comment_By);
		
	}


}

void  facebook::load()
{
	fstream PagesFile("Pages(FB).txt");
	if (PagesFile)
	{
		LoadPagesFromFile(PagesFile);
		PagesFile.close();
	}
	else
	{
		cout << "Error! Failed to open file 'pages'." << endl;
		return;
	}

	fstream Userfile("Users(FB).txt");
	if (Userfile)
	{

		LoadUsersFromFile(Userfile);
		Userfile.close();
	}
	else
	{
		cout << "Error! Failed to open file 'Users'." << endl;
		return;
	}

	fstream Postfile("Post_Info(FB).txt");
	if (Postfile)
	{

		LoadPost(Postfile);
		Postfile.close();
	}
	else
	{
		cout << "Error! Failed to open file 'Post_Info'." << endl;
		return;
	}

	fstream Commentfile("Comments(FB).txt");
	if (Commentfile)
	{

		LoadComments(Commentfile);
		Commentfile.close();
	}
	else
	{
		cout << "Error! Failed to open file 'Comment'." << endl;
		return;
	}

}
int main()

{
	cout << "--------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "-----Welecome to Console-based Social Network Application-----" << endl << endl << endl;

	facebook fb;
	fb.load();


	Date current_Date(15, 11, 2017);
	Date::SetCurrentDate(current_Date);

	char arr[3] = "u7";
	user* CurrentUser = fb.SearchUser(arr);

	CurrentUser->viewFriend_list();
	CurrentUser->viewliked_Pages();

	cout << endl << endl << endl;


	CurrentUser->ViewHomeScreen();


	CurrentUser->ViewTimeLine();

	//Like Post
	char arr2[] = "post5";
	Post* PostPtr = fb.SearchPost(arr2);
	PostPtr->ViewlikeBy();

	Object* likedBy = fb.SearchObjectByID(arr);
	PostPtr->Likedpost(likedBy);
	PostPtr->ViewlikeBy();

	//Post Comment 
	char post[] = "post4";
	char comment[] = "Good Luck for your result";
	Post* PostPtr2 = fb.SearchPost(post);
	cout << "Command:                PostComment(" << post << "," << comment << ")" << endl;
	cout << "Command:                 PostComment(" << post << ")" << endl;
	CurrentUser->post_comment(PostPtr2, comment);
	PostPtr2->ViewPOst(0, 1);

	char post_[] = "post8";
	char comment_[] = "Thanks for the wishes";
	Post* PostPtr3 = fb.SearchPost(post_);
	cout << "Command:                PostComment(" << post_ << "," << comment_ << ")" << endl;
	cout << "Command:                 PostComment(" << post_ << ")" << endl;
	CurrentUser->post_comment(PostPtr3, comment_);
	PostPtr3->ViewPOst(1, 1);

	//SeeYourMemories
	char arrr[] = "post10";
	char ar[] = "Never thought I will be specialist in this field...";
	Post* PostPtr4 = fb.SearchPost(arrr);
	CurrentUser->See_memories(PostPtr4);
	CurrentUser->ShareYourMemory(PostPtr4, ar);
	CurrentUser->ViewTimeLine();

	//Pages
	cout << "-------------------------------------------------------------" << endl;
	char page_id[] = "p1";
	cout << "Command:                   ViewPage(" << page_id << ")" << endl;

	page* CurrentPage = fb.SearchPage(page_id);
	CurrentPage->viewPagepost();

	return 0;
	//
}