#include <iostream>
#include <string>
#include <vector>

using namespace std;


class ZAlgorithm 
{

    public:

        vector<int> calculateZ (string input)
        {
            vector<int> Z (input.length());
            int left = 0;
            int right = 0;
            for(int k = 1; k < input.length(); k++)
            {
                if(k > right)
                {

                    left = right = k;
                    while (right < input.length() && input[right] == input[right-left])
                    {
                        right++;
                    }
                    Z[k] = right - left;
                    right--;
                
                }
                else
                {
                    int k1 = k -left;
                    if (Z[k1]<right - k+1)
                    {
                        Z[k] = Z[k1];
                    
                    }
                    else
                    {
                        left = k;
                        while (right < input.length() && input[right] == input[right-left])
                        {
                            right++;
                        }
                        Z[k] = right - left;
                        right--;
                    
                    }
                
                }
            
            
            }
            return Z;
        
        }

        int match_pattern(string text, string pattern)
        {
            //String used to start matching using Z algorithm, contains the pattern$text we are comparing
            string new_string = pattern+"$"+text;
            vector<int> result;
            vector <int> Z = calculateZ(new_string); 
            int pattern_occurance = 0;

            for(int i= 0;i < Z.size();i++)
            {
                if(Z[i] == pattern.length())
                {
                    pattern_occurance++;
                }
            
            }
            return pattern_occurance;
        }






};



int main()
{
    string text = "bbbbb";
    string pattern = "bbb";

    ZAlgorithm *zAlgorithm = new ZAlgorithm();

    int result = zAlgorithm->match_pattern(text,pattern);

    cout<<result<<endl;
    return 0;
}
