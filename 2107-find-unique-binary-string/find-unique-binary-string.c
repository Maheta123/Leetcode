char* findDifferentBinaryString(char** nums, int numsSize) 
{
    // allocate result string
    char* result=(char*)malloc((numsSize+1)*sizeof(char));
    for(int i=0;i<numsSize;i++)
    {
#        // flip the diagonal bit
        if(nums[i][i]=='0')
        result[i]='1';
        else
        result[i]='0';
    }
    result[numsSize]='\0';
    return result;
}