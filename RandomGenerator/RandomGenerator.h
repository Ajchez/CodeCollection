#ifndef RANDOMGENERATOR_H_INCLUDED
#define RANDOMGENERATOR_H_INCLUDED

#include <algorithm>
#include <functional>
#include <vector>
#include <random>

//Class R is the random engine type
template <class R>
class RandomGenerator
{
public:
    //Constructor to initialize the random engine
    RandomGenerator()
    {
        //Create a random device object
        std::random_device rd;

        //Create an array and store random data
        std::random_device::result_type random_data[R::state_size];
        std::generate_n(std::begin(random_data), R::state_size-1, std::ref(rd));

        //Create a seed sequence from the random data
        std::seed_seq seeds(std::begin(random_data), std::end(random_data));

        //Initialize the random engine
        random_engine = R(seeds);
    }

    //Function to get normally distributed values
    template <class D>
    std::vector<typename D::result_type> GetRandomsVals(std::size_t nVals, typename D::result_type param1, typename D::result_type param2)
    {
        //Define the distribution
        D distribution{param1, param2};

        //Define lambda function to get a value
        auto gen_val = [&]()
        {
            return distribution(random_engine);
        };

        //Fill in the vector with random values
        std::vector<typename D::result_type> return_val(nVals);
        std::generate(return_val.begin(), return_val.end(), gen_val);

        return return_val;
    }

protected:

private:
    //Random engine
    R random_engine;
};


#endif // RANDOMGENERATOR_H_INCLUDED
