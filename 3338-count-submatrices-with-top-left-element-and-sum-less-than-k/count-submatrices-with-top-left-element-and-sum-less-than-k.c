int countSubmatrices(int** grid, int gridSize, int* gridColSize, int k)
{
    int i,j,cnt=0;
    int m=gridSize;
    int n=gridColSize[0];
    long long mat[m][n];
    mat[0][0]=grid[0][0];
    for(i=1;i<n;i++)
    {
        mat[0][i]=mat[0][i-1]+grid[0][i];
    }
    for(i=1;i<m;i++)
    {
        mat[i][0]=mat[i-1][0]+grid[i][0];
    }
    for(i=1;i<m;i++)
    {
        for(j=1;j<n;j++)
        {
            mat[i][j]=mat[i-1][j]+mat[i][j-1]+grid[i][j]-mat[i-1][j-1];
        }
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(mat[i][j]<=k)
            {
                cnt++;
            }
        }
    }
    return cnt;
}