#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "main.h"

using namespace std;

int findNextPrime(int n);
bool isPrime(int n);

int main(int argc, const char * argv[]) {
        
        if(!argv[1]){
            throw logic_error("error: dictionary file");
        }
        if(!argv[2]){
            throw logic_error("error: input file");
        }
        
        // Read in arguments
        string dict = argv[1];
        string input = argv[2];
        
        // Open dictionary file
        ifstream dictFile;
        dictFile.open(dict.c_str());
        
        // Check if dictFile are able to open
        if(!dictFile){
            cerr << "Unable to open file" << endl;
        }
        
        // Open input file
        ifstream inputFile;
        inputFile.open(input.c_str());
        
        // Check if inputFile are able to open
        if(!inputFile){
            cerr << "Unable to open file" << endl;
        }
        
        int primeSize = 0;
        int numOfElements = 0;

        string element = "$";
        while(dictFile >> element){
            numOfElements++;
        }
    
        primeSize = findNextPrime(numOfElements);
    
        dictFile.close();
    
        clock_t startConstruct;
        clock_t endConstruct;
        double totalTimeConstruct = 0;
        
        startConstruct = clock();
        
        // Create hash table
        HashTable<string> test1(primeSize);
        
        // Read in elements
        dictFile.open(dict.c_str());
        while(dictFile >> element){
            test1.insert(element);
        }
        
        endConstruct = clock();
        totalTimeConstruct = ((double)(endConstruct - startConstruct)/CLOCKS_PER_SEC);
        
        unsigned correct = 0;
        unsigned total = 0;
        
        clock_t startRetrieve;
        clock_t endRetrieve;
        double totalTimeRetrieve = 0;
        
        startRetrieve = clock();
        
        while(inputFile >> element){
            total++;
            // if found
            if(test1.search(element) == true){
                correct++;
            }
            // if not found
            else{
                // remove punctuation
                for(unsigned i = 0; i < element.length(); i++){
                    if(ispunct(element[i])){
                        element.erase(i--,1);
                    }
                }
                // search
                if(test1.search(element) == true){
                    correct++;
                }
                else{
                    // remove capitals
                    for(unsigned i = 0; i < element.length(); i++){
                        if(isupper(element[i])){
                            element[i] = tolower(element[i]);
                        }
                    }
                    // search
                    if(test1.search(element) == true){
                        correct++;
                    }
                    else{
                        element[0] = toupper(element[0]);
                        if(test1.search(element) == true){
                            correct++;
                        }
                    }
                }
            }
        }
        
        endRetrieve = clock();
        totalTimeRetrieve = ((double)(endRetrieve - startRetrieve)/CLOCKS_PER_SEC);

        int incorrect = total - correct;
        //cout << "Total words: " << total << endl;
        //cout << "Correct words: " << correct << endl;
        cout << "Mispelled words: " << incorrect << endl;
        cout << "Total Construction Time: " << totalTimeConstruct << endl;
        cout << "Total Retrieval Time: " << totalTimeRetrieve << endl;
        
    return 0;
    
}

int findNextPrime(int n){
    int nextPrime = n;
    bool found = false;
    
    while(!found){
        nextPrime++;
        if(isPrime(nextPrime)){
            found = true;
        }
    }
    return nextPrime;
}

bool isPrime(int n){
    for(int i = 2; i <= n/2; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
