class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> cnt(n + 1, 0);
        int minPrice = INT_MAX;

        for (auto &item : items) {
            cnt[item[0]]++;
            minPrice = min(minPrice, item[1]);
        }

        vector<int> gain(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                gain[i] += cnt[j];
            }

            if (gain[i] > 0)
                gain[i]--;
        }

        vector<pair<int, int>> v;

        for (auto &item : items) {
            int factor = item[0];
            int price = item[1];

            if (gain[factor] > 0 && price < 2LL * minPrice) {
                v.push_back({price, gain[factor]});
            }
        }

        sort(v.begin(), v.end());

        long long ans = 0;
        long long rem = budget;

        for (auto &p : v) {
            long long price = p.first;
            long long count = p.second;

            long long take = min(count, rem / price);

            ans += 2 * take;
            rem -= take * price;
        }

        ans += rem / minPrice;

        return (int)ans;
    }
};