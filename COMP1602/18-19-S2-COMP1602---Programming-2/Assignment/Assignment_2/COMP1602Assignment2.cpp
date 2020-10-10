#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;


struct Date{
    int day;
    int month;
    int year;
};


Date getCurrentDate(){
    Date d;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    d.day   = aTime->tm_mday;
    d.month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    d.year  = aTime->tm_year + 1900;

    return d;
}

//write structure definitions here



struct Actor{
    string id;
    string fname;
    string lname;
    char gender;
    int age; 
    string PoB;
  
};

struct Movie{
    int MovieId;
    string name;
    long int gross;
    double rating;
    Date releaseDate;
};

struct Cast{
    int MovieId;
    string actorId;
    string role;
};







//write print functions to print the details of each structure
void printActor(Actor actor){
    cout<<actor.id<<"\t"<<actor.fname<<"\t"<<actor.lname<<"\t"<<actor.gender<<"\t"<<actor.age<<"\t"<<actor.PoB<<endl;
}


void printActors(Actor actors[], int numActors){
    for(int i=0; i<numActors; i=i+1){
        printActor(actors[i]);
    }


}



//This function reads the data from the file actors.txt and creates Actor structures and inserts them in an array of Actor structures.
//The function accepts the array of Actor structures and returns the number of elements in the array.

int loadActors(Actor actors[]){
    ifstream in;
    in.open("actors.txt");
    if(!in.is_open()){
        cout<<"Error opening file, Aborting!"<<endl;
        return -1;
    }
    Actor temp;
    int count=0;
    in>>temp.id;
    while(temp.id != "END"){
        in>>temp.fname>>temp.lname>>temp.gender>>temp.age>>temp.PoB;
        actors[count]=temp;
        count=count+1;
        in>>temp.id;
    }
    in.close();
    return count;
}




//This function reads the data from the file movies.txt and creates Movie structures and inserts them in an array of Movie structures.
//The function accepts the array of Movie structures and returns the number of elements in the array.
int loadMovies (Movie movies[]){
}

//This function reads the data from the file cast.txt and creates Cast structures and inserts them in an array of Cast structures.
//The function accepts the array of Cast structures and returns the number of elements in the array.
int loadCast(Cast casts[]){
}

//This function prints the menu options and prompts the user to enter a choice.
void printMenu(){
}

//This function searches the array of Actor structures for a given actor id. If the Actor with that actor id is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorById(Actor actors[], int numActors, string actorId){
}


//This function searches the array of Actor structures for a given actor by their name. If the Actor with that name is found, the function returns the location in the array
//where the actor was found. If the actor is not found, the function returns -1.
int searchActorByName(Actor actors[], int numActors, string fName, string lName){
}


//This function searches the array of Movie structures for a given movie by their name. If the Movie with that name is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieByName(Movie movies[], int numMovies, string movieName){
}


//This function searches the array of Movie structures for a given movie id. If the Movie with that movie id is found, the function returns the location in the array
//where the movie was found. If the movie is not found, the function returns -1.
int searchMovieById(Movie movies[], int numMovies, int movieId){
}


// This functions searches for a movie. If the movie is found all of the information pertaining to the movie is printed.
// If it is not found an appropriate error message is printed.
void option1(Movie movies[], int numMovies, string movieName){
}

//This functions searches for a movie by name and prints the list of all the actors and the roles they played in the movie.
void option2(Movie movies[], int numMovies, string movieName, Actor actors[], int numActors,Cast casts[], int numEntries){
}


//This functions searches for an actor's name and list the name of the movie (s) and roles(s) played in the movie of all the movies the actor has acted
//in if the actor exists. If the actor exists but has not acted in any of the listed movies, display "Actor has not acted in any movie."
//If the actor does not exist, display an appropriate message.
void option4(Movie movies[], int numMovies, Actor actors[], int numActors,Cast casts[], int numEntries, string fName, string lName){
}

// This functions searches for an actor by name. If the actor is found all of the information pertaining to the actor is printed.
// If it is not found an appropriate error message is printed.
void option3 (Actor actors[], int numActors, string fName, string lName){
}

//This function searches for and prints the names of all movies released within the last month.
void option5(Movie movies[], int numMovies){
}


//This function searches for and prints the  name(s) of the movies and the release date of all the movies that have not been released yet.
void option6(Movie movies[], int numMovies){
}


//This function searches for and prints the names of all movies with a star rating of 8.0 or more that have grossed over 1 billion dollars.
void option7(Movie movies[], int numMovies){
}

int main(){

    int numActors ;
    Actor actors[100];
    Movie movie[100];
    Cast cast[1000];

    numActors=loadActors(actors);
    printActors(actors ,numActors);












}
