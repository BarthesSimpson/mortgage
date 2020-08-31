class Market
{
public:
    enum Regime
    {
        LOW_INTEREST_RATES_INFLATION,
        LOW_INTEREST_RATES_NO_INFLATION,
        MODERATE_INTEREST_RATES,
        HIGH_INTEREST_RATES
    };
    Market(Regime regime) : regime_(regime){};

private:
    Regime regime_;
};
