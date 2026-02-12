int longestBalanced(char* s) {
    int l = strlen(s);
    bool flg;
    int mx = 1;
    for(int i=0;i<l-1;i++){
        int d[26]={0};
        for(int j=i;j<l;j++){
            d[s[j]-'a']++;
            if (j-i+1>mx){
                flg = true;
                int first = -1;
                for(int k=0;k<26;k++){
                    if (d[k]>0){
                        if(first==-1)first=d[k];
                        if(d[k]!=first){
                            flg = false;
                            break;
                        }
                    }
                }
                if (flg) mx = j-i+1;
            }
        }
    }
    return mx;
}