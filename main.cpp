#include <stdlib.h>
#include <libpq-fe.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "db.h"




  

int main(int argc,const char *argv[]){
  ifstream file;
  string arg;
  //if(!test())
    //exit(0);
  if(argc==1){
    printf("Usage:\n");
    printf("\t\tdbimp  [options] <infile>\n");
    printf("Options\n");
    printf("\t\t-del delete table contents before import\n");
    printf("\t\t-u  database user\n");
    printf("\t\t-p  password\n");
    printf("\t\t-h  database host\n");
    printf("\t\t-d  database name\n");
    exit(1);
  }


  for(int i=1;i<argc-1;i+=2){
    arg=argv[i];
    if(arg.compare("-del")==0){
      deletedb=true;

    }
    else if(arg.compare("-u")==0){
      user=argv[i+1];
    }
    else if(arg.compare("-p")==0){
      password=argv[i+1];
    }
    else if(arg.compare("-h")==0){
      host=argv[i+1];
    }
    else if(arg.compare("-d")==0){
      dbname=argv[i+1];
    }
    else{
        printf("Usage:\n");
        printf("\t\tdbimp  [options] <infile>\n");
        printf("Options\n");
        printf("\t\t-del delete table contents before import\n");
        printf("\t\t-u  database user\n");
        printf("\t\t-p  password\n");
        printf("\t\t-h  database host\n");
        printf("\t\t-d  database name\n");
        exit(1);
    }
  }
  arg=argv[argc-1];
  file.open(arg.c_str(), ifstream::in);
  if(!file){
    printf("Usage:\n");
    printf("\t\tdbimp  [options] <infile>\n");
    printf("Options\n");
    printf("\t\t-del delete table contents before import\n");
    printf("\t\t-u  database user\n");
    printf("\t\t-p  password\n");
    printf("\t\t-h  database host\n");
    printf("\t\t-d  database name\n");
    exit(1);
  }
  db_login(user,password,host,dbname);
  string vorname,nachname,geburt,mtnr,line,token;
  vector <string> tupel;
  int count=0,imported=0;


  while(getline(file,line)){
    tupel.clear();
    while (line.find(";", 0) != string::npos)
      { 
        size_t  pos = line.find(";", 0); //store the position of the delimiter
        token = line.substr(0, pos);          //get the token
        line.erase(0, pos + 1);                 //erase it from the source 
        tupel.push_back(token);                //and put it into the array
      }

      tupel.push_back(line);           //the last token is all alone 
    
    if(tupel[0].compare("")==0||tupel[1].compare("")==0||tupel[2].compare("")==0||tupel[3].compare("")==0){
      printf("Import Data incorrect, no undefined fields allowed\n");
      exit(1);
      
    }
    count++;
    if(deletedb){
      db_delete();
      deletedb=false;
    }
    if(db_insert(tupel[3],tupel[0],tupel[1],tupel[2])==0){
      imported++;
    }
  }
  printf("Data read: %i\nData imported:%i\n",count,imported);
}

  


  



