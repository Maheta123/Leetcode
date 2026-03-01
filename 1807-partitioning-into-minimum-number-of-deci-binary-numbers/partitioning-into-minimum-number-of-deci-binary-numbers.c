int minPartitions(char* n) {
    
    int count=0;
        
    for(int i=0; n[i] != '\0'; i++){
            int curr = n[i] - '0';
            if(curr > count){
                    count = curr;

                    if(count== 9){
                        return 9;
                    }
            }
    }


    return count;
}