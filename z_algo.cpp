#include <iostream>
#include <string>
#include <vector>

using namespace std;



string printlcs(string s1,string s2)
{
    int m,n;
    m=s1.size(),n=s2.size();
    vector< vector< pair<int,string> > >dp(m+1,vector< pair<int,string> > (n+1,make_pair(0,"")));
    pair<int,string> pp1;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                pp1=dp[i-1][j-1];
                int num=pp1.first+1;
                string str=pp1.second+s1[i-1];
                //Add spacing to sequence only if it's not the last element
                if(j == n )
                {
                
                    dp[i][j]=make_pair(num,str);
                }
                else
                {
                
                    dp[i][j]=make_pair(num,str+" ");
                
                }
            }
            else
            {
                if(dp[i-1][j]>=dp[i][j-1])
                {
                    pp1=dp[i-1][j];
                }
                else
                {
                    pp1=dp[i][j-1];
                }
                dp[i][j]=pp1;
            }
        }
    }
    return dp[m][n].second;
}

class ZAlgorithm 
{

    public:

        vector<int> calculateZ (string input,string pattern)
        {
            vector<int> Z (input.length());
            vactor <int> pattern_occur;
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
                    if(right-left == pattern.length())
                    {
                        pattern_occur.push_back(pattern.length());
                    
                    }
                    right--;
                
                }
                else
                {
                    int k1 = k -left;
                    if (Z[k1]<right - k+1)
                    {
                        Z[k] = Z[k1];
                        if(Z[k1]==pattern.lenth())
                        {
                        
                            pattern_occur.push_back(pattern.length());
                        
                        }
                    
                    }
                    else
                    {
                        left = k;
                        while (right < input.length() && input[right] == input[right-left])
                        {
                            right++;
                        }
                        Z[k] = right - left;
                        if(right-left == pattern.length())
                        {
                            pattern_occur.push_back(pattern.length());

                        }
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
            vector <int> Z = calculateZ(new_string,pattern); 
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
    string hint;
    int n;
    string line;
    string column = "";
    string sequence_row="";
    string sequence_col="";
    vector<string> matrix;

    ZAlgorithm *zAlgorithm = new ZAlgorithm();

    cin>>hint;
    cin>>n;

    for(int i = 0; i<n; i++)
    {
        cin>>line;
        matrix.push_back(line);
    
    }
    //Perform Z algorithm on the rows of the matrix

    for(string s:matrix)
    {
        sequence_row+= to_string(zAlgorithm->match_pattern(s,hint));
    
    }

    for(int i = 0; i<n;i++)
    {
        column = "";
        for(int j = 0;j < n;j++)
        {
            column+= matrix[j][i];
        
        }
        sequence_col+= to_string(zAlgorithm->match_pattern(column,hint));
    
    }
    cout<<printlcs(sequence_row,sequence_col);


    return 0;
}
