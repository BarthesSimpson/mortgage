
class Portfolio
{
public:
    enum Strategy
    {
        PASSIVE,
        ACTIVE,
        MIXED
    };

    Portfolio(float endowment, Strategy strategy) : balance_(endowment), strategy_(strategy)
    {
        year_ = 0;
    };
    double getBalance();
    void getYear();
    void incrementYear();

private:
    double balance_;
    int year_;
    Strategy strategy_;
};
