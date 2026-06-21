class Solution {
public: // code written by sunny
    int maxIceCream(vector<int>& costs, int coins) {
        int maxCost = *max_element(costs.begin(), costs.end());
        vector<int> freq(maxCost + 1, 0);
        
        for (int cost : costs) {
            freq[cost]++;
        }
        
        int count = 0;
        for (int price = 1; price <= maxCost; price++) {
            if (coins < price) break;
            int canBuy = min(freq[price], coins / price);
            count += canBuy;
            coins -= canBuy * price;
        }
        
        return count;
    }
};