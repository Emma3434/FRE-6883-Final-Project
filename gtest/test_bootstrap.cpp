#include <gtest/gtest.h>
#include "StockData.h"
#include "Utils.h"

class BootstrapTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        //std::cout << "SetUpTestCase\n";
    }
    static void TearDownTestCase() {
        //std::cout << "TearDownTestCase\n";
    }
    virtual void SetUp() {
        //std::cout << "SetUp\n";
    }
    virtual void TearDown() {
        //std::cout << "TearDown\n";
    }
    vector<StockData> stock_list;
};

TEST_F(BootstrapTest, resultSize) {
    vector<StockData> stock_list_miss = load_stock_data(MISS_FILE, "Miss");
    vector<StockData> stock_list_meet = load_stock_data(MEET_FILE, "Meet");
    vector<StockData> stock_list_beat = load_stock_data(BEAT_FILE, "Beat");
    vector<StockData> stock_list = combine_stock_list(stock_list_miss, stock_list_meet, stock_list_beat);
    map<string, vector<StockData>> bootstrap_result;
    bootstrap_result = bootstrapping(stock_list);

    EXPECT_EQ(50, bootstrap_result["Beat"].size());
    EXPECT_EQ(50, bootstrap_result["Meet"].size());
    EXPECT_EQ(50, bootstrap_result["Miss"].size());
}

