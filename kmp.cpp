    vector<int> calculateLPS(string& pattern){
        int n = pattern.length();
        vector<int> lps(n,0);

        int len = 0;     //length of previous longest prefix suffix 
        int i=1;

        while(i<n){
            if(pattern[len]==pattern[i]){
                len++;
                lps[i]=len;
                i++;
            }
            else{
                if(len!=0){        //Use previous LPS value
                    len = lps[len-1];
                }
                else{
                    lps[i]=0;
                    i++;
                }
            }
        }

        return lps;
    }


    void KMPsearch(string text, string pattern){

        int m = pattern.size() , n = text.size();
        vector<int> lps = calculateLPS(pattern);

        int i = 0 ; //index for text
        int j = 0 ; //index for pattern

        while(i<n){
            if(text[i]==pattern[j]){
                i++;
                j++;
            }

            if(j==m){    //Full match found
                cout<<"Match found at index "<< i-j <<endl;
                j=lps[j-1];
            }

            else{
                if(j!=0){
                    j=lps[j-1];
                }
                else{
                    i++;
                }
            }
        }
    }
