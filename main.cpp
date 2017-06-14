//Scott Balchin 14/6/17
//C++ 11, compiled with clang++ main.cpp -O3 -g -pg -std=c++11 -o main.exe
//Code which takes as input a list of 8x8 matrices and checks strong coincidence on a random sample of their realisations.
//Code is optimised for 8x8, but can be adjusted accordingly for higher dimensions or for a general setting.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

//This function checks to see if two strings have the same abelianisation up to a position m
bool abl(std::string s1, std::string s2, const unsigned& m){
    if(m==0){return true;}
    s1.resize(m-1);
    s2.resize(m-1);
    std::sort(s1.begin(),s1.end());
    std::sort(s2.begin(),s2.end());
    for(unsigned i=0; i<s1.size(); ++i){
        if(s1[i] != s2[i]){return false;}
    }
    return true;
}

//The class for a substitution data type
class sub{
private:
    std::vector<std::string> S;
    
public:
	//Constructors
    sub(const std::vector<std::string> & rhs){S = rhs;}
    
    sub(const unsigned& s){
        for(unsigned i=0; i<s; ++i)
            S.push_back("");
    }
    
    //Accessor
    const std::string operator[](const unsigned& i) const {return S[i];}
              
	//Printing Operator (for easy printout of results)  
    friend std::ostream& operator<<(std::ostream& lhs, sub& rhs) {
        std::vector<char> a = {'a','b','c','d','e','f','g','h'};
        for(unsigned i=0; i<a.size(); ++i)
            lhs << a[i] << " ⟶   " << rhs[i] << std::endl;
        
        return lhs;
    }
    
    //Performing a substitution on a single character
    std::string subst(const char& rhs){return S[int(rhs)-97];}
    
	//Performing all substitutions on a string
    std::string rep(const std::string& rhs) {
        std::string res;
        for(unsigned i=0; i<rhs.size(); ++i){res.append(this->subst(rhs[i]));}
        return res;
    }
        
    //Checking for strong coincidence
    bool scoin() {
    	std::vector<char> A = {'a','b','c','d','e','f','g','h'};
        std::vector<std::string> B = S;
        //Note that here we have set the maximum iterations to 20-A.size = 12, this has not caused any false positives for over 130k substitutions.
        for(unsigned iters=0; iters<20-A.size(); ++iters){
            unsigned counter = 0;
            for(unsigned i=0; i<A.size(); ++i)
                for(unsigned j=i+1; j<A.size(); ++j){
                    bool match = false;
                    while(match == false){
                        unsigned m = std::min(B[i].size(),B[j].size());
                        for(unsigned k=0; k<m; ++k)
                            if(B[i][k]==B[j][k]){
                                if(abl(B[i],B[j],k)){
                                    match = true;
                                    counter++;
                                    if(counter == A.size()*(A.size()-1)/2)
                                        return true;
                                    break;
                                }
                            }
                        break;
                    }
                }
            for(unsigned iters1=0; iters1<B.size(); ++iters1)
                B[iters1]=this->rep(B[iters1]);
        }
        return false;
    }
};

//Random number generator function
int RNG (int i) { return std::rand()%i;}
int main() {

//Initialise the RNG stream
std::srand ( unsigned ( std::time(0) ) );
	
	//Open the data file where matrixes are stored in the following way:
	//{{0,1,1,1,1,0,1,1},{1,1,1,1,1,1,1,0},{0,1,1,0,1,0,1,0},{0,1,1,0,0,1,0,0}, {1,1,1,1,1,0,1,1},{0,1,0,1,1,0,1,1},{1,0,0,1,0,1,1,0},{0,1,0,1,0,0,1,1}}
    std::ifstream input( "data.txt" );
    
	unsigned total = 1;
	
	//Begin by reading in the first matrix in the file into a C++ "matrix"
	for( std::string line; getline( input, line ); ){    
    	std::vector<std::vector<unsigned>> extracted;    	
    	std::vector<unsigned> temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
    	for(unsigned i=0; i<8; ++i){
    		temp1.push_back((int)line[2+2*i]-48);
    		temp2.push_back((int)line[20+2*i]-48);
    		temp3.push_back((int)line[38+2*i]-48);
    		temp4.push_back((int)line[56+2*i]-48);
    		temp5.push_back((int)line[74+2*i]-48);
    		temp6.push_back((int)line[92+2*i]-48);
    		temp7.push_back((int)line[110+2*i]-48);
    		temp8.push_back((int)line[128+2*i]-48);
    		}
    	extracted.push_back(temp1);
    	extracted.push_back(temp2);
    	extracted.push_back(temp3);
    	extracted.push_back(temp4);
    	extracted.push_back(temp5);
    	extracted.push_back(temp6);
    	extracted.push_back(temp7);
    	extracted.push_back(temp8);
    	
    	//'store' is the first realisation of the matrix we consider
    	std::vector<std::string> store;   	
    	for(unsigned i=0; i<extracted.size(); ++i){
    		std::string a;
    		for(unsigned j=0; j<extracted[i].size(); ++j){
    			for(unsigned k=0; k<extracted[i][j]; ++k){
    				char q = (char)97+j;
    				std::stringstream ss;
					std::string s;
					ss << q;
					ss >> s;
    				a += s;
    			}		
    		}
    		store.push_back(a);
    	} 
    	
    	unsigned counter = 0;
    	
    	while(counter < 1000){
    		//We shuffle each substitution rule appearing in the realisation, giving a new substitution with the same abelianisation
			for(unsigned i=0; i<store.size(); ++i)
				std::random_shuffle(store[i].begin(), store[i].end(), RNG); 
			sub K(store);  
			
			std::cout << "Checking Sub #" << total << ":" << std::endl << K <<std::endl;
    		
    		//We then check the substitution for strong coincidence
    		if(!K.scoin()){
    			//If it is NOT strongly coincident, we print the substitution and terminate the code.
    			std::cout << K << std::endl;
    			return 1;
    		}
    		counter++; total++;	    		
    	}
	}
    return 0;
}
