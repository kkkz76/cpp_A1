#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio> 
#include <limits>
using namespace std;

// funcion declaration
void menu();
void configuration();
void readFile (string filename);
vector<string> tokenizeString (string input, string delimiter);
int fileLineCount(string filename);
void displayCityMap();
string** initializeMap();
void displayMatrix(string** cityMap);
void displayCloudIdx();
void displayCloudLMH();
void displayPressureIdx();
void displayPressureLMH();
void displayReport();
string checkLMH(double value);

// static varible declaration
static int callCount = 0;
static int gridCallCount = 0;

// struct declaration
struct cityLocationStruct{
    int xPoint;
    int yPoint;
    int id;
    string value;
    int lineCount;

};

struct cloudCoverStruct{
    int xPoint;
    int yPoint;
    int value;
    int lineCount;

};

struct pressureStruct{
    int xPoint;
    int yPoint;
    int value;
    int lineCount;

};
struct coordinateStruct{
    int gridXmax;
    int gridXmin;
    int gridXsize;
    int gridYmax;
    int gridYmin;
    int gridYsize;
};

// pointer declaration
cityLocationStruct *cityLocationArray;
cloudCoverStruct *cloudCoverArray;
pressureStruct *pressureArray;
coordinateStruct *coordinatearray;
string** cityMap;


int main(){
    menu();
}

// Display Menu Function
void menu(){
    bool loop_menu = true;
    while (loop_menu)
    {
        int choice;
        cout << "Student ID     : 8219035" << endl;
        cout << "Student Name   : Khant Ko Ko Zaw" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Welcome to Weather Information Processing System!" << endl;
        cout << "\n1)   Read in and process a configuration file" << endl;
        cout << "2)   Display city map"<< endl;
        cout << "3)   Display cloud coverage map (cloudiness index)" << endl;
        cout << "4)   Display cloud coverage map (LMH symbols)" << endl;
        cout << "5)   Display atmospheric pressure map (pressure index)" << endl;
        cout << "6)   Display atmospheric pressure map (LMH symbols)" << endl;
        cout << "7)   Show weather forecast summary report" << endl;
        cout << "8)   Quit" << endl;
        cout << "\nPlease enter your choice : ";
        cin >> choice;
        
      if(!cin){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << endl;
        cout << "Enter a valid option number only"<<endl;
        cout << endl;
        }else{
        switch (choice)
        {
        case 1:
            cout << "\n[ Read in and process a configuration file ]" << endl;
            configuration();
            break;
        case 2:
            cout << "2" << endl;
            displayCityMap();
            break;
        case 3:
            cout << "3" << endl;
            displayCloudIdx();
            break;
        case 4:
            cout << "4" << endl;
            displayCloudLMH();
            break;
        case 5:
            cout << "5" << endl;
            displayPressureIdx();
            break;
        case 6:
            cout << "6" << endl;
            displayPressureLMH();
            break;
        case 7:
            cout << "7" << endl;
            displayReport();
            break;
        case 8:
            cout << "8" << endl;
            loop_menu = false;
            break;
        
        default:
            cout << endl;
            cout << "Wrong Option.Try again!!!" << endl;
            cout << endl;
            break;
        }
        }
      
    }
}

// config file read function
void configuration(){
    string configfile;
    int min;
    int max;
    int gridsize;

    cout << endl;
    cout << "Please enter your config filename : ";
    cin >> configfile;
    fstream targetFile (configfile.c_str(), fstream::in);
    string aLine;
    cout << endl;
    while (getline (targetFile, aLine))
    {
		cout << aLine << endl;
        size_t pos = aLine.find(".txt");
        size_t gridPos = aLine.find("=");
        
        if (pos != string::npos){
            readFile (aLine);
        }
        else if(gridPos != string::npos){
            vector<string> tokenStringVector = tokenizeString (aLine, "=");
            vector<string> tokenStringVector1 = tokenizeString (tokenStringVector[1], "-");
            min = stoi(tokenStringVector1[0]);
            max = stoi(tokenStringVector1[1]);
            gridsize =(max-min)+1;

            if(gridCallCount == 0){
                coordinatearray = new coordinateStruct[1];
                coordinatearray[0].gridXmax = max;
                coordinatearray[0].gridXmin = min;
                coordinatearray[0].gridXsize = gridsize;
                gridCallCount++;
            }else{
                coordinatearray[0].gridYmax = max;
                coordinatearray[0].gridYmin = min;
                coordinatearray[0].gridYsize = gridsize;
                gridCallCount = 0;
            }
            tokenStringVector.clear();
            tokenStringVector1.clear();
        }
	}


    targetFile.ignore();
    targetFile.close();


    cout << endl;
    cout << "for city"<< endl;

    for (int i=0; i< 14; i++){
        cout << cityLocationArray [i].id << endl;
        cout << cityLocationArray [i].value << endl;
        cout << cityLocationArray [i].xPoint << endl;
        cout << cityLocationArray [i].yPoint << endl;
        cout << endl;
    }
    cout << endl;
    cout << "for cloud"<< endl;
    for (int j=0; j<81; j++){
       
        cout << cloudCoverArray [j].value << endl;
        cout << cloudCoverArray [j].xPoint << endl;
        cout << cloudCoverArray [j].yPoint << endl;
        cout << endl;
    }
    cout << endl;
    cout << "for pressure"<< endl;
    for (int k=0; k<81; k++){
     
        cout << pressureArray [k].value << endl;
        cout << pressureArray [k].xPoint << endl;
        cout << pressureArray [k].yPoint << endl;
        cout << endl;
    }
		
    cout << endl;
    cout << "for coordinate"<< endl;
    cout<< coordinatearray[0].gridXmax << endl;
    cout<< coordinatearray[0].gridXmin << endl;
    cout<< coordinatearray[0].gridXsize << endl;
    cout<< coordinatearray[0].gridYmax << endl;
    cout<< coordinatearray[0].gridYmin << endl;
    cout<< coordinatearray[0].gridYsize << endl;
    cout << endl;
    
}

// read a single file from config file function
void readFile(string filename){
    
    fstream targetFile (filename.c_str(), fstream::in);
    cout << endl;
    cout << "Reading file : " << filename << endl;
    cout << endl;
    string aLine;
    string coordinates;
    vector<string> tokenStringVector;
    vector<string> tokenCoordinates;
    int arrayCount = 0;
    int lineCount = fileLineCount(filename);
    if(callCount == 0){
        
        cityLocationArray = new cityLocationStruct [lineCount];
        callCount++;
        while (getline(targetFile, aLine))
    {
        tokenStringVector = tokenizeString (aLine, "-");
        coordinates = tokenStringVector[0];
        tokenCoordinates = tokenizeString (coordinates, ",");
        cityLocationArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        cityLocationArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        cityLocationArray[arrayCount].id = stoi(tokenStringVector[1]);
        cityLocationArray[arrayCount].value = tokenStringVector[2];
        cityLocationArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
       
    }
    
    }else if(callCount == 1){
       
        cloudCoverArray = new cloudCoverStruct [lineCount];
        callCount++;
        while (getline(targetFile, aLine))
    {
        vector<string> tokenStringVector = tokenizeString (aLine, "-");
        string coordinates = tokenStringVector[0];
        vector<string> tokenCoordinates = tokenizeString (coordinates, ",");
        cloudCoverArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        cloudCoverArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        cloudCoverArray[arrayCount].value = stoi(tokenStringVector[1]);
        cloudCoverArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
       
    }
       
    }else if (callCount == 2){
         
       pressureArray = new pressureStruct[lineCount];
       callCount=0; // reset call count
        while (getline(targetFile, aLine))
    {
        vector<string> tokenStringVector = tokenizeString (aLine, "-");
        string coordinates = tokenStringVector[0];
        vector<string> tokenCoordinates = tokenizeString (coordinates, ",");
        pressureArray[arrayCount].xPoint = stoi(tokenCoordinates[0]);
        pressureArray[arrayCount].yPoint = stoi(tokenCoordinates[1]);
        pressureArray[arrayCount].value = stoi(tokenStringVector[1]);
        pressureArray[arrayCount].lineCount = lineCount;
        arrayCount++;
        targetFile.ignore();
    }}

    tokenCoordinates.clear();
    tokenStringVector.clear();
}

// calculate the total size of file function
int fileLineCount(string filename){
    fstream targetFile (filename.c_str(), fstream::in);
    string aLine;
    int lineCount = 0;
    while (getline(targetFile, aLine)){
        lineCount++;
        targetFile.ignore();
    }
    return lineCount;
}

// separate string function
vector<string> tokenizeString (string input, string delimiter){
	size_t pos = 0;
	string token;
	vector<string> result;
    if(delimiter == ","){
        input.erase(remove(input.begin(), input.end(), '['), input.end());
	    input.erase(remove(input.begin(), input.end(), ']'), input.end());
	    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    }
    while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);
    return (result);
}

// initialize the coordinate
string ** initializeMap(){
    cityMap = new string*[coordinatearray[0].gridXsize];
    
    for (int x = coordinatearray[0].gridXmin; x < coordinatearray[0].gridXsize; ++x) {
        cityMap[x] = new string[coordinatearray[0].gridYsize];
        for (int y = coordinatearray[0].gridYmin; y < coordinatearray[0].gridYsize; ++y) {
            cityMap[x][y] = " ";
        }
    }
    return cityMap;
}



void displayMatrix(string** cityMap){

    cout << "\n\n\n\n";
    string Border = " \t";
    for (int i = coordinatearray[0].gridXmin; i < coordinatearray[0].gridXsize+1; i++)
    {
       Border += "#\t";
      
    }
    cout <<Border<<endl;
    cout << "\n\n\n";
    
    for(int y =coordinatearray[0].gridYmax; y>=coordinatearray[0].gridYmin;y--){
        cout << to_string(y) + "\t#\t";
            
        for(int x =coordinatearray[0].gridXmin; x<coordinatearray[0].gridXsize;x++){
             cout <<  (cityMap)[x][y] <<"\t";
        }
        cout << "#";
       cout << "\n\n\n";
    }
    cout <<Border<<endl;
    cout << "\n\n\n";
    cout << " \t \t";
    for (int i = coordinatearray[0].gridXmin; i < coordinatearray[0].gridXsize; i++)
    {
        cout <<to_string(i)+"\t";
    }
   cout << "\n\n\n\n";

}
    
void displayCityMap(){

    string** cityMap = initializeMap();

    for (int i = 0; i < cityLocationArray->lineCount; i++)
    {
        cityMap[cityLocationArray[i].xPoint][cityLocationArray[i].yPoint] = to_string(cityLocationArray[i].id);
    }
    displayMatrix(cityMap);
    
}


void displayCloudIdx(){
    string** cityMap = initializeMap();
    int value =0;
    int* valueptr = &value;
    for (int i = 0; i < cloudCoverArray[0].lineCount; i++)
    {   
        if(cloudCoverArray[i].value >=0 && cloudCoverArray[i].value <10 ){
            *valueptr = 0;
        }else if (cloudCoverArray[i].value >=10 && cloudCoverArray[i].value <20)
        {
            *valueptr = 1;
        }else if (cloudCoverArray[i].value >=20 && cloudCoverArray[i].value <30)
        {
            *valueptr = 2;
        }else if (cloudCoverArray[i].value >=30 && cloudCoverArray[i].value <40)
        {
            *valueptr = 3;
        }else if (cloudCoverArray[i].value >=40 && cloudCoverArray[i].value <50)
        {
            *valueptr = 4;
        }else if (cloudCoverArray[i].value >=50 && cloudCoverArray[i].value <60)
        {
            *valueptr = 5;
        }else if (cloudCoverArray[i].value >=60 && cloudCoverArray[i].value <70)
        {
            *valueptr = 6;
        }else if (cloudCoverArray[i].value >=70 && cloudCoverArray[i].value <80)
        {
            *valueptr = 7;
        }else if (cloudCoverArray[i].value >=80 && cloudCoverArray[i].value <90)
        {
            *valueptr = 8;
        }else if (cloudCoverArray[i].value >=90 && cloudCoverArray[i].value <100)
        {
            *valueptr = 9;
        }else{
            *valueptr = 10;
        }      
        cityMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = to_string(*valueptr);
    }
    cout << "\n\n\n";
    cout << "Cloud Coverage Map (cloudiness Index )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
  
   
}

void displayCloudLMH(){
    string** cityMap = initializeMap();
    string value;
    string* valueptr = &value;
    for (int i = 0; i < cloudCoverArray[0].lineCount; i++)
    {   
        if(cloudCoverArray[i].value >=0 && cloudCoverArray[i].value <35 ){
            *valueptr = "L";
        }else if (cloudCoverArray[i].value >=35 && cloudCoverArray[i].value <65)
        {
            *valueptr = "M";
        }else if (cloudCoverArray[i].value >=65 && cloudCoverArray[i].value <100)
        {
            *valueptr = "H";
        }else{
            *valueptr = "uk";
        }      
        cityMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = *valueptr;
    }
    cout << "\n\n\n";
    cout << "Cloud Coverage Map (LMH Symbols )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    
}


void displayPressureIdx(){
    string** cityMap = initializeMap();
    int value =0;
    int* valueptr = &value;
    for (int i = 0; i < pressureArray[0].lineCount; i++)
    {   
        if(pressureArray[i].value >=0 && pressureArray[i].value <10 ){
            *valueptr = 0;
        }else if (pressureArray[i].value >=10 && pressureArray[i].value <20)
        {
            *valueptr = 1;
        }else if (pressureArray[i].value >=20 && pressureArray[i].value <30)
        {
            *valueptr = 2;
        }else if (pressureArray[i].value >=30 && pressureArray[i].value <40)
        {
            *valueptr = 3;
        }else if (pressureArray[i].value >=40 && pressureArray[i].value <50)
        {
            *valueptr = 4;
        }else if (pressureArray[i].value >=50 && pressureArray[i].value <60)
        {
            *valueptr = 5;
        }else if (pressureArray[i].value >=60 && pressureArray[i].value <70)
        {
            *valueptr = 6;
        }else if (pressureArray[i].value >=70 && pressureArray[i].value <80)
        {
            *valueptr = 7;
        }else if (pressureArray[i].value >=80 && pressureArray[i].value <90)
        {
            *valueptr = 8;
        }else if (pressureArray[i].value >=90 && pressureArray[i].value <100)
        {
            *valueptr = 9;
        }else{
            *valueptr = 10;
        }
        cityMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = to_string(*valueptr);
    }
    cout << "\n\n\n";
    cout << "Atmospheric Pressure Map (Pressure Index )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
    
}

void displayPressureLMH(){
    string** cityMap = initializeMap();
    string value;
    string* valueptr = &value;
    for (int i = 0; i < pressureArray[0].lineCount; i++)
    { 

        if(pressureArray[i].value >=0 && pressureArray[i].value <35 ){
            *valueptr = "L";
        }else if (pressureArray[i].value >=35 && pressureArray[i].value <65)
        {
            *valueptr = "M";
        }else if (pressureArray[i].value >=65 && pressureArray[i].value <100)
        {
            *valueptr = "H";
        }else{
            *valueptr = "uk";
        }       
        cityMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = *valueptr;
    }
    cout << "\n\n\n";
    cout << "Atmospheric Pressure Map (LMH Symbols )" << endl;
    cout << "\n\n\n";
    displayMatrix(cityMap);
   
}


void displayReport(){
    
    map<pair<int, string>, set<pair<int, int>>> cityMap;
    for (int i = 0; i < cityLocationArray->lineCount; i++)
    {
        int x = cityLocationArray[i].xPoint;
        int y = cityLocationArray[i].yPoint;
        int id = cityLocationArray[i].id;
        string name = cityLocationArray[i].value;

        pair<int,int> cityData(x,y);
        pair<int,int> cityData1(x-1,y);
        pair<int,int> cityData2(x+1,y);
        pair<int,int> cityData3(x,y-1);
        pair<int,int> cityData4(x,y+1);
        pair<int,int> cityData5(x-1,y+1);
        pair<int,int> cityData6(x+1,y+1);
        pair<int,int> cityData7(x+1,y-1);
        pair<int,int> cityData8(x-1,y-1);
        
        cityMap[{id,name}].insert(cityData);
        if (cityData1.first <= coordinatearray->gridXmax && cityData1.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData1);
        }
        if (cityData2.first <= coordinatearray->gridXmax && cityData2.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData2);
        }
        if (cityData3.first <= coordinatearray->gridXmax && cityData3.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData3);
        }
        if (cityData4.first <= coordinatearray->gridXmax && cityData4.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData4);
        }
        if (cityData5.first <= coordinatearray->gridXmax && cityData5.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData5);
        }
        if (cityData6.first <= coordinatearray->gridXmax && cityData6.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData6);
        }
        if (cityData7.first <= coordinatearray->gridXmax && cityData7.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData7);
        }
        if (cityData8.first <= coordinatearray->gridXmax && cityData8.second <= coordinatearray->gridYmax){
             cityMap[{id,name}].insert(cityData8);
        }
    }

    string** cloudMap = initializeMap();
    string** pressureMap = initializeMap();
    for (int i = 0; i < cloudCoverArray[0].lineCount; i++)
    {        
        cloudMap[cloudCoverArray[i].xPoint][cloudCoverArray[i].yPoint] = to_string(cloudCoverArray[i].value);
    }
    for (int i = 0; i < pressureArray[0].lineCount; i++)
    {        
        pressureMap[pressureArray[i].xPoint][pressureArray[i].yPoint] = to_string(pressureArray[i].value);
    }
    cout << endl;
    cout << "Weather Forecast Summary Report" << endl;
    cout << "---------------------------------";
    for (const auto& entry : cityMap) {
        double acc = 0.00;
        double ap = 0.00;
        string accLMH = "";
        string apLMH ="";
        double rain = 0;
        string rainGraphic = "";
        for (const auto& coordinates : entry.second) {
            double valueAcc = stod(cloudMap[coordinates.first][coordinates.second]);
            double valueAp = stod(pressureMap[coordinates.first][coordinates.second]);
            acc += valueAcc;
            ap += valueAp;
        }
        acc = acc / entry.second.size();
        ap = ap / entry.second.size();
        accLMH = checkLMH(acc);
        apLMH = checkLMH(ap);

        if(apLMH == "L" and accLMH == "H"){
            rain = 90.00;
            rainGraphic = "~~~~\n~~~~~\n\\\\\\\\\\";
        }else if(apLMH == "L" and accLMH == "M"){
            rain = 80.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\\\\\";
        }else if(apLMH == "L" and accLMH == "L"){
            rain = 70.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\\\";
        }else if(apLMH == "M" and accLMH == "H"){
            rain = 60.00;
            rainGraphic = "~~~~\n~~~~~\n \\\\";
        }else if(apLMH == "M" and accLMH == "M"){
            rain = 50.00;
            rainGraphic = "~~~~\n~~~~~\n\\";
        }else if(apLMH == "M" and accLMH == "L"){
            rain = 40.00;
            rainGraphic = "~~~~\n~~~~~";
        }else if(apLMH == "H" and accLMH == "H"){
            rain = 30.00;
            rainGraphic = "~~~\n~~~~";
        }else if(apLMH == "H" and accLMH == "M"){
            rain = 20.00;
            rainGraphic = "~~\n~~~\n \\\\\\\\";
        }else if(apLMH == "H" and accLMH == "L"){
            rain = 10.00;
            rainGraphic = "~\n~~\n \\\\\\\\";
        }
        cout << endl;
        cout << "City Name : " << entry.first.second <<endl;
        cout << "City ID   : " << entry.first.first <<endl;

        printf("Ave. Cloud Cover (ACC)   : %.2f (%s)\n", acc,accLMH.c_str());
        printf("Ave. Pressure    (Ap)    : %.2f (%s)\n", ap,apLMH.c_str());
        printf("Probability of Rain (%)  : %.2f\n",rain);
        cout<<rainGraphic<<endl;
        cout << endl;
    }
}


string checkLMH(double value){
    string LMH = "";

     if(value >=0 && value <35 ){
            LMH = "L";
        }else if (value>=35 && value <65)
        {
            LMH = "M";
        }else if (value >=65 && value <100)
        {
            LMH = "H";
        }
    return LMH;

}



