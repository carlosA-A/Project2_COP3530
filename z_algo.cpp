#include <iostream>
#include <string>
#include <vector>

using namespace std;




class Solution
{

    public:

        vector<int> calculateZ (string z_string,string pattern)
        {
            vector<int> Z (z_string.length());
            vector <int> pattern_occur;
            int left = 0;
            int right = 0;
            for(int k = 1; k < z_string.length(); k++)
            {
                if(k > right)
                {

                    left = right = k;
                    while (right < z_string.length() && z_string[right] == z_string[right-left])
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
                        if(Z[k1]==pattern.length())
                        {

                            pattern_occur.push_back(pattern.length());

                        }

                    }
                    else
                    {
                        left = k;
                        while (right < z_string.length() && z_string[right] == z_string[right-left])
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
            return pattern_occur;

        }

        int match_pattern(string text, string pattern)
        {
            //String used to start matching using Z algorithm, contains the pattern$text we are comparing
            string new_string = pattern+"$"+text;
            vector<int> result;
            vector <int> Z = calculateZ(new_string,pattern); 

            return Z.size();
        }
        //Print LCS function

        string printlcs(string s1,string s2)
        {
            int m,n;
            m=s1.size(),n=s2.size();
            vector< vector< pair<int,string> > >seq(m+1,vector< pair<int,string> > (n+1,make_pair(0,"")));
            pair<int,string> pair_int_str;
            //Create 2d matrix with table set to 0 and empty string by default
            for(int i=1;i<=m;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    if(s1[i-1]==s2[j-1])
                    {
                        pair_int_str=seq[i-1][j-1];
                        int num=pair_int_str.first+1;
                        string str=pair_int_str.second+s1[i-1];
                        //Add spacing to sequence only if it's not the last element
                        if(j == n )
                        {

                            seq[i][j]=make_pair(num,str);
                        }
                        else
                        {

                            seq[i][j]=make_pair(num,str+" ");

                        }
                    }
                    else
                    {
                        if(seq[i-1][j]>=seq[i][j-1])
                        {
                            pair_int_str=seq[i-1][j];
                        }
                        else
                        {
                            pair_int_str=seq[i][j-1];
                        }
                        seq[i][j]=pair_int_str;
                    }
                }
            }
            return seq[m][n].second;
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

    Solution *solution = new Solution();

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
        sequence_row+= to_string(solution->match_pattern(s,hint));

    }
    //Perform Z algorithm on each column
    for(int i = 0; i<n;i++)
    {
        column = "";
        for(int j = 0;j < n;j++)
        {
            column+= matrix[j][i];

        }
        sequence_col+= to_string(solution->match_pattern(column,hint));

    }
    //print LCS
    cout<<solution->printlcs(sequence_row,sequence_col)<<endl;


    return 0;
}
