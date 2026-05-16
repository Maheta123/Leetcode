class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        profit =0
        start =prices[0]

        for i in range(1,len(prices)):
            if start < prices[i]:   
                    profit +=  prices[i]-start
            start = prices[i]
                
                    
        return profit
            