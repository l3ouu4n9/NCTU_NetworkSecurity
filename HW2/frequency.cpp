#include <iostream>
#include <map>
#include <vector>

using namespace std;

int cmp(const pair<char, int>& x, const pair<char, int>& y)    
{    
    return x.second > y.second;    
}

void sortMapByValue(map<char, int>& tMap,vector<pair<char, int> >& map_vec)    
{    
    for (map<char, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)     
        map_vec.push_back(make_pair(curr->first, curr->second));      
     
    sort(map_vec.begin(), map_vec.end(), cmp);    
}  


int main(int argc, char* argv[]){

	int length = atoi(argv[1]);
  	cout << "Testing key length : " << length << endl;

  	map<char, int> table[length];
    
    char ch;
    FILE* target_file = fopen("decrypt", "r+b");
    int size[length];

    for(int i = 0;i < length; ++i){
    	size[i] = 0;
    }

    int i = 0;
    while ((ch = fgetc(target_file)) != EOF)
    {
      if (table[i].find(ch) != table[i].end()){
 			table[i][ch]++;
      }
      else{
 			table[i][ch] = 1;
      }
      size[i]++;
      i = (i + 1) % length ;
    }

    for(int j = 0; j < length; ++j){
	    vector<pair<char,int> > map_vec;    
	    sortMapByValue(table[j], map_vec);
	    printf("%d Character\n", (j + 1));
	    for(int i = 0;i < map_vec.size(); ++i)
	    	printf("\tChar: %02x, Frequency: %f\n", map_vec[i].first, (((float)map_vec[i].second)/size[j])*100); 

	    map_vec.clear();
	}

    fclose(target_file);
	
}